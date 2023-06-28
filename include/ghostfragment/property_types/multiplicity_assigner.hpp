#pragma once
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

struct MultiplicityAssignerTraits {
    using system_type = chemist::FragmentedNuclei;

    using size_type = chemist::Molecule::size_type;
    using result_type = std::vector<size_type>;
};

DECLARE_PROPERTY_TYPE(MultiplicityAssigner);

PROPERTY_TYPE_INPUTS(MultiplicityAssigner) {
    using traits_type = MultiplicityAssignerTraits;
    using input_type = traits_type::system_type;

    return pluginplay::declare_input().add_field<input_type>("Fragments to assign multiplicity");
}

PROPERTY_TYPE_RESULTS(MultiplicityAssigner) {
    using traits_type = MultiplicityAssignerTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>{"Vector of multiplicities for each fragment"};
}

} // namespace ghostfragment::pt