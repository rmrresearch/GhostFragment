#pragma once
#include "ghostfragment/types.hpp"
#include <property_types/connectivity.hpp>
#include <property_types/fragmented.hpp>

namespace ghostfragment::pt {

using connectivity = property_types::Connectivity;

using fragmented_system = property_types::Fragmented<type::chem_system>;

using fragmented_mol = property_types::Fragmented<type::molecule>;

using nmer_maker = property_types::Fragmented<type::fragmented_molecule>;

} // namespace ghostfragment::pt
