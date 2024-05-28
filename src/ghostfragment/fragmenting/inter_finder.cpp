#include "inter_finder.hpp"
// #include <algorithm>
// #include <chemist/nucleus/fragmented_nuclei.hpp>
// #include <cstdlib>
// #include <iostream>

namespace ghostfragment::fragmenting {

using traits_type       = IntersectionTraits;
using fragments_type    = typename traits_type::input_type;
using result_type       = typename traits_type::result_type;
using nuclear_index_set = typename fragments_type::nucleus_index_set;
using size_type         = typename nuclear_index_set::size_type;

using index_set        = std::set<size_type>;
using intersection_set = std::set<index_set>;

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

result_type intersections(fragments_type frags) {
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

    return frags;
}

} // namespace ghostfragment::fragmenting
