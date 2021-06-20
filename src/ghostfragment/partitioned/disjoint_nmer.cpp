#include "../modules.hpp"
#include "ghostfragment/property_types/property_types.hpp"
#include <utilities/iter_tools/combinations.hpp>

namespace ghostfragment {

using n_type = std::size_t;

const auto mod_desc = R"(
.. |n| replace:: :math:`n`

NMer Generator for Disjoint Fragments
=====================================

Given a set of input fragments, this module will take unions of the input
fragments to generate all dimers, trimers, on up to |n|-mers where the value of
|n| is controlled by the user.
)";

MODULE_CTOR(DisjointNMerGenerator) {
    description(mod_desc);
    satisfies_property_type<pt::nmer_maker>();

    add_input<n_type>("n").set_description("The maximum n-mer size");
}

MODULE_RUN(DisjointNMerGenerator) {
    auto [frags] = pt::nmer_maker::unwrap_inputs(inputs);
    auto n       = inputs.at("n").value<n_type>();
    type::fragmented_molecule nmers(frags);

    auto rv = results();
    return pt::nmer_maker::wrap_results(rv, nmers);
}

} // namespace ghostfragment