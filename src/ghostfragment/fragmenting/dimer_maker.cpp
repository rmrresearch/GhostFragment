#include "fragmenting.hpp"

#include <ghostfragment/property_types/property_types.hpp>
#include <ghostfragment/property_types/fragmented_nuclei.hpp>

namespace ghostfragment::fragmenting {

// This function takes as argument a FragmentedNuclei object, and returns
// a FragmentedNuclei object consisting of all possible pairs of fragments.
chemist::FragmentedNuclei nuke_pairs(const chemist::FragmentedNuclei& frags) {
    chemist::FragmentedNuclei pairs(frags.supersystem());
    std::vector<std::size_t> indices;

    for(std::size_t frag_i = 0; frag_i < frags.size(); ++ frag_i) {
        for(std::size_t frag_j = frag_i + 1; frag_j < frags.size(); ++ frag_j) {
            for(const auto atom_i : frags[frag_i]) {
                indices.push_back(atom_i);
            }
            for(const auto atom_j : frags[frag_j]) {
                indices.push_back(atom_j);
            }
            pairs.add_fragment(indices.begin(), indices.end());
            indices.clear();
        }
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