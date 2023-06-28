#pragma once
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

struct ChargeAssignerTraits {
    using system_type = chemist::FragmentedNuclei;

    using charge_type = chemist::Molecule::charge_type;
    using result_type = std::vector<charge_type>;
};

DECLARE_PROPERTY_TYPE(ChargeAssigner);

PROPERTY_TYPE_INPUTS(ChargeAssigner) {
    using traits_type = ChargeAssignerTraits;
    using input_type = traits_type::system_type;

    return pluginplay::declare_input().add_field<input_type>("Fragments to assign charge");
}

PROPERTY_TYPE_RESULTS(ChargeAssigner) {
    using traits_type = ChargeAssignerTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>{"Vector of charges for each fragment"};
}

} // namespace ghostfragment::pt