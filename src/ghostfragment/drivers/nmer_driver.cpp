#include "drivers.hpp"

#include "ghostfragment/property_types/property_types.hpp"

namespace ghostfragment::drivers {

using pt       = ghostfragment::pt::NMers;
using frags_pt = simde::FragmentedMolecule;

const auto mod_desc = R"(
NMer Driver
-----------

This module wraps the general process of going from a 
``simde::type::fragmented_molecule_object`` to a ``ghostfragment::type::nmers``.
This has two major steps:

#. Cap the input fragments
#. Take selected unions of the capped fragments

Since it makes taking unions of fragments easier, the input fragments have not
been capped. However, for most screening methods caps are needed. Thus the first
step is to cap the fragments. Once we have capped fragments we screen the nmers 
and return the nmers which survive the screening process.
)";

} // namespace ghostfragment::drivers