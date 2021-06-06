#pragma once
#include <property_types/types.hpp>

namespace ghostfragment::type {

/// Type used to model the nuclear framework of a system
using molecule = property_types::type::molecule;

/// Type used to model a nucleus in the molecule
using atom = typename molecule::value_type;

/// Type used for connectivity tables
using connectivity_table = property_types::type::connectivity_table;

/// Type used to denote tags/labels per fragment
using tag = std::string;

} // namespace ghostfragment::type