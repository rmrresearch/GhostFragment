#pragma once
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

/// Used to conveniently propagate types associated with FragmentedNuclei PT
struct FragmentedNucleiTraits {
    /// Expected input type of the molecular system
    using system_type = chemist::ChemicalSystem;

    /// How the fragmented system is returned.
    using result_type = chemist::FragmentedNuclei;
};

/** @brief Property type for modules which fragment Nuclei objects.
 *
 */
DECLARE_PROPERTY_TYPE(FragmentedNuclei);

PROPERTY_TYPE_INPUTS(FragmentedNuclei) {
    using traits_type = FragmentedNucleiTraits;
    using input0_type = traits_type::system_type;

    return pluginplay::declare_input().add_field<input0_type>(
      "System to fragment");
}

PROPERTY_TYPE_RESULTS(FragmentedNuclei) {
    using traits_type = FragmentedNucleiTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>(
      "Fragmented Nuclei");
}

} // namespace ghostfragment::pt