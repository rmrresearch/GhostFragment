#pragma once
#include "ghostfragment/property_types/subset_map.hpp"
#include "ghostfragment/types.hpp"
#include <simde/simde.hpp>

namespace ghostfragment::pt {

using frag_traits = simde::FragmentedTraits<simde::type::molecule>;

using nmer_traits = simde::FragmentedTraits<typename frag_traits::return_type>;

/// Property type for a module which computes N-Mers
using NMers = simde::Fragmented<typename nmer_traits::input_type>;

} // namespace ghostfragment::pt
