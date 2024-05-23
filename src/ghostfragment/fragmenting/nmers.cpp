#include "fragmenting.hpp"
#include <combinations.hpp>
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

Given a set of input fragments, this module will take unions of the input
fragments to generate **all** fragments, dimers, trimers, on up to |n|-mers
where the value of |n| is controlled by the user. This module works with both
disjoint and intersecting fragments; however, for non-disjoint fragments the
nmers may not be unique.
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

    // Make the mmers
    for(decltype(n) m = 1; m <= n; ++m) {
        for(auto&& mmer : iter::combinations(frag_indices, m)) {
            std::set<index_type> nuclear_indices;
            for(auto&& frag_index : mmer) {
                auto buffer = frags.nuclear_indices(frag_index);
                nuclear_indices.insert(buffer.begin(), buffer.end());
            }
            nmers.insert(nuclear_indices.begin(), nuclear_indices.end());
        }
    }

    auto rv = results();
    return my_pt::wrap_results(rv, nmers);
}

} // namespace ghostfragment::fragmenting
