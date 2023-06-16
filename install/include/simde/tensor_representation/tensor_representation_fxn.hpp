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
#include "simde/tensor_representation/detail_/ao_dispatch.hpp"
#include "simde/tensor_representation/detail_/split_basis_op.hpp"
#include "simde/tensor_representation/detail_/tensor_rep_parser.hpp"
#include "simde/tensor_representation/detail_/transform_traits.hpp"
#include "simde/tensor_representation/general_ao_tensor_representation.hpp"
#include "simde/tensor_representation/general_transformed_tensor_representation.hpp"
#include "simde/tensor_representation/transformed_tensor_representation.hpp"
#include "simde/types.hpp"
#include <chemist/chemist.hpp>

namespace simde {

/** @brief Syntactic sugar for computing a tensor filled with integrals.
 *
 *  Quantum chemistry deals with a lot of tensors. Standard notation represents
 *  an element of the tensor using braket notation with one index per mode. The
 *  index used typically corresponds to the basis set for that mode (*e.g.*, it
 *  is common to use i,j,k... for occupied MOs and a,b,c... for virtual MOs).
 *  In the spirit of the standard notation, the tensor_representation function
 *  allows a user to request an integral tensor by specifying the basis sets
 *  for each mode of the tensor (and the operator). For example,
 *
 *  @code
 *  auto i     = get_occupied_orbitals();
 *  auto a     = get_virtual_orbitals();
 *  auto r_hat = get_dipole_operator();
 *  auto mod   = get_dipole_module();
 *
 *  auto [r_ia] = tensor_representation(mod, i, r_hat, a);
 *  @endcode
 *
 *  would compute the transition dipole moment. The underlying modules will
 *  automatically take care of building and transforming the integrals as
 *  needed (re-using them when possible); you just have to use the result!!!
 *
 *  @tparam Args The types of the arguments being used to specify the integral.
 *               For an N-center integral there should be N+1 types in parameter
 *               pack (the types of the basis functions for each of the N
 *               centers plus the type of the operator). Types are expected to
 *               be orbital spaces or derived from chemist::OperatorBase.
 *
 * @param[in] mod The module which actually computes the integral.
 *
 * @param[in] args The specification of the integral. For two-electron integrals
 *                 chemist notation is used ("bra" indices are for electron 1,
 *                 "ket" indices are for electron 2).
 *
 * @return The tensor representation of the operator, in the specified basis
 *         set.
 *
 */
template<typename... Args>
auto tensor_representation(pluginplay::Module& mod, const Args&... args) {
    constexpr auto n_add_args = sizeof...(Args); // # of additional arguments
    constexpr auto n_center   = n_add_args - 1;  // One arg is an operator

    // Basic compile-time error checking
    static_assert(n_center >= 2, "Minimally must be a two-center integral");
    static_assert(n_center <= 4, "Only support up to four-center integrals");

    auto&& [op, bases] = detail_::split_basis_op(args...);

    detail_::TensorRepParser p(bases);

    using transform_traits_t = detail_::TransformTraits<std::decay_t<Args>...>;
    constexpr bool has_tots  = transform_traits_t::has_tots;
    constexpr bool has_derived = transform_traits_t::has_derived;
    constexpr bool is_general  = has_tots;
    constexpr bool is_derived  = has_derived && (!is_general);
    constexpr bool is_all_ao   = (!has_derived) && (!is_general);

    using op_type = std::decay_t<decltype(op)>;

    if constexpr(is_all_ao) {
        return detail_::ao_dispatch<n_center, op_type>(mod, p.m_ao_spaces, op);
    } else if constexpr(is_derived) {
        using pt = TransformedTensorRepresentation<n_center, op_type>;
        // Some of the spaces may be independent, need to handle this

        return mod.run_as<pt>(p.m_ao_spaces, p.m_derived_spaces, op);
    } else {
        using pt = GeneralTransformedTensorRepresentation<n_center, op_type>;
        return mod.run_as<pt>(p.m_ao_spaces, p.m_derived_spaces, p.m_tot_spaces,
                              // p.m_ind_spaces,
                              op);
    }
}

} // namespace simde
