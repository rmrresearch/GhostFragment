#pragma once
#include <chemist/set_theory/set_theory.hpp>
#include <simde/types.hpp>

namespace ghostfragment::type {

/// Type used to model a set of nuclei
using nuclei_set = simde::type::molecule;

/// Type of a partitioned molecule
using fragmented_molecule = chemist::set_theory::FamilyOfSets<nuclei_set>;

/// Type of a set of nuclei (a fragment)
using atom_set = typename fragmented_molecule::value_type;

/// Type of the nmers
// using nmers = chemist::set_theory::FamilyOfSets<fragmented_molecule>;

} // namespace ghostfragment::type
