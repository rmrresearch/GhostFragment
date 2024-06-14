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
#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/nuclear_graph.hpp>
#include <simde/simde.hpp>

namespace ghostfragment::pt {

struct NuclearGraphToFragmentsTraits {
    /// Type of input to a NuclearGraphToFragments module
    using graph_type = ghostfragment::NuclearGraph;

    /// Type of result from a NuclearGraphToFragments module
    using fragment_type =
      chemist::fragmenting::FragmentedNuclei<chemist::Nuclei>;
};

DECLARE_PROPERTY_TYPE(NuclearGraphToFragments);

PROPERTY_TYPE_INPUTS(NuclearGraphToFragments) {
    using graph_type = const NuclearGraphToFragmentsTraits::graph_type&;

    return pluginplay::declare_input().add_field<graph_type>("Molecular Graph");
}

PROPERTY_TYPE_RESULTS(NuclearGraphToFragments) {
    using fragment_type = NuclearGraphToFragmentsTraits::fragment_type;

    return pluginplay::declare_result().add_field<fragment_type>("Fragments");
}

} // namespace ghostfragment::pt
