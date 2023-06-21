#pragma once
#include <chemist/molecule/fragmented_molecule.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

/// Used to conveniently propagate types associated with FragmentedMolecule PT
struct FragmentedMoleculeTraits {
    /// Expected input type of the molecular system
    using system_type = chemist::Molecule;

    /// How the fragmented system is returned.
    using result_type = chemist::FragmentedMolecule;
};

/** @brief Property type for modules which fragment Molecule objects.
 *
 */
DECLARE_PROPERTY_TYPE(FragmentedMolecule);

PROPERTY_TYPE_INPUTS(FragmentedMolecule) {
    using traits_type = FragmentedMoleculeTraits;
    using input0_type = traits_type::system_type;

    return pluginplay::declare_input().add_field<input0_type>(
      "System to fragment");
}

PROPERTY_TYPE_RESULTS(FragmentedMolecule) {
    using traits_type = FragmentedMoleculeTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>(
      "Fragmented Molecule");
}

} // namespace ghostfragment::pt
