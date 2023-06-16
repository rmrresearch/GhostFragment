/*
 * Copyright 2022 NWChemEx-Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <parallelzone/mpi_helpers/traits/mpi_data_type.hpp>
#include <parallelzone/mpi_helpers/traits/mpi_op.hpp>

/** @file commpp.ipp
 *
 *  This file contains the inline definitions for the CommPP class. It is not
 *  meant for inclusion in any other file besides commpp.hpp
 */

namespace parallelzone::mpi_helpers {

template<typename T>
typename CommPP::gather_return_type<T> CommPP::gather(T&& input,
                                                      size_type root) const {
    return gather_t_(std::forward<T>(input), root);
}

template<typename T>
typename CommPP::all_gather_return_type<T> CommPP::gather(T&& input) const {
    return *gather_t_(std::forward<T>(input), std::nullopt);
}

template<typename T>
typename CommPP::gather_return_type<T> CommPP::gatherv(T&& input,
                                                       size_type root) const {
    return gatherv_t_(std::forward<T>(input), root);
}

template<typename T>
typename CommPP::all_gather_return_type<T> CommPP::gatherv(T&& input) const {
    return *gatherv_t_(std::forward<T>(input), std::nullopt);
}

template<typename T, typename Fxn>
typename CommPP::reduce_return_type<T> CommPP::reduce(T&& input, Fxn&& fxn,
                                                      size_type root) const {
    return reduce_t_(std::forward<T>(input), std::forward<Fxn>(fxn), root);
}

template<typename T, typename Fxn>
typename CommPP::all_reduce_return_type<T> CommPP::reduce(T&& input,
                                                          Fxn&& fxn) const {
    return *reduce_t_(std::forward<T>(input), std::forward<Fxn>(fxn),
                      std::nullopt);
}

// -----------------------------------------------------------------------------
// -- Private Methods
// -----------------------------------------------------------------------------

template<typename T>
typename CommPP::gather_return_type<T> CommPP::gather_t_(
  T&& input, opt_root_t root) const {
    using clean_type  = std::decay_t<T>;
    using return_type = typename CommPP::gather_return_type<clean_type>;
    using value_type  = typename return_type::value_type;

    const bool am_i_root = root.has_value() ? me() == *root : true;

    if constexpr(needs_serialized_v<clean_type>) {
        // Do gather in binary
        auto binary    = make_binary_buffer(std::forward<T>(input));
        auto binary_rv = gather_(binary, root);

        // Early out if not root
        return_type rv;
        if(!binary_rv.has_value()) return rv;

        // We got back a std::vector<std::byte> which contains this->size()
        // instances of type clean_type, the serialized form of each clean_type
        // object has size binary_rv->size() / this->size()
        const auto& buffer   = *binary_rv;
        auto serialized_size = buffer.size() / size();

        value_type vec(size());
        for(size_type i = 0, j = 0; i < buffer.size();
            i += serialized_size, ++j) {
            const_binary_reference view(binary_rv->data() + i, serialized_size);
            vec[j] = std::move(from_binary_view<clean_type>(view));
        }
        rv.emplace(std::move(vec));
        return rv;
    } else {
        // TODO: make traits to_binary, binary_size to wrap calling .data() and
        //       .size()
        const_binary_reference input_binary(input.data(), input.size());

        // Make output buffer, but only allocate on root
        value_type output;
        if(am_i_root) value_type(input.size() * size()).swap(output);
        binary_reference output_binary(output.data(), output.size());

        gather_(input_binary, output_binary, root);

        return_type rv;
        if(am_i_root) rv.emplace(std::move(output));
        return rv;
    }
}

template<typename T>
typename CommPP::gather_return_type<T> CommPP::gatherv_t_(
  T&& input, opt_root_t root) const {
    using clean_type  = std::decay_t<T>;
    using return_type = typename CommPP::gather_return_type<clean_type>;
    using value_type  = typename return_type::value_type;

    const bool am_i_root = root.has_value() ? me() == *root : true;

    if constexpr(needs_serialized_v<clean_type>) {
        //  Do gather in binary
        auto binary    = make_binary_buffer(std::forward<T>(input));
        auto binary_rv = gatherv_(binary, root);

        // Early out if not root
        return_type rv;
        if(!binary_rv.has_value()) return rv;

        // We got back a std::vector<std::byte> of the binary data
        // and the sizes sent by each rank
        const auto& buffer = binary_rv->first;
        const auto& sizes  = binary_rv->second;

        value_type vec(size());
        for(size_type i = 0, total = 0; i < size(); ++i) {
            const_binary_reference view(buffer.data() + total, sizes[i]);
            vec[i] = std::move(from_binary_view<clean_type>(view));
            total += sizes[i];
        }
        rv.emplace(std::move(vec));
        return rv;
    } else {
        // TODO: make traits to_binary, binary_size to wrap calling .data() and
        //       .size()
        const_binary_reference input_binary(input.data(), input.size());

        // TODO: avoid copy by preallocating buffer
        auto binary_rv = gatherv_(input_binary, root);

        // Early out if not root
        return_type rv;
        if(!binary_rv.has_value()) return rv;

        // We got back a std::vector<std::byte> of the binary data
        // and the sizes (in bytes) sent by each rank
        const auto& buffer    = binary_rv->first;
        using element_type    = typename value_type::value_type;
        constexpr auto t_size = sizeof(element_type);

        value_type vec;
        auto n_elements = buffer.size() / t_size;
        for(size_type i = 0; i < buffer.size(); i += t_size) {
            const_binary_reference view(buffer.data() + i, t_size);
            vec.emplace_back(std::move(from_binary_view<element_type>(view)));
        }
        rv.emplace(std::move(vec));
        return rv;
    }
}

template<typename T, typename Fxn>
typename CommPP::reduce_return_type<T> CommPP::reduce_t_(
  T&& input, Fxn&& fxn, opt_root_t root) const {
    // Assumed to be a container
    using clean_type = std::decay_t<T>;
    using value_type = typename clean_type::value_type;
    using clean_fxn  = std::decay_t<Fxn>;

    static_assert(!needs_serialized_v<clean_type>, "Doesn't needs serialized?");
    static_assert(has_mpi_data_type_v<value_type>, "Is a recognized MPI type?");
    static_assert(has_mpi_op_v<clean_fxn>, "Is a recognized MPI Operation?");

    const auto am_i_root = root.has_value() ? me() == *root : true;
    const auto n_elems   = input.size();
    auto type            = mpi_data_type_v<value_type>;
    auto op              = mpi_op_v<clean_fxn>;

    std::vector<value_type> temp;
    if(am_i_root) std::vector<value_type>(n_elems).swap(temp);

    const auto send = input.data();
    const auto recv = temp.data();

    if(root.has_value()) {
        MPI_Reduce(send, recv, n_elems, type, op, *root, comm());
    } else {
        MPI_Allreduce(send, recv, n_elems, type, op, comm());
    }
    reduce_return_type<T> rv;
    if(am_i_root) rv.emplace(std::move(temp));
    return rv;
}

} // namespace parallelzone::mpi_helpers
