#include "drivers.hpp"
#include <ghostfragment/property_types/charge_assigner.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <chemist/capping/cap_set.hpp>

using my_pt = ghostfragment::pt::ChargeAssigner;
using traits_t = ghostfragment::pt::ChargeAssignerTraits;

namespace ghostfragment::drivers {

namespace {
constexpr auto module_desc = R"""(
#######################
Neutral Charge Assigner
#######################

This module assigns a charge of zero to each input fragment.

The inputs to this module are fragments, a cap set, and the original molecule.
)""";
} // end namespace

MODULE_CTOR(Neutral) {
    satisfies_property_type<my_pt>();
}

MODULE_RUN(Neutral) {
    const auto& [frags, caps, mol] = my_pt::unwrap_inputs(inputs);

    using result_type = traits_t::result_type;
    result_type charges;

    // Simply sets each fragment's charge to zero
    for(const auto& frag_i : frags) {
        charges.push_back(0);
    }

    auto rv = results();
    return my_pt::wrap_results(rv, charges);
}
} // namespace ghostfragment::drivers