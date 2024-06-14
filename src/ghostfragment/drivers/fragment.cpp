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

#include "drivers.hpp"
#include <ghostfragment/property_types/fragmenting/capped_fragments.hpp>
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/fragmenting/intersections.hpp>
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
#include <ghostfragment/property_types/topology/broken_bonds.hpp>
#include <ghostfragment/property_types/topology/connectivity_table.hpp>
#include <ghostfragment/property_types/topology/nuclear_graph.hpp>
namespace ghostfragment::drivers {

using conn_pt          = pt::ConnectivityTable;
using broken_bonds_pt  = pt::BrokenBonds;
using cap_pt           = pt::CappedFragments;
using frags_pt         = pt::FragmentedNuclei;
using intersections_pt = pt::Intersections;
using graph_pt         = pt::NuclearGraph;
using graph2frags_pt   = pt::NuclearGraphToFragments;
using n_type           = unsigned short;

const auto mod_desc = R"(
Fragment Driver
---------------

This module is responsible for going from a chemist::ChemicalSystem object to
a chemist::FragmentedNuclei object. Generally speaking this occurs by:

#. Determining the connectivity of the ChemicalSystem
#. Fragmenting the resulting molecular graph
#. Find intersections for the fragments
#. Determine if bonds were broken
#. Cap the broken bonds

)";

MODULE_CTOR(Fragment) {
    description(mod_desc);
    satisfies_property_type<frags_pt>();

    // Inputs/modules controlling
    add_input<n_type>("n").set_default(n_type(1));
    add_submodule<graph2frags_pt>("N-mer builder");
    add_submodule<graph2frags_pt>("Fragment builder");

    add_submodule<conn_pt>("Atomic connectivity");
    add_submodule<graph_pt>("Molecular graph");
    add_submodule<intersections_pt>("Intersection finder");
    add_submodule<broken_bonds_pt>("Find broken bonds");
    add_submodule<cap_pt>("Cap broken bonds");
}

MODULE_RUN(Fragment) {
    auto n = inputs.at("n").value<n_type>();

    pluginplay::Module frags_mod;

    if(n == 1) {
        frags_mod = submods.at("Fragment builder").value();
    } else {
        frags_mod = submods.at("N-mer builder").value().unlocked_copy();
        frags_mod.change_input("n", n);
    }

    const auto& [mol] = frags_pt::unwrap_inputs(inputs);
    auto& runtime     = get_runtime();

    auto& conn_mod           = submods.at("Atomic connectivity");
    const auto& atomic_conns = conn_mod.run_as<conn_pt>(mol.molecule());

    // Step 1: Form the molecular graph
    auto& graph_mod    = submods.at("Molecular Graph");
    const auto& graph  = graph_mod.run_as<graph_pt>(mol);
    const auto n_nodes = graph.nodes_size();
    const auto n_edges = graph.edges_size();
    runtime.logger().debug("Created a graph with " + std::to_string(n_nodes) +
                           " nodes and " + std::to_string(n_edges) + " edges.");

    // Step 2: Use the graph to make fragments
    const auto& frags_no_ints = frags_mod.run_as<graph2frags_pt>(graph);
    const auto n_frags        = frags_no_ints.size();
    runtime.logger().debug("Created " + std::to_string(n_frags) +
                           " fragments.");

    // Step 3: Analyze the fragments for intersections
    auto& intersect_mod = submods.at("Intersection finder");
    const auto& frags   = intersect_mod.run_as<intersections_pt>(frags_no_ints);
    const auto n_ints   = frags.size() - n_frags;
    runtime.logger().debug("Added " + std::to_string(n_ints) +
                           " intersections.");

    // Step 4: Did forming fragments (or intersections) break bonds?
    auto& bonds_mod = submods.at("Find broken bonds");
    const auto& broken_bonds =
      bonds_mod.run_as<broken_bonds_pt>(frags, atomic_conns);
    runtime.logger().debug("Found " + std::to_string(broken_bonds.size()) +
                           " broken bonds.");

    // Step 5: Fix those broken bonds!!!!
    auto& cap_mod            = submods.at("Cap broken bonds");
    const auto& capped_frags = cap_mod.run_as<cap_pt>(frags, broken_bonds);
    const auto n_caps        = capped_frags.cap_set().size();
    runtime.logger().debug("Added " + std::to_string(n_caps) + " caps.");

    auto rv = results();
    return frags_pt::wrap_results(rv, capped_frags);
}

} // namespace ghostfragment::drivers
