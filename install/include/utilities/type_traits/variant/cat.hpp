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
#include "utilities/type_traits/tuple/variant.hpp"
#include "utilities/type_traits/variant/to_tuple.hpp"

namespace utilities::type_traits::variant {

/** @brief Creates a new variant by concatenating 0 or more variants.
 *
 *  This is a typedef of a single variant obtained from concatenating the types
 *  in 0 or more std::variant types.
 *
 *  @tparam Args 0 or more std::variant instances to concatenate.
 */
template<typename... Args>
using cat_t = tuple::to_variant_t<tuple::tuple_cat_t<to_tuple_t<Args>...>>;

} // namespace utilities::type_traits::variant