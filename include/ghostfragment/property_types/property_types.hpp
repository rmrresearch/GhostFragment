#pragma once
#include "ghostfragment/property_types/partitioned.hpp"
#include "ghostfragment/types.hpp"
#include <property_types/connectivity.hpp>

namespace ghostfragment::pt {

using connectivity = property_types::Connectivity;

using fragmented_system = property_types::Partitioned<type::chem_system>;

using fragmented_mol = property_types::Partitioned<type::molecule>;

using nmer_maker = property_types::Partitioned<type::fragmented_molecule>;

} // namespace ghostfragment::pt
