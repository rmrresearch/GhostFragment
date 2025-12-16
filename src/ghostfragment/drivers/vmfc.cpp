/*
 * Copyright 2025 GhostFragment
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

#include "drivers.hpp"
#include "helpers.hpp"

#include <ghostfragment/property_types/fragmenting/fragmented_chemical_system.hpp>
namespace ghostfragment::drivers {

using my_pt       = simde::AOEnergy;
using fragment_pt = pt::FragmentedChemicalSystem;

namespace {
const auto mod_desc = R"(
VMFC Driver
-----------
Implements the Valiron-Mayer Function Counterpoise (VMFC) method.
)";

}

MODULE_CTOR(VMFC) {
    description(mod_desc);
    satisfies_property_type<my_pt>();
    add_submodule<my_pt>("Energy method");
    add_submodule<fragment_pt>("Fragment Driver");

    add_input<std::size_t>("Truncation order");
}

MODULE_RUN(VMFC) {
    const auto& [basis_set, sys] = my_pt::unwrap_inputs(inputs);
    const auto n = inputs.at("Truncation order").value<std::size_t>();

    // Step 1: Fragment system
    auto& fragment_mod    = submods.at("Fragment Driver");
    const auto& fragments = fragment_mod.run_as<fragment_pt>(sys);
    // TODO: Assert disjoint fragments
    // TODO: Assert no caps
    // TODO: Assert fragments.size() >= n

    // Step 2: Map basis functions to atoms
    auto bf_map = drivers::map_atomic_bases_to_atoms(sys, basis_set);

    // Step 3: Build inputs
    auto calcs = build_vmfc_ao_energy_inputs(n, basis_set, fragments, bf_map);

    // Step 4: Run calculations
    auto energy_mod = submods.at("Energy method");
    // TODO: Set Logger for energy_mod to not print anything
    simde::type::tensor energy(0.0);
    for(const auto& [desc, coefficient, sub_basis, sub_sys] : calcs) {
        simde::type::chemical_system temp_sys(sub_sys.molecule().as_molecule());
        auto sub_energy = energy_mod.run_as<my_pt>(sub_basis, temp_sys);
        simde::type::tensor buffer;
        buffer("") = sub_energy("") * coefficient;
        energy("") = energy("") + buffer("");
    }

    auto rv = results();
    return my_pt::wrap_results(rv, energy);
}

} // namespace ghostfragment::drivers