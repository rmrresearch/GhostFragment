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
#include "simde/tensor_representation/ao_tensor_representation.hpp"
#include "simde/tensor_representation/detail_/tensor_rep_traits.hpp"
#include "simde/types.hpp"
#include <pluginplay/pluginplay.hpp>

namespace simde::detail_ {

/** @brief Wraps dispatching from tensor_representation to a module
 *         satisfying property type AOTensorRepresentation.
 *
 *  This function handles forwarding the intermediate representation used in
 *  tensor_representation to a module satisfying property type
 *  AOTensorRepresentation.
 *
 *  @tparam N The number of centers in the integral. Assumed to be the same as
 *            the size of @p ao_spaces.
 *  @tparam OpType The type of the operator being evaluated. Assumed to be the
 *                 derived type and not the type-erased base.
 *
 *  @param[in] mod The module to call. Must satisfy AOTensorRepresentation
 *  @param[in] ao_spaces The ao spaces, in the intermediate representation
 *                       created by tensor_rep_parser.
 *  @param[in] op The operator to forward to @p mod.
 *
 *  @return The result of calling @p mod as property type
 *          AOTensorRepresentation<N, OpType>.
 *
 *  @throw ??? If @p mod throws while being run. Same throw guarantee.
 */
template<std::size_t N, typename OpType>
auto ao_dispatch(
  pluginplay::Module& mod,
  const typename TensorRepTraits<type::ao_space>::map_type& ao_spaces,
  const OpType& op) {
    using prop_type = AOTensorRepresentation<N, std::decay_t<OpType>>;

    const auto& bra1 = ao_spaces.at(0).get();

    if constexpr(N == 2) {
        const auto& ket1 = ao_spaces.at(1).get();
        return mod.run_as<prop_type>(bra1, op, ket1);
    } else if constexpr(N == 3) {
        const auto& ket1 = ao_spaces.at(1).get();
        const auto& ket2 = ao_spaces.at(2).get();
        return mod.run_as<prop_type>(bra1, op, ket1, ket2);
    } else if constexpr(N == 4) {
        const auto& bra2 = ao_spaces.at(1).get();
        const auto& ket1 = ao_spaces.at(2).get();
        const auto& ket2 = ao_spaces.at(3).get();
        return mod.run_as<prop_type>(bra1, bra2, op, ket1, ket2);
    } else {
        // If we get here we know N != 2 or 3 or 4
        static_assert(
          N == 2, "Unsupported number of centers. N must be in range [2,4]");
    }
}

} // namespace simde::detail_
