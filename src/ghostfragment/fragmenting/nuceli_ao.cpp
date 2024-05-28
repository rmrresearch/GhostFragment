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

// #include "fragmenting.hpp"
// #include <ghostfragment/property_types/subset_map.hpp>

// using namespace ghostfragment::pt;

// namespace ghostfragment::fragmenting {

// using my_pt          = Frag2AO;
// using atom2center_pt = simde::AtomToAO;

// const auto mod_desc = R"(
// AOSpace/Molecule Partitioner
// ----------------------------

// This module serves as a driver of sorts for fragmenting a molecule and then
// assigning AO basis sets to the fragments. How fragments are formed, and how
// AOs are mapped to atoms is determined by submodules. This module then uses
// the results of the two submodules to associate each fragment with an AO basis
// set.

// .. note::

//    The AO basis set associated with each fragment is more akin to applying an
//    atomic basis set to the fragment, than the AO basis set one would use for
//    say performing a basis-set superposition error calculation. The exact
//    details depend on the "Atom to Center" module though.
// )";

// MODULE_CTOR(NucleiAO) {
//     satisfies_property_type<my_pt>();

//     add_submodule<atom2center_pt>("Atom to Center");
// }

// MODULE_RUN(NucleiAO) {
//     const auto& [frags, aos] = my_pt::unwrap_inputs(inputs);
//     const auto& mol          = frags.object();

//     // Step 1: Map atoms to AOs
//     const auto& atom_ao =
//       submods.at("Atom to Center").run_as<atom2center_pt>(mol, aos);

//     typename Frag2AOTraits::fos_value_type fragged_aos(aos);
//     typename Frag2AOTraits::result_type frag2aos;
//     // Step 2: Apply basis functions to fragment
//     for(const auto& fragi : frags) {
//         auto new_set = fragged_aos.new_subset();
//         for(auto atomi : fragi) {
//             for(auto centeri : atom_ao.at(atomi)) new_set.insert(centeri);
//         }
//         frag2aos.emplace(fragi, std::move(new_set));
//     }

//     auto rv = results();
//     return my_pt::wrap_results(rv, frag2aos);
// }

// } // namespace ghostfragment::fragmenting
