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

#include "ghostfragment/property_types/fragmenting/capped_fragments.hpp"
#include "ghostfragment/property_types/fragmenting/fragment_weights.hpp"
#include "ghostfragment/property_types/fragmenting/fragmented_chemical_system.hpp"
#include "ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp"
#include "ghostfragment/property_types/fragmenting/intersections.hpp"
#include "ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp"
#include "ghostfragment/property_types/topology/broken_bonds.hpp"
#include "ghostfragment/property_types/topology/connectivity_table.hpp"
#include "ghostfragment/property_types/topology/nuclear_graph.hpp"
#include "property_type/macros.hpp"
#include <ghostfragment/ghostfragment.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment {

EXPORT_PLUGIN(ghostfragment, m) {

    using namespace pt;
    EXPORT_PROPERTY_TYPE(CappedFragments, m);
    EXPORT_PROPERTY_TYPE(FragmentedNuclei, m);
    EXPORT_PROPERTY_TYPE(FragmentedChemicalSystem, m);
    EXPORT_PROPERTY_TYPE(FragmentWeights, m);
    EXPORT_PROPERTY_TYPE(ConnectivityTable, m);
    EXPORT_PROPERTY_TYPE(BrokenBonds, m);
    EXPORT_PROPERTY_TYPE(Intersections, m);
    EXPORT_PROPERTY_TYPE(NuclearGraph, m);

}

} // namespace ghostfragment
