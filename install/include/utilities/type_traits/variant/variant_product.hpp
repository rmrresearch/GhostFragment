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
#include "utilities/type_traits/tuple/tuple_product.hpp"
#include "utilities/type_traits/tuple/variant.hpp"
#include "utilities/type_traits/variant/to_tuple.hpp"
#include <variant>

namespace utilities::type_traits::variant {
namespace detail_ {
/// Makes variant_prod_t easier to read
template<template<typename, typename> typename Op, typename LHSVariant,
         typename RHSVariant>
struct variant_prod {
    /// Convert LHSVariant to a tuple
    using lhs_as_tuple = to_tuple_t<LHSVariant>;
    /// Convert RHSVariant to a tuple
    using rhs_as_tuple = to_tuple_t<RHSVariant>;
    /// Take product of the two tuples, result is a tuple
    using result_type = tuple::product_t<Op, lhs_as_tuple, rhs_as_tuple>;
    /// Convert product tuple to a variant
    using type = tuple::to_variant_t<result_type>;
};

} // namespace detail_

/** @brief Takes the Cartesian product of two variants.
 *
 *  This typedef will be set to a variant whose types are the Cartesian
 *  products of the types in @p LHSVariant with the types in @p RHSVariant. The
 *  type @p Op will be used to group the pairs. For example:
 *
 *  @code
 *  using variant0 = std::variant<int, double>;
 *  using variant1 = std::variant<float, char>;
 *  using variant01 = variant_prod_t<std::pair, variant0, variant1>;
 *  @endcode
 *
 *  will result in `variant01` being a typedef of
 * `std::variant<std::pair<int, float>, std::pair<int, char>, std::pair<double,
 *  float>, std::pair<double, char>>`.
 *
 *  @tparam Op A type templated on two types. @p Op will be used to group
 *             the pairs formed from taking the cartesian product of the types
 *             in @p LHSVariant and @p RHSVariant.
 *  @tparam LHSVariant The variant containing the first members of the pairs.
 *  @tparam RHSVariant The variant containing the second members of the pairs.
 */
template<template<typename, typename> typename Op, typename LHSVariant,
         typename RHSVariant>
using product_t =
  typename detail_::variant_prod<Op, LHSVariant, RHSVariant>::type;

} // namespace utilities::type_traits::variant
