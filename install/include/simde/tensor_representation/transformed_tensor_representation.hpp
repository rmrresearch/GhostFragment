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
#include "simde/tensor_representation/detail_/tensor_rep_traits.hpp"
#include "simde/types.hpp"

namespace simde {

template<std::size_t N, typename OperatorType>
DECLARE_TEMPLATED_PROPERTY_TYPE(TransformedTensorRepresentation, N,
                                OperatorType);

template<std::size_t N, typename OperatorType>
TEMPLATED_PROPERTY_TYPE_INPUTS(TransformedTensorRepresentation, N,
                               OperatorType) {
    using ao_space      = type::ao_space;
    using derived_space = type::derived_space;

    using ao_traits      = detail_::TensorRepTraits<ao_space>;
    using derived_traits = detail_::TensorRepTraits<derived_space>;

    using ao_space_map      = typename ao_traits::map_type;
    using derived_space_map = typename derived_traits::map_type;

    using ao_space_map_t      = const ao_space_map&;
    using derived_space_map_t = const derived_space_map&;
    using op_t                = const OperatorType&;

    auto rv = pluginplay::declare_input()
                .add_field<ao_space_map_t>("AO spaces")
                .template add_field<derived_space_map_t>("Derived spaces")
                .template add_field<op_t>("Operator");
    return rv;
}

template<std::size_t N, typename OperatorType>
TEMPLATED_PROPERTY_TYPE_RESULTS(TransformedTensorRepresentation, N,
                                OperatorType) {
    return pluginplay::declare_result().add_field<type::tensor>(
      "Transformed tensor");
}

} // namespace simde
