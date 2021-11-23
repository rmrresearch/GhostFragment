#include "drivers.hpp"

namespace ghostfragment::drivers {

using frags_pt = simde::FragmentedMolecule;

const auto mod_desc = R"(
Fragment Driver
---------------

This module is responsible for going from a simde::type::molecule object to
a simde::type::fragmented_molecule object. Generally speaking this occurrs by:

#. Forming pseudoatoms
#. Determining the connectivity of the pseudoatoms
#. Fragmenting the resulting molecular graph

Ultimately, pseudoatoms are simply a partitioning of the molecule. In fact, the
pesudoatoms are (conceptually) perfectly fine fragments in and of themselves.
For this reason we take the submodule for forming the pseudoatoms to be of type
simde::FragmentMolecule also. Next we determine the connectivity of the
pseudoatoms; this happens in a submodule of type MolecularGraph. Finally, the
driver calls into a submodule of type XXX, which is responsible for breaking the
MolecularGraph instance into fragments.

)";

} // namespace ghostfragment::drivers