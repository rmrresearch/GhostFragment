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

// #pragma once
// #include <ghostfragment/property_types/capped.hpp>
// #include <ghostfragment/property_types/expression.hpp>
// #include <ghostfragment/property_types/molecular_graph.hpp>
// #include <ghostfragment/property_types/molecular_graph_to_fragments.hpp>
// #include <ghostfragment/property_types/nmer_screener.hpp>
// #include <ghostfragment/property_types/nmer_system.hpp>
// #include <ghostfragment/property_types/subset_map.hpp>
// #include <ghostfragment/property_types/input_queue.hpp>
// #include <ghostfragment/type/type.hpp>
// #include <simde/simde.hpp>

// /** @brief Namespace collecting all of the property types used throughout
//  *         GhostFragment.
//  *
//  *  GhostFragment uses a number of property types. To protect the source code
//  of
//  *  GhostFragment from upstream changes to those property types, and for
//  *  consistency, we typedef the property types we use in the pt namespace and
//  *  rely on the typedefs throughout GhostFragment.
//  */
// namespace ghostfragment::pt {

// /// PT for assigning AOs to a nuclei
// using AtomicOrbitals = simde::AtomicOrbitals;

// /// Traits associated with simde::FragmentedMolecule PT
// using frag_traits = simde::FragmentedTraits<type::nuclei_set>;

// /// PT for fragmenting a Molecule object
// // using FragmentedMolecule = simde::FragmentedMolecule;

// /// Traits associated with the PT for NMers
// using nmer_traits = simde::FragmentedTraits<typename
// frag_traits::return_type>;

// /// Property type for a module which computes N-Mers
// using NMers = simde::Fragmented<typename nmer_traits::input_type>;

// /// Traits for property types
// using atom2ao_traits = simde::detail_::AtomToCenterTraits;

// } // namespace ghostfragment::pt
