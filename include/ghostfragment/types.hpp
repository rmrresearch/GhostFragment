#pragma once
#include <libchemist/molecule/molecule.hpp>

namespace ghostfragment::type {

/// Type used to model the nuclear framework of a system
using molecule = libchemist::Molecule;

/// Type used to denote tags/labels per fragment
using tag = std::string;

} // namespace ghostfragment::type