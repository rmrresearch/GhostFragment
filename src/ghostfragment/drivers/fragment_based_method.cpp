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

#include "drivers.hpp"
#include <ghostfragment/property_types/fragmenting/fragment_weights.hpp>
#include <ghostfragment/property_types/fragmenting/fragmented_chemical_system.hpp>
#include <simde/energy/ao_energy.hpp>
#include <zip.hpp>
namespace ghostfragment::drivers {

using my_pt                = simde::TotalEnergy;
using ao_energy_pt         = simde::AOEnergy;
using fragmenting_pt       = pt::FragmentedChemicalSystem;
using fragmenting_traits   = pt::FragmentedChemicalSystemTraits;
using chemical_system_type = typename fragmenting_traits::system_type;
using basis_set_pt         = simde::MolecularBasisSet;
using weight_pt            = pt::FragmentWeights;
using egy_type             = simde::type::tensor;

namespace {
const auto mod_desc = R"(
Fragment-Based Method Driver
----------------------------

)";
}

MODULE_CTOR(FragmentBasedMethod) {
    description(mod_desc);

    satisfies_property_type<my_pt>();

    add_submodule<fragmenting_pt>("Subsystem former");
    add_submodule<weight_pt>("Weighter");
    add_submodule<my_pt>("Energy method");
}

MODULE_RUN(FragmentBasedMethod) {
    auto& logger = get_runtime().logger();

    // Step 0: Unpack input
    const auto& [sys] = my_pt::unwrap_inputs(inputs);

    // Step 1: Form subsystems
    auto& subsystem_mod    = submods.at("Subsystem former");
    const auto& subsystems = subsystem_mod.run_as<fragmenting_pt>(sys);

    // Step 2: Determine weights
    auto& weight_mod    = submods.at("weighter");
    const auto& weights = weight_mod.run_as<weight_pt>(subsystems);

    auto& energy_mod = submods.at("Energy method");

    egy_type energy(0.0);

    auto n_subsystems              = subsystems.size();
    decltype(n_subsystems) counter = 0;
    auto msg = [](auto counter, auto n_subsystems, auto egy) {
        std::stringstream ss;
        ss << egy;
        return "Energy of subsystem " + std::to_string(counter) + " of " +
               std::to_string(n_subsystems) + " : " + ss.str();
    };
    for(auto&& [c_i, sys_i] : iter::zip(weights, subsystems)) {
        auto mol_i = sys_i.molecule().as_molecule();

        // This is a hack until views work with values
        chemical_system_type sys_i_copy(mol_i);

        const auto e_i = energy_mod.run_as<my_pt>(sys_i_copy);
        simde::type::tensor temp;
        temp("")   = e_i("") * c_i;
        energy("") = energy("") + temp("");
        logger.debug("Weight of subsystem " + std::to_string(counter) + " is " +
                     std::to_string(c_i) + ".");
        logger.info(msg(counter++, n_subsystems, e_i));
    }

    auto rv = results();
    return my_pt::wrap_results(rv, energy);
}

} // namespace ghostfragment::drivers
