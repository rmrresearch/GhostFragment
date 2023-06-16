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

/** @file variant.hpp
 *
 *  @brief Contains type traits for working with tuples as if they were
 *         variants.
 *
 *  Much of the template meta-programming dealing with template parameter packs
 *  is implemented in terms of std::tuple. We have need to use that
 *  functionality with other variadic types, such as std::variant. The simplest
 *  way to do this is to define routines for converting std::variant to
 *  std::tuple and vice versa. *N.B.* These conversions are only of the type,
 *  they will not actually convert the instances.
 */

namespace utilities::type_traits::tuple {
namespace detail_ {

/** @brief Primary template for converting a std::tuple to a std::variant
 *
 *  This is the primary template for converting a std::tuple to a std::variant.
 *  This template is not defined leading to a compiler error when @p T is not
 *  an instantiation of std::tuple.
 *
 *  @tparam T The type we are attempting to convert to an std::variant. For the
 *            primary template @p T will be any type aside from std::tuple and
 *            the code will fail to compile.
 */
template<typename T>
struct to_variant;

/** @brief Specialization of tuple_to_variant for when the template paramter is
 *         a std::tuple.
 *
 *  This specialization of tuple_to_variant is for when the template type
 *  parameter is an instantiation of std::tuple. This class will contain a
 *  member type `type` set to the type of a std::variant with the same template
 *  parameters as the std::tuple it is specialized on.
 *
 *  @tparam Args The types in the std::tuple.
 */
template<typename... Args>
struct to_variant<std::tuple<Args...>> {
    using type = std::variant<Args...>;
};

} // namespace detail_

/// Public API for getting the type of a variant with the same types as a tuple
template<typename T>
using to_variant_t = typename detail_::to_variant<T>::type;

} // namespace utilities::type_traits::tuple
