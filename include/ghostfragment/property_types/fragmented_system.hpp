#pragma once
#include "ghostfragment/fragmented_system.hpp"
#include <simde/simde.hpp>

namespace ghostfragment::pt {

/// Used to conviently propagate types associated with FragmentedSystem PT
struct FragmentedSystemTraits {
    /// Expected input type of the molecular system
    using system_type = simde::type::chemical_system;

    /// Expected input type of the molecular AO basis set
    using ao_basis_type = simde::type::ao_basis_set;

    /// How the fragmented system is returned.
    using result_type = ghostfragment::FragmentedSystem;
};

/** @brief Property type for modules which fragment inputs.
 *
 *  The typical input to a fragment-based method is: the chemical system and
 *  the AO basis set for the molecular system. This module is responsible for
 *  mapping that input to a FragmentedSystem instance. The FragmentedSystem
 *  instance contains:
 *
 *  - the fragments,
 *  - the molecular AO basis sets for those fragments, and
 *  - the number of electrons in each fragment
 *
 *
 *  It is assumed that modules satisfying the property type FragmentedSystem are
 *  driver-like (basically responsible for chaining together calls from several
 *  submodules); however, users may provide their own module which returns the
 *  FragmentedSystem using a different stategy.
 */
DECLARE_PROPERTY_TYPE(FragmentedSystem);

PROPERTY_TYPE_INPUTS(FragmentedSystem) {
    using traits_type = FragmentedSystemTraits;
    using input0_type = traits_type::system_type;
    using input1_type = traits_type::ao_basis_type;

    return pluginplay::declare_input()
      .add_field<input0_type>("Parent system")
      .template add_field<input1_type>("Molecular AO Basis Set");
}

PROPERTY_TYPE_RESULTS(FragmentedSystem) {
    using traits_type = FragmentedSystemTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>(
      "Fragmented System");
}

} // namespace ghostfragment::pt
