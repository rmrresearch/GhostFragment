#pragma once
#include <chemist/set_theory/set_theory.hpp>
#include <ghostfragment/caps.hpp>
#include <ghostfragment/type/aos.hpp>
#include <simde/types.hpp>

namespace ghostfragment::type {

/// Type of a partitoned set of caps
using fragmented_caps = chemist::set_theory::FamilyOfSets<Caps>;

/// Type of a set of caps
using cap_set = typename fragmented_caps::value_type;

/// Type of a map from a fragment to its caps
using fragment_to_caps = std::map<atom_set, cap_set>;

} // namespace ghostfragment::type
