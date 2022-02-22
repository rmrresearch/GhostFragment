#include "capping.hpp"

#include "ghostfragment/property_types/capped.hpp"

namespace ghostfragment::capping {

using my_pt  = pt::CappedNMers;
using cap_pt = pt::CappedFragments;

namespace {
constexpr auto module_desc = R"""(
###########
NMer Capper
###########

AFAIK most capping methods are defined for fragments and the generalization to
n-mers is assumed. This module assumes this is the case and ultimately calls a
capping routine which works on fragments. Thus this module actually caps the
n-mers by:

#. flattening each n-mer to a fragment,
#. capping the flattened n-mer as if it was a fragment,
#. mapping the flattened n-mer back to the n-mer, and then
#. associating the caps with the n-mer.

"Flattening" in this context refers to making the n-mers look like fragments.
More specifically fragments are stored as sets of atoms, whereas n-mers are
stored as sets of fragments. Flattening occurs by mapping each fragment in an
n-mer to the set of atoms comprising that fragment, and taking the union of all
such sets of atoms.
)""";

}

MODULE_CTOR(NMer) {
    satisfies_property_type<my_pt>();

    add_submodule<cap_pt>("Fragment Capper");
}

MODULE_RUN(NMer) {
    using capped_frags_traits = pt::CappedFragmentsTraits;
    using frags_type = std::decay_t<typename capped_frags_traits::input_type>;
    using frag_type  = typename frags_type::value_type;

    using capped_nmers_traits = pt::CappedNMersTraits;
    using nmers_type  = std::decay_t<typename capped_nmers_traits::input_type>;
    using nmer_type   = typename nmers_type::value_type;
    using return_type = typename capped_nmers_traits::result_type;

    const auto& [nmers] = my_pt::unwrap_inputs(inputs);
    const auto& frags   = nmers.object();

    // Step 1. Flatten n-mers (also track which n-mer makes which fragment)
    frags_type flattened_nmers(frags.object());
    std::map<nmer_type, frag_type> nmer2frag;
    for(const auto& nmer : nmers) {
        auto frag = flattened_nmers.new_subset();
        for(const auto& i : nmer) frag += frags[i];
        nmer2frag.emplace(nmer, frag);
        flattened_nmers.insert(frag);
    }

    // Step 2. Cap the flattened n-mers
    auto& submod               = submods.at("Fragment Capper");
    const auto& [capped_frags] = submod.run_as<cap_pt>(flattened_nmers);

    // Step 3. Map the flattened n-mers back to n-mers (and associate caps)
    return_type capped_nmers;
    for(const auto& nmer : nmers)
        capped_nmers.emplace(nmer, capped_frags.at(nmer2frag.at(nmer)));

    auto rv = results();
    return my_pt::wrap_results(rv, capped_nmers);
}

} // namespace ghostfragment::capping
