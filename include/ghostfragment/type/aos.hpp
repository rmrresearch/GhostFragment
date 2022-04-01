#pragma once
#include <chemist/set_theory/set_theory.hpp>
#include <ghostfragment/type/nuclei.hpp>
#include <map>
#include <simde/types.hpp>
#include <vector>

namespace ghostfragment::type {

/// Type used to model atomic orbitals
using ao_basis_set = simde::type::ao_basis_set;

/// Type of a partitioned molecular AO basis set
using fragmented_aos = chemist::set_theory::FamilyOfSets<ao_basis_set>;

/// Type of a set of aos
using ao_set = typename fragmented_aos::value_type;

/// Type of a map from an index to a set of AOs
using idx2aos = std::vector<ao_set>;

/// Type of a map from a set of nuclei to an AO basis set
using fragment_to_ao_basis = std::map<atom_set, ao_set>;

} // namespace ghostfragment::type
