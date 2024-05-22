#include "drivers.hpp"
#include <ghostfragment/property_types/fragmenting/capped_fragments.hpp>
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
#include <ghostfragment/property_types/topology/broken_bonds.hpp>
#include <ghostfragment/property_types/topology/nuclear_graph.hpp>
namespace ghostfragment::drivers {

using broken_bonds_pt = pt::BrokenBonds;
using cap_pt          = pt::CappedFragments;
using frags_pt        = pt::FragmentedNuclei;
using graph_pt        = pt::NuclearGraph;
using graph2frags_pt  = pt::NuclearGraphToFragments;

const auto mod_desc = R"(
Fragment Driver
---------------

This module is responsible for going from a chemist::ChemicalSystem object to
a chemist::FragmentedNuclei object. Generally speaking this occurs by:

#. Determining the connectivity of the ChemicalSystem
#. Fragmenting the resulting molecular graph
#. Determine if bonds were broken
#. Cap the broken bonds

)";

MODULE_CTOR(Fragment) {
    description(mod_desc);
    satisfies_property_type<frags_pt>();

    add_submodule<graph_pt>("Molecular graph");
    add_submodule<graph2frags_pt>("Molecular graph to fragments");
    add_submodule<broken_bonds_pt>("Find broken bonds");
    add_submodule<cap_pt>("Cap broken bonds");
}

MODULE_RUN(Fragment) {
    const auto& [mol] = frags_pt::unwrap_inputs(inputs);

    auto& graph_mod   = submods.at("Molecular Graph");
    const auto& graph = graph_mod.run_as<graph_pt>(mol);

    auto& frags_mod   = submods.at("Molecular graph to fragments");
    const auto& frags = frags_mod.run_as<graph2frags_pt>(graph);

    auto& bonds_mod          = submods.at("Find broken bonds");
    const auto& conns        = graph.edges();
    const auto& broken_bonds = bonds_mod.run_as<broken_bonds_pt>(frags, conns);

    auto& cap_mod            = submods.at("Cap broken bonds");
    const auto& capped_frags = cap_mod.run_as<cap_pt>(frags, broken_bonds);

    auto rv = results();
    return frags_pt::wrap_results(rv, capped_frags);
}

} // namespace ghostfragment::drivers
