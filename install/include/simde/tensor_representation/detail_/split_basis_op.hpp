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
#include <chemist/chemist.hpp>

namespace simde::detail_ {

/** @brief Given the arguments to tensor_representation, this fxn returns two
 *         values: the operator in the arguments and a tuple containing just the
 *         basis sets.
 *
 *  The arguments to tensor_representation come in as a parameter pack. This
 *  function handles the process of separating the arguments into the perator
 *  instance and the basis set instances. Care is taken to ensure that no
 *  copying occurs.
 *
 *  @tparam Args The types of the arguments. Assumed to be an operator and a
 *               series of basis sets. The exact order depends on how many
 *               centers are in the integral.
 *
 *  @param[in] args The arguments being forwarded from tensor_representation.
 *                  Assumed to be basis sets and an operator.
 *
 *  @return A pair whose first element is the operator and whose second element
 *          is a tuple containing the basis sets.
 */
template<typename... Args>
auto split_basis_op(const Args&... args) {
    constexpr auto n_args = sizeof...(Args);
    auto arg_tuple        = std::tie(args...);

    // This could be done with TMP using some fancy traits to grab only select
    // elements out of a tuple, but those traits don't exist in utilities at the
    // moment.
    if constexpr(n_args == 3) {
        auto&& op            = std::get<1>(arg_tuple);
        using op_type        = std::decay_t<decltype(op)>;
        constexpr auto is_op = chemist::operators::is_operator_v<op_type>;
        static_assert(is_op, "For two centers, Op must be argument 1");

        auto&& bra = std::get<0>(arg_tuple);
        auto&& ket = std::get<2>(arg_tuple);
        using tuple_type =
          std::tuple<decltype(std::as_const(op)), decltype(std::tie(bra, ket))>;
        return tuple_type(std::as_const(op), std::tie(bra, ket));
    } else if constexpr(n_args == 4) {
        auto&& op            = std::get<1>(arg_tuple);
        using op_type        = std::decay_t<decltype(op)>;
        constexpr auto is_op = chemist::operators::is_operator_v<op_type>;
        static_assert(is_op, "For three centers, Op must be argument 1");

        auto&& bra       = std::get<0>(arg_tuple);
        auto&& ket1      = std::get<2>(arg_tuple);
        auto&& ket2      = std::get<3>(arg_tuple);
        using tuple_type = std::tuple<decltype(std::as_const(op)),
                                      decltype(std::tie(bra, ket1, ket2))>;
        return tuple_type(std::as_const(op), std::tie(bra, ket1, ket2));
    } else if constexpr(n_args == 5) {
        auto&& op            = std::get<2>(arg_tuple);
        using op_type        = std::decay_t<decltype(op)>;
        constexpr auto is_op = chemist::operators::is_operator_v<op_type>;
        static_assert(is_op, "For four centers, Op must be argument 2");

        auto&& bra1 = std::get<0>(arg_tuple);
        auto&& bra2 = std::get<1>(arg_tuple);
        auto&& ket1 = std::get<3>(arg_tuple);
        auto&& ket2 = std::get<4>(arg_tuple);

        using tuple_type =
          std::tuple<decltype(std::as_const(op)),
                     decltype(std::tie(bra1, bra2, ket1, ket2))>;
        return tuple_type(std::as_const(op), std::tie(bra1, bra2, ket1, ket2));
    } else {
        // N.B. If we get here we know n_args != 3, 4, or 5
        static_assert(n_args == 3,
                      "Only support 2, 3, or 4-centered integrals");
    }
}

} // namespace simde::detail_
