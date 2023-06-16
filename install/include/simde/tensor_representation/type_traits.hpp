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

namespace simde {

template<std::size_t N, typename OperatorType>
class AOTensorRepresentation;

template<typename T>
struct NCenters;

template<std::size_t N, typename OperatorType>
struct NCenters<AOTensorRepresentation<N, OperatorType>>
  : std::integral_constant<std::size_t, N> {};

template<typename T>
struct OperatorType;

template<std::size_t N, typename OpType>
struct OperatorType<AOTensorRepresentation<N, OpType>> {
    using type = OpType;
};

template<typename T>
static constexpr std::size_t n_centers_v = NCenters<T>::value;

template<typename T>
using operator_t = typename OperatorType<T>::type;

} // namespace simde
