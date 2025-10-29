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
#include <ghostfragment/property_types/fragmenting/fragmented_chemical_system.hpp>
namespace ghostfragment::drivers {

using my_pt = simde::AOEnergy;
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

    add_input<int>("Truncation order");
}

MODULE_RUN(VMFC){
    const auto& [basis_set, sys] = my_pt::unwrap_inputs(inputs);
    const auto n = inputs.at("Truncation order").value<int>();

    // Step 1: Fragment system
    auto& fragment_mod = submods.at("Fragment Driver");
    const auto& fragments = fragment_mod.run_as<fragment_pt>(sys);

    // Step 2: Map basis functions to atoms

    // Step 3: Build inputs
    // Loop over m = 1 to n
    // Loop over m-mers
    // Make m-mer basis set
    // Loop over powerset of k-mers (k <= m) in m-mer basis set
    // Push pairs back

    // Step 4: Run calculations

    // Step 5: Combine results
    simde::type::tensor energy(0.0);

    auto rv = results();
    return my_pt::wrap_results(rv, energy);
}

}