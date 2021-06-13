#pragma once
#include "ghostfragment/property_types/partitioned.hpp"
#include "ghostfragment/types.hpp"
#include <property_types/connectivity.hpp>

namespace ghostfragment::pt {

using connectivity = property_types::Connectivity;

using fragmented_mol = property_types::Partitioned<type::molecule>;

} // namespace ghostfragment::pt