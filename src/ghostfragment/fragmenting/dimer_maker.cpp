#include "fragmenting.hpp"

#include <ghostfragment/property_types/property_types.hpp>
#include <ghostfragment/property_types/fragmented_nuclei.hpp>

namespace ghostfragment::fragmenting {

// Returns true if one vector is a subset of the other
bool is_subset(const std::vector<std::size_t>& subset, const std::vector<std::size_t>& vector) {
    std::unordered_set<std::size_t> uniqueVector(vector.begin(), vector.end());
    return std::all_of(subset.begin(), subset.end(), [&](const std::size_t& element) {
        return uniqueVector.count(element) > 0;
    });
}

// This function determines if a vector of indices is a subset of an existing fragment
bool is_contained(const std::vector<std::vector<std::size_t>> vecs, 
const std::vector<std::size_t> subset) {
    std::set<std::size_t> subset_elements(subset.begin(), subset.end());
    for(const auto& vector : vecs) {
        if(is_subset(subset, vector)) {
            return true;
        }
    }
    return false;
}

// This function returns the indices of all vectors that are subsets of the input vector
std::vector<std::size_t> subsets(const std::vector<std::vector<std::size_t>> vecs, 
const std::vector<std::size_t> input) {
    std::vector<std::size_t> indcs;
    for(std::size_t i = 0; i < vecs.size(); ++i) { 
        if(is_subset(vecs[i], input)) {
            if(input != vecs[i]) {
                indcs.push_back(i);
            }
        }
    }
    return(indcs);
}

// This function takes as argument a FragmentedNuclei object, and returns
// a FragmentedNuclei object consisting of all possible pairs of fragments.
chemist::FragmentedNuclei nuke_pairs(const chemist::FragmentedNuclei& frags) {
    chemist::FragmentedNuclei pairs(frags.supersystem());
    std::vector<std::vector<std::size_t>> indices;
    std::vector<std::size_t> single_frag;
    std::vector<std::size_t> indxs;

    for(std::size_t frag_i = 0; frag_i < frags.size(); ++ frag_i) {
        for(std::size_t frag_j = frag_i + 1; frag_j < frags.size(); ++ frag_j) {
            for(const auto atom_i : frags[frag_i]) {
                single_frag.push_back(atom_i);
            }
            for(const auto atom_j : frags[frag_j]) {
                single_frag.push_back(atom_j);
            }
            if(!is_contained(indices, single_frag)) {
                indices.push_back(single_frag);
            }
            indxs = subsets(indices, single_frag);
            std::sort(indxs.rbegin(), indxs.rend());
            for (std::size_t i = 0; i < indxs.size(); ++i) {
                std::size_t indx = indxs[indxs.size() - 1 - i];
                indices.erase(indices.begin() + indx);
            }
            single_frag.clear();
        }
    }

    for(std::size_t i = 0; i < indices.size(); ++i) {
        pairs.add_fragment(indices[i].begin(), indices[i].end());
    }

    return(pairs);
}

const auto mod_desc = R"(
    Fragmented Nuclei Dimer Generator
    --------------------------------

    This module takes as input a Molecule object, and returns a new
    FragmentedNuclei object consisting of every pair of fragments given as input.
    This first involves creating a FragmentedNuclei object of standard fragments
    via an existing FragmentedNuclei module called as a submod. Then, given
    a FragmentedNuclei object consisting of n fragments, this module
    will return the n choose 2 pairs of fragments as fragments themselves.
)";

using my_pt   = pt::FragmentedNuclei;
using frag_pt = pt::FragmentedNuclei;

MODULE_CTOR(DimerMaker) {
    description(mod_desc);

    satisfies_property_type<my_pt>();

    add_submodule<frag_pt>("Fragmentation");
}

MODULE_RUN(DimerMaker) {
    using result_type = pt::FragmentedNucleiTraits::result_type;
    using input_type  = pt::FragmentedNucleiTraits::system_type;

    const auto& [nuclei] = my_pt::unwrap_inputs(inputs);

    auto& frag_mod    = submods.at("Fragmentation");
    const auto& frags = frag_mod.run_as<frag_pt>(nuclei);

    chemist::FragmentedNuclei frag_pairs(nuke_pairs(frags));

    auto rv = results();
    return my_pt::wrap_results(rv, frag_pairs);
}

} // namespace ghostfragment