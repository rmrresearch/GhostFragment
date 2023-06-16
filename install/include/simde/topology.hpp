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
#include <pluginplay/pluginplay.hpp>

namespace simde {

DECLARE_PROPERTY_TYPE(MolecularTopology);

PROPERTY_TYPE_INPUTS(MolecularTopology) {
    using mol_input_t = const type::molecule&;
    auto rv = pluginplay::declare_input().add_field<mol_input_t>("Molecule");
    rv.at("Molecule")
      .set_description("Molecular system whose topology is being determined");
    return rv;
}

PROPERTY_TYPE_RESULTS(MolecularTopology) {
    using topology_t = type::topology;
    auto rv = pluginplay::declare_result().add_field<topology_t>("Topology");
    rv.at("Topology").set_description("Topology of input molecule");
    return rv;
}

} // namespace simde
