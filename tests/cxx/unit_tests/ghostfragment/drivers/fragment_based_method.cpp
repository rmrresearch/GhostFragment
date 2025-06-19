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

#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmenting/fragment_weights.hpp>
#include <ghostfragment/property_types/fragmenting/fragmented_chemical_system.hpp>
#include <simde/simde.hpp>

/* Testing Strategy:
 *
 * This tests the main driver for GhostFragment. The main driver dispatches
 * to four submodules which respectively: fragment, compute weights, apply
 * basis sets, and finally run the calculations. We assume those submodules
 * are independently tested and known to work. Thus for the purposes of this
 * test we need to make sure the driver calls those submodules with the
 * correct inputs, and properly handles the results. This is easiest if we only
 * have one fragment, which we also just assume is a water molecule.
 *
 * To that end we create four lambda modules:
 *
 * - frag_mod checks that the inputs to the FragmentBasedMethod driver are
 *   forwarded to it correctly and then returns a set of fragments
 * - weight_mod checks that it was passed the fragments from frag_mod, then
 *   returns the weights.
 * - basis_mod just returns a basis
 * - egy_mod checks that its given one of the systems expr_mod makes and then
 *   computes a double based on the index of that system
 *
 * For a system with n fragments truncated at order m the energy computed by

 */

using namespace ghostfragment;
using namespace testing;

using my_pt                = simde::TotalEnergy;
using frag_sys_pt          = pt::FragmentedChemicalSystem;
using frag_sys_traits      = pt::FragmentedChemicalSystemTraits;
using chemical_system_type = typename frag_sys_traits::system_type;
using frag_sys_type        = typename frag_sys_traits::result_type;
using frag_mol_type        = typename frag_sys_type::fragmented_molecule_type;
using weights_pt           = pt::FragmentWeights;

// Checks that we pass in the correct system, returns a set of fragments
auto frag_mod(const chemical_system_type& sys, const frag_sys_type& frags) {
    return pluginplay::make_lambda<frag_sys_pt>([=](auto&& sys_in) {
        REQUIRE(sys == sys_in);
        return frags;
    });
}

// Checks we pass in fragments, returns a vector filled with 1s
auto weight_mod(const frag_sys_type& frags) {
    return pluginplay::make_lambda<weights_pt>([=](auto&& frags_in) {
        REQUIRE(frags == frags_in);
        return std::vector<double>(frags.size(), 2.0);
    });
}

auto energy_mod(const chemical_system_type& sys) {
    return pluginplay::make_lambda<my_pt>([=](auto&& sys_in) {
        REQUIRE(sys == sys_in);
        return -75.123456; // Just make up an energy...
    });
}

using tensorwrapper::operations::approximately_equal;

TEST_CASE("FragmentBasedMethod") {
    auto mm   = initialize();
    auto& mod = mm.at("Fragment Based Method");

    chemical_system_type water(testing::water(1));
    frag_mol_type frag_mol(testing::water_fragmented_nuclei(1), 0, 1);
    frag_sys_type frags(std::move(frag_mol));

    mod.change_submod("Subsystem former", frag_mod(water, frags));
    mod.change_submod("Weighter", weight_mod(frags));
    mod.change_submod("Energy method", energy_mod(water));

    auto energy = mod.run_as<my_pt>(water);
    simde::type::tensor corr(2.0 * -75.123456);

    REQUIRE(approximately_equal(energy, corr, 0.000001));
}
