#include "drivers.hpp"
#include <ghostfragment/property_types/property_types.hpp>
#include <ghostfragment/property_types/fragmented_nuclei.hpp>

namespace ghostfragment::drivers {

using frags_pt       = pt::FragmentedNuclei;
using graph_pt       = pt::MolecularGraph;
using graph2frags_pt = pt::MolecularGraphToFragments;

const auto mod_desc = R"(
Fragment Driver
---------------

This module is responsible for going from a simde::type::molecule object to
a simde::type::fragmented_molecule object. Generally speaking this occurrs
by:

#. Forming pseudoatoms
#. Determining the connectivity of the pseudoatoms
#. Fragmenting the resulting molecular graph

Ultimately, pseudoatoms are simply a partitioning of the molecule. In fact,
the pesudoatoms are (conceptually) perfectly fine fragments in and of
themselves. For this reason we take the submodule for forming the pseudoatoms
to be of type simde::FragmentMolecule also. Next we determine the
connectivity of the pseudoatoms; this happens in a submodule of type
MolecularGraph. Finally, the driver calls into a submodule of type
MolecularGraphToFragments, which is responsible for breaking the
MolecularGraph instance into fragments.

)";

MODULE_CTOR(Fragment) {
    description(mod_desc);
    satisfies_property_type<frags_pt>();

    add_submodule<frags_pt>("Pseudoatoms");
    add_submodule<graph_pt>("Molecular graph");
    add_submodule<graph2frags_pt>("Molecular graph to fragments");
}

MODULE_RUN(Fragment) {
    const auto& [mol] = frags_pt::unwrap_inputs(inputs);

    auto& pseudoatom_mod    = submods.at("Pseudoatoms");
    const auto& pseudoatoms = pseudoatom_mod.run_as<frags_pt>(mol);

    auto& graph_mod         = submods.at("Molecular Graph");
    const auto& graph       = graph_mod.run_as<graph_pt>(pseudoatoms);

    auto& frags_mod         = submods.at("Molecular graph to fragments");
    const auto& frags       = frags_mod.run_as<graph2frags_pt>(graph);

    auto rv = results();
    return frags_pt::wrap_results(rv, frags);
}

} // namespace ghostfragment::drivers