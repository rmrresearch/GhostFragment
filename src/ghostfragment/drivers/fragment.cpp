#include "drivers.hpp"
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
#include <ghostfragment/property_types/topology/nuclear_graph.hpp>
namespace ghostfragment::drivers {

using frags_pt       = pt::FragmentedNuclei;
using graph_pt       = pt::NuclearGraph;
using graph2frags_pt = pt::NuclearGraphToFragments;

const auto mod_desc = R"(
Fragment Driver
---------------

This module is responsible for going from a chemist::ChemicalSystem object to
a chemist::FragmentedNuclei object. Generally speaking this occurs by:

#. Determining the connectivity of the ChemicalSystem
#. Fragmenting the resulting molecular graph

)";

MODULE_CTOR(Fragment) {
    description(mod_desc);
    satisfies_property_type<frags_pt>();

    add_submodule<graph_pt>("Molecular graph");
    add_submodule<graph2frags_pt>("Molecular graph to fragments");
}

MODULE_RUN(Fragment) {
    const auto& [mol] = frags_pt::unwrap_inputs(inputs);

    auto& graph_mod   = submods.at("Molecular Graph");
    const auto& graph = graph_mod.run_as<graph_pt>(mol);

    auto& frags_mod   = submods.at("Molecular graph to fragments");
    const auto& frags = frags_mod.run_as<graph2frags_pt>(graph);

    auto rv = results();
    return frags_pt::wrap_results(rv, frags);
}

} // namespace ghostfragment::drivers
