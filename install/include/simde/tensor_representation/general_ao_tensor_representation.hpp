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

// #pragma once
// #include "simde/tensor_representation/detail_/tensor_rep_traits.hpp"
// #include "simde/types.hpp"

// namespace simde {

// template<std::size_t N, typename OperatorType>
// DECLARE_TEMPLATED_PROPERTY_TYPE(GeneralAOTensorRepresentation, N,
// OperatorType);

// template<std::size_t N, typename OperatorType>
// TEMPLATED_PROPERTY_TYPE_INPUTS(GeneralAOTensorRepresentation, N,
// OperatorType) {
//     using ao_space        = type::ao_space;
//     using sparse_ao_space = type::sparse_ao_space;

//     using ao_traits        = detail_::TensorRepTraits<ao_space>;
//     using sparse_ao_traits = detail_::TensorRepTraits<sparse_ao_space>;

//     using ao_space_map        = typename ao_traits::map_type;
//     using sparse_ao_space_map = typename sparse_ao_traits::map_type;

//     using ao_space_map_t        = const ao_space_map&;
//     using sparse_ao_space_map_t = const sparse_ao_space_map&;
//     using op                    = const OperatorType&;

//     auto rv = pluginplay::declare_input()
//                 .add_field<ao_space_map_t>("AO Spaces")
//                 .template add_field<sparse_ao_space_map_t>("Sparse AO
//                 Spaces") .template add_field<op>("Operator");
//     return rv;
// }

// template<std::size_t N, typename OperatorType>
// TEMPLATED_PROPERTY_TYPE_RESULTS(GeneralAOTensorRepresentation, N,
//                                 OperatorType) {
//     auto rv =
//     pluginplay::declare_result().add_field<type::tensor_of_tensors>(
//       "Tensor representation");
//     return rv;
// }

// } // namespace simde
