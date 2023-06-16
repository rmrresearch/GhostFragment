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
DECLARE_TEMPLATED_PROPERTY_TYPE(GeneralTransformedTensorRepresentation, N,
                                OperatorType);

template<std::size_t N, typename OperatorType>
TEMPLATED_PROPERTY_TYPE_INPUTS(GeneralTransformedTensorRepresentation, N,
                               OperatorType) {
    using ao_space          = type::ao_space;
    using derived_space     = type::derived_space;
    using tot_derived_space = type::tot_derived_space;
    // using ind_space         = type::independent_space;

    using ao_traits            = detail_::TensorRepTraits<ao_space>;
    using derived_space_traits = detail_::TensorRepTraits<derived_space>;
    using tot_derived_traits   = detail_::TensorRepTraits<tot_derived_space>;
    // using ind_space_traits     = detail_::TensorRepTraits<ind_space>;

    using ao_space_map      = typename ao_traits::map_type;
    using derived_space_map = typename derived_space_traits::map_type;
    using tot_space_map     = typename tot_derived_traits::map_type;
    // using ind_space_map     = typename ind_space_traits::map_type;

    using ao_space_map_t      = const ao_space_map&;
    using derived_space_map_t = const derived_space_map&;
    using tot_space_map_t     = const tot_space_map&;
    // using ind_space_map_t     = const ind_space_map&;
    using op_t = const OperatorType&;

    auto rv =
      pluginplay::declare_input()
        .add_field<ao_space_map_t>("AO spaces")
        .template add_field<derived_space_map_t>("derived spaces")
        .template add_field<tot_space_map_t>("tot spaces")
        //.template add_field<ind_space_map_t>("independent derivedspaces")
        .template add_field<op_t>("Operator");
    return rv;
}

template<std::size_t N, typename OperatorType>
TEMPLATED_PROPERTY_TYPE_RESULTS(GeneralTransformedTensorRepresentation, N,
                                OperatorType) {
    return pluginplay::declare_result().add_field<type::tensor_of_tensors>(
      "Transformed tensor");
}

} // namespace simde
