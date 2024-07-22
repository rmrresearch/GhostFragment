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
using frag_set          = std::vector<index_set>;

namespace {
void compute_intersection(const index_set& curr_frag, std::size_t starting_frag,
                          const frag_set& frag_indices,
                          intersection_set& ints_so_far) {
    while(starting_frag < frag_indices.size()) {
        index_set intersection;
        const index_set& next_frag = frag_indices[starting_frag];
        auto itr = std::inserter(intersection, intersection.begin());
        std::set_intersection(curr_frag.begin(), curr_frag.end(),
                              next_frag.begin(), next_frag.end(), itr);
        ++starting_frag;
        // If it's empty and/or we've seen it befor just move on
        if(intersection.empty() || ints_so_far.count(intersection)) continue;

        // Add the intersection
        ints_so_far.insert(intersection);

        compute_intersection(intersection, starting_frag, frag_indices,
                             ints_so_far);
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
    auto& logger = get_runtime().logger();
    auto [frags] = property_type::unwrap_inputs(inputs);

    // It's much easier to work with nuclear indices
    std::vector<index_set> frag_indices;

    for(size_type i = 0; i < frags.size(); ++i) {
        const auto frag_i = frags.nuclear_indices(i);
        std::string frag_str;
        for(auto x : frag_i) frag_str += std::to_string(x) + ",";
        frag_str.pop_back();
        logger.debug("Input fragment: " + frag_str);
        frag_indices.emplace_back(frag_i.begin(), frag_i.end());
    }

    std::set<index_set> intersections;

    for(decltype(frags.size()) begin = 0; begin < frags.size(); ++begin) {
        const index_set& frag = frag_indices[begin];
        compute_intersection(frag, begin + 1, frag_indices, intersections);
    }

    for(const auto& intersection_i : intersections) {
        std::string int_str;
        for(auto x : intersection_i) int_str += std::to_string(x) + ",";
        int_str.pop_back();
        logger.debug("Found intersection: " + int_str);
        frags.insert(intersection_i.begin(), intersection_i.end());
    }

    auto rv = results();
    return property_type::wrap_results(rv, frags);
}

} // namespace ghostfragment::fragmenting
