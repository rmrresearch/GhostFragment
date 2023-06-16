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
#include "utilities/printing/print_stl.hpp"
#include <ostream>
#include <type_traits>

namespace utilities::type_traits {
namespace detail_ {

using namespace utilities::printing;

/// Typedef of the result of calling std::ostream<< on an object of type @p T
template<typename T>
using result_of_insertion =
  decltype(std::declval<std::ostream&>() << std::declval<T>());

} // namespace detail_

/** @brief Used to determine if an object can be forwarded to an std::ostream
 *
 *  This is the primary template for checking if an object of a given type can
 *  be printed out by passing it to an std::ostream. The class IsPrintable will
 *  contain a constexpr static bool member `value` whose value is true if the
 *  @p T can be printed out and false otherwise. The primary template catches
 *  all the cases where @p T can not be printed out.
 *
 *  @tparam T the type for which printing abilities are in question.
 *  @tparam <anonymous> type used purely for SFINAE.
 */
template<typename T, typename = void>
struct IsPrintable : std::false_type {};

/** @brief Specializes IsPrintable for printable types
 *
 *  This specialization will only compile if it is possible to print out an
 *  object of type @p T.
 *
 *  @tparam T the type for which printing abilities are in question.
 *  @tparam <anonymous> type used purely for SFINAE.
 */
template<typename T>
struct IsPrintable<T, std::void_t<detail_::result_of_insertion<T>>>
  : std::true_type {};

/** @brief Makes it easier to determine a type is printable.
 *
 *  This is a const global variable whose value is true if @p T is printable and
 *  false otherwise.
 *
 * @tparam T The type whose printable-ness is in question.
 */
template<typename T>
static constexpr bool is_printable_v = IsPrintable<T>::value;

} // namespace utilities::type_traits
