/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <chemist/fragmenting/fragmented_molecule.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

/// Used to conveniently propagate types associated with FragmentedMolecule PT
struct FragmentedMoleculeTraits {
    /// Expected input type of the molecular system
    using system_type = chemist::FragmentedNuclei;

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
      "FragmentedNuclei");
}

PROPERTY_TYPE_RESULTS(FragmentedMolecule) {
    using traits_type = FragmentedMoleculeTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>(
      "Fragmented Molecule");
}

} // namespace ghostfragment::pt
