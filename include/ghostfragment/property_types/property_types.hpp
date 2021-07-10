#pragma once
#include "ghostfragment/property_types/ao_basis_set.hpp"
#include "ghostfragment/types.hpp"
#include <property_types/connectivity.hpp>
#include <property_types/fragmented.hpp>

namespace ghostfragment::pt {

/// Type of a property type providing ao basis sets to molecules
using ao_space = property_types::AOSpace<double>;

/// Type of a property type assigning connectivity
using connectivity = property_types::Connectivity;

/// Type of the property type for computing an energy
using energy = property_types::Energy<double>;

/// Type of a property type which fragments a molecule
using fragmented_mol = property_types::Fragmented<type::molecule>;

/// Type of a property type which combines fragments into nmers
using nmer_maker = property_types::Fragmented<type::fragmented_molecule>;

} // namespace ghostfragment::pt
