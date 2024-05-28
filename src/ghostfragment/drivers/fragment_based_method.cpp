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

// #include "drivers.hpp"
// #include <ghostfragment/property_types/property_types.hpp>
// #include <simde/energy/ao_energy.hpp>

// namespace ghostfragment::drivers {

// using my_pt         = simde::AOEnergy;
// using frag_sys_pt   = pt::FragmentedSystem;
// using nmer_sys_pt   = pt::NMerSystem;
// using expression_pt = pt::Expression;

// namespace {

// const auto mod_desc = R"(
// Fragment-Based Method Driver
// ----------------------------

// )";
// }

// MODULE_CTOR(FragmentBasedMethod) {
//     satisfies_property_type<my_pt>();
//     description(mod_desc);

//     add_submodule<frag_sys_pt>("Fragment Maker");
//     add_submodule<nmer_sys_pt>("N-Mer Maker");
//     add_submodule<expression_pt>("Expression generator");
//     add_submodule<my_pt>("energy method");

//     unsigned int m(1);
//     add_input<unsigned int>("GMBE truncation order").set_default(m);
// }

// MODULE_RUN(FragmentBasedMethod) {
//     // Step 0: Unpack input
//     const auto& [aos, sys] = my_pt::unwrap_inputs(inputs);
//     const auto n = inputs.at("GMBE truncation order").value<unsigned int>();

//     // Stp 1: Create those fragments
//     auto& frag_mod      = submods.at("Fragment Maker");
//     const auto& [frags] = frag_mod.run_as<frag_sys_pt>(sys, aos.basis_set());

//     // Step 2: Create those n-mers
//     auto& nmer_mod      = submods.at("N-Mer Maker");
//     const auto& [nmers] = nmer_mod.run_as<nmer_sys_pt>(frags, n);

//     // Step 3: Create an expression
//     auto& expr_mod     = submods.at("Expression generator");
//     const auto& [expr] = expr_mod.run_as<expression_pt>(nmers);

//     // Step 4: Run those terms
//     double e      = 0.0;
//     auto& egy_mod = submods.at("energy method");
//     for(std::size_t term_index = 0; term_index < expr.size(); ++term_index) {
//         const auto& term_i = expr.at(term_index);
//         const auto sys_i   = term_i.chemical_system();
//         const chemist::orbital_space::AOSpace aos_i(term_i.ao_basis_set());
//         const auto c_i        = term_i.coefficient();
//         const auto [e_term_i] = egy_mod.run_as<my_pt>(aos_i, sys_i);
//         e += c_i * e_term_i;
//     }

//     auto rv = results();
//     return my_pt::wrap_results(rv, e);
// }

// } // namespace ghostfragment::drivers
