#pragma once
#include <ghostfragment/property_types/capped.hpp>
#include <ghostfragment/property_types/expression.hpp>
#include <ghostfragment/property_types/molecular_graph.hpp>
#include <ghostfragment/property_types/molecular_graph_to_fragments.hpp>
#include <ghostfragment/property_types/nmer_screener.hpp>
#include <ghostfragment/property_types/nmer_system.hpp>
#include <ghostfragment/property_types/subset_map.hpp>
#include <ghostfragment/property_types/input_queue.hpp>
#include <ghostfragment/type/type.hpp>
#include <simde/simde.hpp>

/** @brief Namespace collecting all of the property types used throughout
 *         GhostFragment.
 *
 *  GhostFragment uses a number of property types. To protect the source code of
 *  GhostFragment from upstream changes to those property types, and for
 *  consistency, we typedef the property types we use in the pt namespace and
 *  rely on the typedefs throughout GhostFragment.
 */
namespace ghostfragment::pt {

/// PT for assigning AOs to a nuclei
using AtomicOrbitals = simde::AtomicOrbitals;

/// Traits associated with simde::FragmentedMolecule PT
using frag_traits = simde::FragmentedTraits<type::nuclei_set>;

/// PT for fragmenting a Molecule object
// using FragmentedMolecule = simde::FragmentedMolecule;

/// Traits associated with the PT for NMers
using nmer_traits = simde::FragmentedTraits<typename frag_traits::return_type>;

/// Property type for a module which computes N-Mers
using NMers = simde::Fragmented<typename nmer_traits::input_type>;

/// Traits for property types
using atom2ao_traits = simde::detail_::AtomToCenterTraits;

} // namespace ghostfragment::pt
