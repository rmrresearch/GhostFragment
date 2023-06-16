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
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

/** @brief The property type for modules that compute a sparse relation.
 *
 *  @tparam IndependType The type of the independent basis.
 *  @tparam DependType The type of the dependent basis.
 */
template<typename IndependType, typename DependType>
DECLARE_TEMPLATED_PROPERTY_TYPE(SparsityRelation, IndependType, DependType);

template<typename IndependType, typename DependType>
TEMPLATED_PROPERTY_TYPE_INPUTS(SparsityRelation, IndependType, DependType) {
    auto rv = pluginplay::declare_input()
                .add_field<const IndependType&>("Independent Basis")
                .template add_field<const DependType&>("Dependent Basis");
    rv["Independent Basis"].set_description("The dense basis");
    rv["Dependent Basis"].set_description("The sparse basis");
    return rv;
}

template<typename IndependType, typename DependType>
TEMPLATED_PROPERTY_TYPE_RESULTS(SparsityRelation, IndependType, DependType) {
    using chemist::type::sparse_map;
    auto rv = pluginplay::declare_result().add_field<sparse_map>("Sparse Map");
    rv["Sparse Map"].set_description(
      "Map from a given member of the independent basis to its"
      " domain in the dependent basis set");
    return rv;
}

using AO2AO = SparsityRelation<type::ao_space, type::ao_space>;
using MO2AO = SparsityRelation<type::derived_space, type::ao_space>;
using MO2MO = SparsityRelation<type::derived_space, type::derived_space>;

} // namespace simde
