#pragma once
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

struct MultiplicityAssignerTraits {
    using frag_type = chemist::FragmentedNuclei;
    using cap_type = std::vector<chemist::CapSet>;
    using mol_type = chemist::Molecule;

    using size_type = mol_type::size_type;
    using result_type = std::vector<size_type>;
};

DECLARE_PROPERTY_TYPE(MultiplicityAssigner);

PROPERTY_TYPE_INPUTS(MultiplicityAssigner) {
    using traits_type = ChargeAssignerTraits;
    using frag_type = traits_type::frag_type;
    using cap_type = traits_type::cap_type;
    using mol_type = traits_type::mol_type;

    return pluginplay::declare_input()
            .add_field<frag_type>("Fragments to assign multiplicity")
            .template add_field<caps_type>("Set of caps for each fragment")
            .template add_field<mol_type>("The original molecule");

}

PROPERTY_TYPE_RESULTS(MultiplicityAssigner) {
    using traits_type = MultiplicityAssignerTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>{"Vector of multiplicities for each fragment"};
}

} // namespace ghostfragment::pt