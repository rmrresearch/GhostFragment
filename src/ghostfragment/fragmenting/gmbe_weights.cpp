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
#include <algorithm>
#include <ghostfragment/property_types/fragmenting/fragment_weights.hpp>

namespace ghostfragment::fragmenting {

using my_pt               = pt::FragmentWeights;
using traits_type         = pt::FragmentWeightsTraits;
using weight_container    = typename traits_type::weight_container;
using fragmented_sys_type = typename traits_type::fragments_type;
using fragmented_mol_type =
  typename fragmented_sys_type::fragmented_molecule_type;
using fragmented_nuclei_type =
  typename fragmented_mol_type::fragmented_nuclei_type;
using nucleus_index_set = typename fragmented_nuclei_type::nucleus_index_set;
using index_type        = typename nucleus_index_set::value_type;
using size_type         = typename fragmented_nuclei_type::size_type;
using index_set         = std::set<index_type>;
using index_set_to_frag = std::map<index_set, size_type>;
using length_to_map     = std::map<size_type, index_set_to_frag>;

namespace {

const auto mod_desc = R"(
GMBE Fragment Weights
---------------------

Given the list of subsystems (subsystem being defined as either a fragment or an
intersection) this module will determine the weights of each subsystem. This
module will NOT add intersections to the input list.

This module adopts the algorithm from DOI:10.1021/jp103074f. More specifically,
each subsystem with :math:`\eta` nuclei in it represents an :math:`eta`-body
interaction. Each :math:`\eta`-body interaction should only occur once when we
sum up the subsystems. Therefore the coefficient of the :math:`i`-th subsystem
is :math:`c_i = 1-\sum_{j\supset i}c_j` where the sum is over the weights of
the proper supersets of the :math:`i`-th subsystem.

While the non-linear nature of the weights may seem troubling at first, we can
exploit the fact that a proper superset must have more members. More
specifically, if we start with the supersystem(s) with the most members we know
they have weights of 1 because they can't be subsets of any other subsystem. We
can then move on to the next largest subsystem(s) which can only be subsets of
the largest subsystem(s). The process then continues with the next largest
subsystem(s), so on and so forth. More formally:

#. Sort subsystems by length (remembering their original offset)
#. Let :math:`\eta` be the length of the largest subsystem(s)
#. Set :math:`n` to :math:`\eta`
#. Let :math:`c^n_i` be the weight for the :math:`i`-th subsystem of length
   :math:`n`; set :math:c^n_i: to 1.0.
#. Loop over subsystem lengths :math:`m` such that :math:`m>n`.

   #. Loop over subsystems of length :math:`m`, if the :math:`j`-th subsystem of
      length :math:`m` is a supersystem of the :math:`i`-th subsystem of length
       :math:`n` subtract :math:`c^m_j` from :math:`c^n_i`

#. Set :math:`n` to :math:`n-1`. If :math:`n` is 0 terminate, otherwise return
   to step 4.
)";

template<typename SetType>
bool is_subset(const SetType& superset, const SetType& subset) {
    return std::includes(superset.begin(), superset.end(), subset.begin(),
                         subset.end());
}

} // namespace

MODULE_CTOR(GMBEWeights) {
    description(mod_desc);
    satisfies_property_type<my_pt>();
}

MODULE_RUN(GMBEWeights) {
    const auto& [fragmented_sys]    = my_pt::unwrap_inputs(inputs);
    const auto& fragmented_molecule = fragmented_sys.fragmented_molecule();
    const auto& fragmented_nuclei   = fragmented_molecule.fragmented_nuclei();

    length_to_map sorted_frags;
    std::set<size_type> nnuclei;
    for(size_type frag_i = 0; frag_i < fragmented_nuclei.size(); ++frag_i) {
        auto buffer = fragmented_nuclei.nuclear_indices(frag_i);
        index_set indices(buffer.begin(), buffer.end());
        sorted_frags[buffer.size()][indices] = frag_i;
        nnuclei.insert(buffer.size());
    }

    weight_container weights(fragmented_nuclei.size(), 0.0);

    // N.B. use of rbegin/rend to start with largest fragment
    auto subset_size = nnuclei.rbegin();
    auto smallest    = nnuclei.rend();

    while(subset_size != smallest) {
        for(const auto& [subset, i] : sorted_frags[*subset_size]) {
            // Final weight is equal to 1 minus the weight of each parent's
            // weight
            weights[i] = 1.0;

            // N.b. starting at the end again
            auto parent_size = nnuclei.rbegin();
            while(parent_size != subset_size) {
                for(const auto& [superset, j] : sorted_frags[*parent_size]) {
                    if(is_subset(superset, subset)) weights[i] -= weights[j];
                }
                ++parent_size;
            }
        }
        ++subset_size;
    }

    auto rv = results();
    return my_pt::wrap_results(rv, weights);
}

} // namespace ghostfragment::fragmenting
