#pragma once
#include <chemist/chemical_system/chemical_system.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

/// Used to conveniently propagate types associated with FragmentedMolecule PT
struct InputQueueTraits {
    /// Expected input type of the molecular system
    using system_type = chemist::ChemicalSystem;

    /// How the fragmented system is returned.
    using result_type = std::vector<std::pair<chemist::ChemicalSystem, double>>;
};

/** @brief Property type for modules which fragment Molecule objects.
 *
 */
DECLARE_PROPERTY_TYPE(InputQueue);

PROPERTY_TYPE_INPUTS(InputQueue) {
    using traits_type = InputQueueTraits;
    using input0_type = traits_type::system_type;

    return pluginplay::declare_input().add_field<input0_type>(
      "Input Chemical System");
}

PROPERTY_TYPE_RESULTS(InputQueue) {
    using traits_type = InputQueueTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>(
      "Fragments and Weights");
}

} // namespace ghostfragment::pt