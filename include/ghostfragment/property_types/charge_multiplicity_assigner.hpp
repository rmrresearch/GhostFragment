#pragma once
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/capping/cap_set.hpp>
#include <chemist/capping/cap.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

struct ChargeMultiplicityAssignerTraits {
    using frag_type = chemist::FragmentedNuclei;
    using cap_type = std::vector<chemist::CapSet>;
    using mol_type = chemist::Molecule;

    using charge_type = mol_type::charge_type;
    using charge_result_type = std::vector<charge_type>;

    using size_type = mol_type::size_type;
    using mult_result_type = std::vector<size_type>;
};

DECLARE_PROPERTY_TYPE(ChargeMultiplicityAssigner);

PROPERTY_TYPE_INPUTS(ChargeMultiplicityAssigner) {
    using traits_type = ChargeMultiplicityAssignerTraits;
    using frag_type = traits_type::frag_type;
    using cap_type = traits_type::cap_type;
    using mol_type = traits_type::mol_type;

    return pluginplay::declare_input()
            .add_field<frag_type>("Fragments")
            .template add_field<cap_type>("Set of caps")
            .template add_field<mol_type>("The original molecule");

}

PROPERTY_TYPE_RESULTS(ChargeMultiplicityAssigner) {
    using traits_type = ChargeMultiplicityAssignerTraits;
    using charge_result_type = traits_type::charge_result_type;
    using mult_result_type = traits_type::mult_result_type;

    return pluginplay::declare_result()
        .add_field<charge_result_type>("Charge for each fragment")
        .template add_field<mult_result_type>("Mult for each fragment");
}

} // namespace ghostfragment::pt