#include "drivers.hpp"

#include "ghostfragment/property_types/property_types.hpp"

namespace ghostfragment::drivers {

using my_pt               = ghostfragment::pt::NMers;
using capped_fragments_pt = ghostfragment::pt::CappedFragments;
using screener_pt         = ghostfragment::pt::NMerScreener;

const auto mod_desc = R"(
NMer Driver
-----------

This module wraps the general process of going from a
``simde::type::fragmented_molecule_object`` to a ``ghostfragment::type::nmers``.
This has two major steps:

#. Cap the input fragments
#. Screen unions of the capped fragments

Since it makes taking unions of fragments easier, the input fragments have not
been capped. However, for most screening methods caps are needed. Thus the first
step is to cap the fragments. These caps will not be on the returned NMers, the
caps are only used internally for the screening process. Once we have capped the
fragments, we form the nmers, and finally return the nmers which survive the
screening process.
)";

MODULE_CTOR(NMer) {
    description(mod_desc);
    satisfies_property_type<my_pt>();

    add_submodule<capped_fragments_pt>("Capper");
    add_submodule<screener_pt>("Screener");

    add_input<unsigned>("N-Mer Truncation Order");
}

MODULE_RUN(NMer) {
    const auto& [frags] = my_pt::unwrap_inputs(inputs);
    const auto N        = frags.size();
    const auto n        = inputs.at("N-Mer Truncation Order").value<unsigned>();

    // Basic error checking
    if(N < n)
        throw std::runtime_error("Can not create " + std::to_string(n) +
                                 "-mers with only " + std::to_string(N) +
                                 " fragments.");

    // n == 0 and n == 1 edge cases
    if(n < 2) {
        type::nmers nmers(frags);

        if(n == 1) {
            for(std::size_t i = 0; i < N; ++i) {
                auto frag = nmers.new_subset();
                frag.insert(i);
                nmers.insert(frag);
            }
        }
        auto rv = results();
        return my_pt::wrap_results(rv, nmers);
    }

    // 1. Cap the Fragments
    auto& cap_mod              = submods.at("Capper");
    const auto& [capped_frags] = cap_mod.run_as<capped_fragments_pt>(frags);

    // 2. Screen the nmers
    auto& screen_mod    = submods.at("Screener");
    const auto& [nmers] = screen_mod.run_as<screener_pt>(capped_frags, n);

    auto rv = results();
    return my_pt::wrap_results(rv, nmers);
}

} // namespace ghostfragment::drivers
