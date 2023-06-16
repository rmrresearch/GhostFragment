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
#include <type_traits> // For add_const
#include <variant>     // For std::variant

namespace utilities::type_traits::variant {

namespace detail_ {

/** @brief Primary template for adding const to all types in a variant.
 *
 *  The primary template is not defined and results in a compilation error if
 *  @p T is not a specialization of std::variant.
 *
 *  @tparam T The type of the variant we are adding const to. If this
 *            template is selected it means @p T is not actually a
 *            specialization of std::variant.
 */
template<typename T>
struct AddConst;

/** @brief Specialization of AddConst for when the template type parameter is a
 *         std::variant.
 *
 *  This structure contains a member typedef, `type`, which is set to the type
 *  of a std::variant with the same types as the parameter pack `Args` except
 *  that each type is now const.
 *
 *  @tparam Args The types in the original variant.
 */
template<typename... Args>
struct AddConst<std::variant<Args...>> {
    /// Type of the variant with all types made const
    using type = std::variant<std::add_const_t<Args>...>;
};

} // namespace detail_

/** @brief Public API for adding const to all types in an std::variant.
 *
 *  This type trait can be used to add const to all types in an std::variant.
 *
 *  @tparam T The std::variant whose types are being made const. If @p T is not
 *            a specialization of std::variant this will fail to compile.
 */
template<typename T>
using add_const_t = typename detail_::AddConst<T>::type;

} // namespace utilities::type_traits::variant
