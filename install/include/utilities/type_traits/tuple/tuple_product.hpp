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
#include "utilities/type_traits/tuple/tuple_cat.hpp"
#include <tuple>

namespace utilities::type_traits::tuple {
namespace detail_ {

/** @brief typedef of Op<LHSType, RHSType>
 *
 *  This is the end point for expanding both parameter packs in tuple_product_t.
 *  It is the fundamental templated type which will be present in the final
 *  tuple.
 *
 *  @tparam Op A type that is templated on two types.
 *  @tparam LHSType The first type which will be used as @p Op's first template
 *                  type parameter.
 *  @tparam RHSType The second type which will be used as @p Op's second
 *                  template type parameter.
 */
template<template<typename, typename> typename Op, typename LHSType,
         typename RHSType>
using base_prod_t = Op<LHSType, RHSType>;

/** @brief Function which returns a tuple of base_prod_t types.
 *
 *  This function declaration is used exclusively for its return type. More
 *  specifically we use the input argument to determine the parmater pack of an
 *  input tuple. Once we know the parameter pack we have the function return a
 *  new tuple resulting from pairing @p LHSType with each type in the parameter
 *  pack.
 *
 *  @note This function is never actually defined and it should thus never be
 *        called.
 *  @tparam Op A type templated on two types. @p Op will be used to "glue"
 *             together all of the pairs formed from @p LHSType and the types
 *             in the @p RHSTypes parameter pack.
 *  @tparam LHSType The type which will be the first type parameter to @p Op
 *  @tparam RHSTypes The types which will be paired with @p LHSType one at a
 *                   time.
 *  @param[in] <anonymous> A tuple. We only care about the tuple's type.
 *
 *  @return A tuple resulting from combining LHSType with each type in the
 *          input tuple.
 */
template<template<typename, typename> typename Op, typename LHSType,
         typename... RHSTypes>
auto base_prod_expand_r(std::tuple<RHSTypes...>)
  -> std::tuple<base_prod_t<Op, LHSType, RHSTypes>...>;

/** @brief A typdef to make it easier to get the return of base_prod_expand_r
 *
 *  @tparam Op A type templated on two types. Will be used to "glue" together
 *             pairs of @p LHSType and the types in @p RHSTypes.
 *  @tparam LHSType The type which will be the first type parameter to @p Op
 *  @tparam RHSTypes The types which will be paired with @p LHSType one at a
 *                   time.
 */
template<template<typename, typename> typename Op, typename LHSType,
         typename RTuple>
using base_prod_expand_r_t =
  decltype(base_prod_expand_r<Op, LHSType>(std::declval<RTuple>()));

/** @brief Function which returns a tuple filled with pairs of types from two
 *         tuples.
 *
 *  This function is used to deduce the type of a tuple filled with templated
 *  types @p Op where the first template parameter is taken from the types in
 *  one tuple and the second template parameter is taken from the types of a
 *  second tuple.
 *
 *  @note This function is not actually defined and is only used to for its
 *        ability to get at the tuple's parameter packs.
 *
 *  @tparam Op A type templated on two types. @p Op will be used to "glue"
 *             together all of the pairs formed from cartesian product of the
 *             @p LHSTypes and @p RHSTypes parameter packs.
 *  @tparam LHSType The first of two parameter packs to glue together.
 *  @tparam RHSTypes The second parameter pack to glue together.
 *
 *  @param[in] <anonymous> The tuple from which @p LHSTypes will be deduced.
 *  @param[in] <anonymous> The tuple from which @p RHSTypes will be deduced.
 *
 *  @return A tuple containing a series of @p Op types where the template
 *          parameters are the Cartesian product of the types in @p LHSTypes and
 *          @p RHSTypes.
 */
template<template<typename, typename> typename Op, typename... LHSTypes,
         typename... RHSTypes>
auto base_prod_expand_r_and_l(std::tuple<LHSTypes...>, std::tuple<RHSTypes...>)
  -> tuple_cat_t<
    base_prod_expand_r_t<Op, LHSTypes, std::tuple<RHSTypes...>>...>;

} // namespace detail_

/** @brief Takes the Cartesian product of two tuples.
 *
 *  This typedef will be set to a tuple whose types are the Cartesian
 *  products of the types in @p LHSTuple with the types in @p RHSTuple. The type
 *  @p Op will be used to group the pairs. For example:
 *
 *  @code
 *  using tuple0 = std::tuple<int, double>;
 *  using tuple1 = std::tuple<float, char>;
 *  using tuple01 = tuple_prod_t<std::pair, tuple0, tuple1>;
 *  @endcode
 *
 *  will result in `tuple01` being a typedef of
 * `std::tuple<std::pair<int, float>, std::pair<int, char>, std::pair<double,
 *  float>, std::pair<double, char>>`.
 *
 *  @tparam Op A type templated on two types. @p Op will be used to group
 *             the pairs formed from taking the cartesian product of the types
 *             in @p LHSTuple and @p RHSTuple.
 *  @tparam LHSTuple The tuple containing the first members of the pairs.
 *  @tparam RHSTuple The tuple containing the second members of the pairs.
 */
template<template<typename, typename> typename Op, typename LHSTuple,
         typename RHSTuple>
using product_t = decltype(detail_::base_prod_expand_r_and_l<Op>(
  std::declval<LHSTuple>(), std::declval<RHSTuple>()));

} // namespace utilities::type_traits::tuple
