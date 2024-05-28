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
#include <ghostfragment/property_types/fragmenting/intersections.hpp>

namespace ghostfragment::fragmenting {

using property_type     = pt::Intersections;
using traits_type       = pt::IntersectionTraits;
using fragments_type    = typename traits_type::input_type;
using result_type       = typename traits_type::result_type;
using nuclear_index_set = typename fragments_type::nucleus_index_set;
using size_type         = typename nuclear_index_set::size_type;
using index_set         = std::set<size_type>;
using intersection_set  = std::set<index_set>;

namespace {
template<typename BeginItr, typename EndItr>
void compute_intersection(const index_set& curr_frag, BeginItr&& starting_frag,
                          EndItr&& end_itr, intersection_set& ints_so_far) {
    while(starting_frag != end_itr) {
        index_set intersection;
        auto itr = std::inserter(intersection, intersection.begin());
        std::set_intersection(curr_frag.begin(), curr_frag.end(),
                              starting_frag->begin(), starting_frag->end(),
                              itr);
        ++starting_frag;
        // If it's empty and/or we've seen it befor just move on
        if(intersection.empty() || ints_so_far.count(intersection)) continue;

        // Add the intersection
        ints_so_far.insert(intersection);

        // Copy iterator so we leave starting_frag unchanged when we recurse
        decltype(starting_frag) new_begin(starting_frag);
        compute_intersection(intersection, new_begin, end_itr, ints_so_far);
    }
}

const auto mod_desc = R"(
Intersections by Recursion
--------------------------

This module finds the intersections of a set of fragments via recursion.
)";
} // namespace

MODULE_CTOR(IntersectionsByRecursion) {
    description(mod_desc);

    satisfies_property_type<property_type>();
}

MODULE_RUN(IntersectionsByRecursion) {
    auto [frags] = property_type::unwrap_inputs(inputs);

    // It's much easier to work with nuclear indices
    std::vector<index_set> frag_indices;

    for(size_type i = 0; i < frags.size(); ++i) {
        const auto frag_i = frags.nuclear_indices(i);
        frag_indices.emplace_back(frag_i.begin(), frag_i.end());
    }

    std::set<index_set> intersections;

    auto begin = frag_indices.begin();
    auto end   = frag_indices.end();

    while(begin != end) {
        index_set frag = *begin;
        ++begin;
        decltype(begin) begin_copy(begin);
        compute_intersection(frag, begin_copy, end, intersections);
    }

    for(const auto& intersection_i : intersections)
        frags.insert(intersection_i.begin(), intersection_i.end());

    auto rv = results();
    return property_type::wrap_results(rv, frags);
}

} // namespace ghostfragment::fragmenting
