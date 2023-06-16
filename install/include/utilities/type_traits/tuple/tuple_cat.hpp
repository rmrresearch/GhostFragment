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

namespace utilities::type_traits::tuple {

/** @brief Type of resulting from concatentating several tuple types together.
 *
 *  This typedef
 *
 *  As an example:
 *
 *  @code
 *  using tuple0_t = std::tuple<int, double>;
 *  using tuple1_t = std::tuple<char, bool>;
 *  using tuple0p1_t = tuple_cat_t<tuple0_t, tuple1_t>;
 *  @endcode
 *
 *  Results in the typedef `tuple0p1_t` being a typedef of
 *  `std::tuple<int, double, char, bool>`.
 *
 *  @tparam Args A series of 0 or more tuple types. Each type in the template
 *               parameter pack is expected to be an instantiation of
 *               std::tuple.
 */
template<typename... Args>
using tuple_cat_t = decltype(std::tuple_cat(std::declval<Args>()...));

} // namespace utilities::type_traits::tuple
