/*
 * Copyright 2024 GhostFragment
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
#include <chemist/chemical_system/chemical_system.hpp>
#include <ghostfragment/nuclear_graph.hpp>

namespace ghostfragment::pt {

struct NuclearGraphTraits {
    using input_type  = chemist::ChemicalSystem;
    using result_type = ghostfragment::NuclearGraph;
};

/** @brief Property type for forming a nuclear graph
 *
 *  There are a number of use cases in computational chemistry which lead to the
 *  chemical system being thought of as a mathematical graph. Modules which
 *  satisfy this property type are responsible for taking a ChemicalSystem and
 *  creating a nuclear graph from it (essentially the module must break the
 *  Molecule into nodes and assign connectivity to the nodes).
 */
DECLARE_PROPERTY_TYPE(NuclearGraph);

PROPERTY_TYPE_INPUTS(NuclearGraph) {
    using chemical_system_type = typename NuclearGraphTraits::input_type;
    using input_type = chemist::ChemicalSystemView<const chemical_system_type>;

    return pluginplay::declare_input().add_field<input_type>("Chemical System");
}

PROPERTY_TYPE_RESULTS(NuclearGraph) {
    using result_type = NuclearGraphTraits::result_type;

    return pluginplay::declare_result().add_field<result_type>("Graph");
}

} // namespace ghostfragment::pt
