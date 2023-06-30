#pragma once
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/capping/cap_set.hpp>
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
    using traits_type = MultiplicityAssignerTraits;
    using frag_type = traits_type::frag_type;
    using cap_type = traits_type::cap_type;
    using mol_type = traits_type::mol_type;

    return pluginplay::declare_input()
            .add_field<frag_type>("Fragments to assign multiplicity")
            .template add_field<cap_type>("Set of caps")
            .template add_field<mol_type>("The original molecule");

}

PROPERTY_TYPE_RESULTS(MultiplicityAssigner) {
    using traits_type = MultiplicityAssignerTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>("Charge for each fragment");
}

} // namespace ghostfragment::pt