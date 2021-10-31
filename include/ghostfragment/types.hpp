#pragma once
#include <libchemist/chemical_system/chemical_system.hpp>
#include <libchemist/set_theory/set_theory.hpp>
#include <simde/types.hpp>

namespace ghostfragment::type {

/// Type used to denote tags/labels per fragment
using tag = std::string;

/// Type resulting from partitioning an object of type @p T
template<typename T>
using fragmented = libchemist::set_theory::FamilyOfSets<T>;

/// Type of a partitioned molecule
using fragmented_molecule = fragmented<simde::type::molecule>;

/// Type of a partitioned pairs of molecules and AO basis sets
using fragmented_mols_and_aos =
  fragmented<std::tuple<simde::type::molecule, simde::type::ao_basis_set>>;

/// Type of the nmers
using nmers = fragmented<fragmented_molecule>;

/// Type of a partitioned system
using fragmented_system = fragmented<simde::type::chemical_system>;

} // namespace ghostfragment::type
