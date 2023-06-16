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
#include "utilities/type_traits/parameter_pack_traits.hpp"
#include <tuple>
#include <type_traits>

namespace utilities::type_traits::tuple {
namespace detail_ {

/** @brief Primary template for determining if a type is in a tuple.
 *
 *  This struct can be used to determine if @p Type2Look4 appears in the tuple
 *  @p Tuple. The primary template is selected when @p Tuple is not an
 *  std::tuple; the primary template is not defined and thus a compilation error
 *  will arise if @p Tuple is not a tuple.
 *
 *  @tparam Type2Look4 The type we are attempting to find in @p Tuple
 *  @tparam Tuple If this version of has_type is selected @p Tuple will be a
 *                type other than std::tuple.
 */
template<typename Type2Look4, typename Tuple>
struct has_type;

/// Implementation of `has_type` for tuple types
template<typename Type2Look4, typename... TupleTypes>
struct has_type<Type2Look4, std::tuple<TupleTypes...>>
  : public utilities::type_traits::parameter_pack_contains_type<Type2Look4,
                                                                TupleTypes...> {
};

} // namespace detail_

/** @brief Global variable indicating whether @p Type2Look4 is in the tuple
 *         @p Tuple.
 *
 *  This is the public API for determining if a type appears in a tuple. If
 *  @p Type2Look4 appears in @p Tuple this variable will be set to true,
 *  otherwise it is set to false.
 *
 *  @tparam Type2Look4 The type we are looking for.
 *  @tparam Tuple The tuple we are searching.
 */
template<typename Type2Look4, typename Tuple>
static constexpr bool has_type_v = detail_::has_type<Type2Look4, Tuple>::value;

template<typename Type2Look4, typename Tuple, typename T = void>
using enable_if_has_type_t = std::enable_if_t<has_type_v<Type2Look4, Tuple>, T>;

} // namespace utilities::type_traits::tuple
