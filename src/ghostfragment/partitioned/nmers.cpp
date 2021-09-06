#include "../modules.hpp"
#include "ghostfragment/types.hpp"
#include <simde/simde.hpp>
#include <utilities/iter_tools/combinations.hpp>

namespace ghostfragment {

using n_type = std::size_t;

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

using pt = simde::NMers;

MODULE_CTOR(NMers) {
    description(mod_desc);
    satisfies_property_type<pt>();

    add_input<n_type>("n").set_description("The maximum n-mer size");
}

MODULE_RUN(NMers) {
    using nmer_type = typename type::nmers::value_type;

    // Unpack inputs
    const auto& [frags] = pt::unwrap_inputs(inputs);
    auto n              = inputs.at("n").value<n_type>();
    if(n > frags.size())
        throw std::runtime_error("Cannot make " + std::to_string(n) +
                                 "-mers with only " +
                                 std::to_string(frags.size()) + " fragments");

    // Initialize nmer container and container of fragment indices
    type::nmers nmers(frags);
    auto n_frags = frags.size();
    std::vector<decltype(n_frags)> frag_indices(n_frags);
    std::iota(frag_indices.begin(), frag_indices.end(), 0);

    // Make the mmers
    for(decltype(n) m = 1; m <= n; ++m) {
        for(auto mmer : utilities::Combinations(frag_indices, m)) {
            nmer_type temp(nmers.data(), mmer.begin(), mmer.end());
            nmers.insert(temp);
        }
    }

    auto rv = results();
    return pt::wrap_results(rv, nmers);
}

} // namespace ghostfragment