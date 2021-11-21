#pragma once
#include <chemist/chemical_system/chemical_system.hpp>
#include <chemist/set_theory/set_theory.hpp>
#include <simde/types.hpp>

namespace ghostfragment::type {

/// Type used to denote tags/labels per fragment
using tag = std::string;

/// Type resulting from partitioning an object of type @p T
template<typename T>
using fragmented = chemist::set_theory::FamilyOfSets<T>;

/// Type of a partitioned molecule
using fragmented_molecule = fragmented<simde::type::molecule>;

/// Type of a partitioned molecular AO basis set
using fragmented_aos = fragmented<simde::type::ao_basis_set>;

/// Type of a map from fragment to AO basis set
using fragment_to_ao_basis = std::map<typename fragmented_molecule::value_type,
                                      typename fragmented_aos::value_type>;

/// Type of the nmers
using nmers = fragmented<fragmented_molecule>;

/// Type of a partitioned system
using fragmented_system = fragmented<simde::type::chemical_system>;

} // namespace ghostfragment::type
