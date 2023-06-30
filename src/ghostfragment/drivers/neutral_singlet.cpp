#include "drivers.hpp"
#include <ghostfragment/property_types/charge_multiplicity_assigner.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <chemist/capping/cap_set.hpp>

using my_pt = ghostfragment::pt::ChargeMultiplicityAssigner;
using traits_t = ghostfragment::pt::ChargeMultiplicityAssignerTraits;

namespace ghostfragment::drivers {

namespace {
constexpr auto module_desc = R"""(
#######################
Neutral Singlet Charge Assigner
#######################

This module assigns a charge of zero
and a multiplicity of one to each input fragment.

The inputs to this module are fragments, a cap set, and the original molecule.
)""";
} // end namespace

MODULE_CTOR(NeutralSinglet) {
    satisfies_property_type<my_pt>();
}

MODULE_RUN(NeutralSinglet) {
    const auto& [frags, caps, mol] = my_pt::unwrap_inputs(inputs);

    using charge_result_type = traits_t::charge_result_type;
    using mult_result_type = traits_t::mult_result_type;
    // Charge vector is only populated with 0s
    charge_result_type charges(frags.size(), 0);
    mult_result_type multiplicities;


    // Goes over every fragment and attempts
    // to set each one's multiplicity to one.
    for(auto frag_i = 0; frag_i < frags.size(); frag_i++) {
        // Keeps track of the number of electrons in each fragment
        auto num_electrons = 0;

        // Adds the electrons from the original atoms in the fragment
        const auto& nukes = frags[frag_i];
        for(auto atom_i = 0; atom_i < nukes.size(); atom_i++) {
            num_electrons += nukes[atom_i].Z();
        }

        // Adds the electrons from the caps in the fragment
        const auto& cap_set = caps[frag_i];
        for(auto cap_i = 0; cap_i < cap_set.size(); cap_i++) {
            const auto& cap = cap_set[cap_i];
            for(auto atom_i = 0; atom_i < cap.size(); atom_i++) {
                num_electrons += cap.cap_atom(atom_i).Z();
            }
        }

        // Even number of electrons which means multiplicity can be one.
        if(num_electrons % 2 == 0) {
            multiplicities.push_back(1);
        }

        // With an odd number of electrons, a multiplicity of one is impossible
        else {
            throw std::runtime_error("An odd number of electrons cannot have multiplicity of one");
        }
    }

    auto rv = results();
    return my_pt::wrap_results(rv, charges, multiplicities);
}
} // namespace ghostfragment::drivers