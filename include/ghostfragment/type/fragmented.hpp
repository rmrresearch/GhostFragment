#pragma once
#include <chemist/set_theory/set_theory.hpp>
#include <simde/types.hpp>

namespace ghostfragment::type {

/** @brief Type of an object holding subsets taken from an object of type @p T.
 *
 */
template<typename T>
using set_of_fragments = chemist::set_theory::FamilyOfSets<T>;

using fragment_set = set_of_fragments<simde::type::molecule>;

// using nmer_set = set_of_fragments<fragmented_molecule>;

using fragmented_ao_set = set_of_fragments<simde::type::ao_basis_set>;

} // namespace ghostfragment::type
