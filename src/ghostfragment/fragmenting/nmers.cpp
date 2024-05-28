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
#include <combinations.hpp>
#include <enumerate.hpp>
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
#include <numeric>
namespace ghostfragment::fragmenting {

using my_pt              = ghostfragment::pt::NuclearGraphToFragments;
using traits_type        = ghostfragment::pt::NuclearGraphToFragmentsTraits;
using nmers_type         = typename traits_type::fragment_type;
using nucleus_index_list = typename nmers_type::nucleus_index_set;
using index_type         = typename nucleus_index_list::value_type;
using n_type             = unsigned short;

const auto mod_desc = R"(
.. |n| replace:: :math:`n`

NMers
=====

Given a set of input fragments, this module will take all |n|-way unions of the
input fragments. This module works with both disjoint and intersecting
fragments. For intersecting fragments, this module will ensure that the
resulting set of |n|-mers are such that no |n|-mer is a subset of another
|n|-mer (notably this also guarantees their uniqueness).
)";

MODULE_CTOR(NMers) {
    description(mod_desc);
    satisfies_property_type<my_pt>();

    add_input<n_type>("n").set_description("The maximum n-mer size");
    add_submodule<my_pt>("Monomer maker");
}

MODULE_RUN(NMers) {
    const auto& [graph] = my_pt::unwrap_inputs(inputs);
    auto n              = inputs.at("n").value<n_type>();

    auto& monomer_mod = submods.at("Monomer maker");
    const auto& frags = monomer_mod.run_as<my_pt>(graph);

    auto n_frags = frags.size();

    if(n > n_frags)
        throw std::runtime_error("Cannot make " + std::to_string(n) +
                                 "-mers with only " + std::to_string(n_frags) +
                                 " fragments");

    // Initialize nmer container and container of fragment indices
    nmers_type nmers(frags.supersystem().as_nuclei());

    std::vector<decltype(n_frags)> frag_indices(n_frags);
    std::iota(frag_indices.begin(), frag_indices.end(), 0);

    // Use a set of sets to avoid copies
    using index_set_type     = std::set<index_type>;
    using index_set_set_type = std::set<index_set_type>;

    index_set_set_type nmer_indices;

    // Make the mmers
    for(auto&& mmer : iter::combinations(frag_indices, n)) {
        index_set_type nuclear_indices;
        for(auto&& frag_index : mmer) {
            auto buffer = frags.nuclear_indices(frag_index);
            nuclear_indices.insert(buffer.begin(), buffer.end());
        }
        nmer_indices.insert(nuclear_indices);
    }

    // This block ensures we only add non subsets

    // This is used to avoid comparing against sets we know are subsets already
    std::vector<bool> i_is_good(nmer_indices.size(), true);

    for(const auto&& [i, nmer_i] : iter::enumerate(nmer_indices)) {
        // N.b. "x is not a subset of y" does NOT mean that
        // "y is not a subset of x", i.e., this loop must always consider the
        // full range.
        for(const auto&& [j, nmer_j] : iter::enumerate(nmer_indices)) {
            // Every set is a subset of itself, so skip i == j, also skip j if
            // we already know it's a subset of something else (i.e., if i was
            // going to be a subset of j, and j is a subset of say x, then i
            // is also going to be a subset of x)
            if(i == j || !i_is_good[j]) continue;

            // Checks if nmer_i is a subset of nmer_j
            if(std::includes(nmer_j.begin(), nmer_j.end(), nmer_i.begin(),
                             nmer_i.end())) {
                i_is_good[i] = false;
                break; // Early out b/c it's a subset
            }
        }
        if(i_is_good[i]) nmers.insert(nmer_i.begin(), nmer_i.end());
    }

    auto rv = results();
    return my_pt::wrap_results(rv, nmers);
}

} // namespace ghostfragment::fragmenting
