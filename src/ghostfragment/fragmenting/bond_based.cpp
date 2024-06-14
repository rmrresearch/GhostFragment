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

#include "fragmenting.hpp"
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
#include <simde/simde.hpp>

namespace ghostfragment::fragmenting {

using my_pt       = pt::NuclearGraphToFragments;
using result_type = pt::NuclearGraphToFragmentsTraits::fragment_type;
using subset_type = typename result_type::nucleus_index_set;
using input_type  = pt::NuclearGraphToFragmentsTraits::graph_type;
using nuclei_type = typename input_type::nuclei_type;

// This function takes a NuclearGraph, a node and a parameter nbonds and returns
// all nuclei that are within nbonds bonds of the given node. Uses a stack
// node_stack to perform a depth-first search, where the elements of node_stack
// are pairs containing the indices of nodes and their distance from the root
// node. The function loops over the stack, adding the nodes with distance <=
// nbonds to a set.

subset_type frag_nodes(const NuclearGraph& graph, std::size_t root_node,
                       std::size_t nbonds) {
    const auto& bonds = graph.edge_list();
    using size_type   = typename subset_type::value_type;
    std::unordered_map<size_type, size_type> distance;
    std::stack<std::pair<size_type, size_type>> node_stack;

    node_stack.push(std::make_pair(root_node, 0));
    distance[root_node] = 0;

    while(!node_stack.empty()) {
        size_type current_node     = node_stack.top().first;
        size_type current_distance = node_stack.top().second;
        node_stack.pop();

        if(current_distance >= nbonds) {
            continue; // Skip if node is beyond distance nbonds
        }

        for(auto bond : bonds) {
            if(bond[0] == current_node) { // If first index is current node
                size_type next_node = bond[1];
                if(distance.count(next_node) == 0 ||
                   distance[next_node] > current_distance + 1) {
                    distance[next_node] = current_distance + 1;
                    node_stack.push(
                      std::make_pair(next_node, current_distance + 1));
                }
            }

            if(bond[1] == current_node) { // If second index is current node
                size_type next_node = bond[0];
                if(distance.count(next_node) == 0 ||
                   distance[next_node] > current_distance + 1) {
                    distance[next_node] = current_distance + 1;
                    node_stack.push(
                      std::make_pair(next_node, current_distance + 1));
                }
            }
        }
    }

    // Convert nodes (which could consist of multiple nuclei) to their
    // constituent nuclei
    std::set<size_type> buffer;
    for(const auto& entry : distance) {
        std::size_t node = entry.first;
        for(std::size_t j : graph.node_indices(node)) { buffer.insert(j); }
    }
    return subset_type(buffer.begin(), buffer.end());
}

// This function takes a MolecularGraph and a parameter nbonds, and loops
// over all nodes in MolecularGraph, calling frag_nodes for each. If the set
// of indices is novel, then it is added to a vector of sets to be returned.

std::vector<subset_type> graph_to_frags(const NuclearGraph& graph,
                                        std::size_t nbonds) {
    using return_type = std::vector<subset_type>;
    using size_type   = typename subset_type::value_type;
    return_type indices; // vector of sets of indices denoting fragments
    subset_type current_frag;
    size_type supersets = 0;
    size_type subsets   = 0;

    for(size_type i = 0; i < graph.nodes_size(); ++i) {
        auto current_frag = frag_nodes(graph, i, nbonds);
        size_type j       = 0;
        while(j < indices.size()) {
            if(std::includes(indices[j].begin(), indices[j].end(),
                             current_frag.begin(), current_frag.end())) {
                supersets++;
            }
            if(std::includes(current_frag.begin(), current_frag.end(),
                             indices[j].begin(), indices[j].end())) {
                indices.erase(indices.begin() + j);
                j--;
                subsets++;
            }
            j++;
        }

        if(supersets == 0) {
            indices.push_back(current_frag);
        } else if(subsets > 0) {
            indices.push_back(current_frag);
        }

        supersets = 0;
        subsets   = 0;
    }
    return indices;
}

const auto mod_desc = R"(
Bond-Based Fragmenter
-------------------

This module takes as input a MolecularGraph representation of the molecular
system and an integer parameter nbonds, and outputs a FragmentedNuclei
object. The fragments are generated by looping over the nodes in
MolecularGraph and assembling all nodes a distance of nbonds or less away
from the node in question into a fragment. Each distinct fragment will be
output exactly once (i.e. no repeats).
)";

MODULE_CTOR(BondBased) {
    description(mod_desc);
    satisfies_property_type<my_pt>();

    add_input<std::size_t>("nbonds")
      .set_description("bond width of fragment")
      .set_default(std::size_t(0));
}

MODULE_RUN(BondBased) {
    const auto& [graph] = my_pt::unwrap_inputs(inputs);
    const auto& nbonds  = inputs.at("nbonds").value<std::size_t>();

    if(graph.nodes_size() == 0) { // Handles trivial mol edge-case
        auto rv = results();
        return my_pt::wrap_results(rv, result_type{nuclei_type{}});
    }

    result_type frags(graph.nuclei().as_nuclei()); // Will be the fragments

    const auto indices = graph_to_frags(graph, nbonds);

    for(std::size_t i = 0; i < indices.size(); ++i) {
        frags.insert(indices[i].begin(), indices[i].end());
    }

    auto rv = results();
    return my_pt::wrap_results(rv, frags);
}

} // namespace ghostfragment::fragmenting
