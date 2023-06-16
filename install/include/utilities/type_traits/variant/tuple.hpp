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
#include <tuple>
#include <variant>

/** @file tuple.hpp
 *
 *  @brief Contains type traits for working with variants as if they were
 *         tuples.
 *
 *  Much of the template meta-programming dealing with template parameter packs
 *  is implemented in terms of std::tuple. We have need to use that
 *  functionality with other variadic types, such as std::variant. The simplest
 *  way to do this is to define routines for converting std::variant to
 *  std::tuple and vice versa. *N.B.* These conversions are only of the type,
 *  they will not actually convert the instances.
 */

namespace utilities {
namespace detail_ {

/** @brief Primary template for converting a std::variant to a std::tuple
 *
 *  This is the primary template for converting a std::variant to a std::tuple.
 *  This template is not defined leading to a compiler error when @p T is not
 *  an instantiation of std::variant.
 *
 *  @tparam T The type we are attempting to convert to an std::tuple. For the
 *            primary template @p T will be any type aside from std::variant and
 *            the code will fail to compile.
 */
template<typename T>
struct variant_to_tuple;

/** @brief Specialization of variant_to_tuple for when the template paramter is
 *         a std::variant.
 *
 *  This specialization of variant_to_tuple is for when the template type
 *  parameter is an instantiation of std::variant. This class will contain a
 *  member type `type` set to the type of a std::tuple with the same template
 *  parameters as the std::variant it is specialized on.
 *
 *  @tparam Args The types in the std::variant.
 */
template<typename... Args>
struct variant_to_tuple<std::variant<Args...>> {
    using type = std::tuple<Args...>;
};
} // namespace detail_

/// Public API for getting the type of a tuple with the same types as a variant
template<typename T>
using variant_to_tuple_t = typename detail_::variant_to_tuple<T>::type;

} // namespace utilities