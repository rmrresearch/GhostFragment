#pragma once
#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment {

/// Used to conveniently propagate types associated with FragmentedNuclei PT
struct FragmentedNucleiTraits {
    /// Expected input type of the molecular system
    using system_type = chemist::ChemicalSystem;

    /// How the fragmented system is returned.
    using result_type = chemist::fragmenting::FragmentedNuclei<chemist::Nuclei>;
};

/** @brief Property type for modules which fragment Nuclei objects.
 *
 */
DECLARE_PROPERTY_TYPE(FragmentedNuclei);

PROPERTY_TYPE_INPUTS(FragmentedNuclei) {
    using system_type = typename FragmentedNucleiTraits::system_type;
    using input0_type = chemist::ChemicalSystemView<const system_type>;

    return pluginplay::declare_input().add_field<input0_type>(
      "System to fragment");
}

PROPERTY_TYPE_RESULTS(FragmentedNuclei) {
    using traits_type = FragmentedNucleiTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>(
      "Fragmented Nuclei");
}

} // namespace ghostfragment
