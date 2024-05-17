#include "topology.hpp"
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/topology/connectivity_table.hpp>
#include <ghostfragment/property_types/topology/nuclear_graph.hpp>

namespace ghostfragment::topology {

using my_pt   = ghostfragment::pt::NuclearGraph;
using pa_pt   = ghostfragment::pt::FragmentedNuclei;
using conn_pt = ghostfragment::pt::ConnectivityTable;

const auto module_desc = R"(
Nuclear Graph From Atomic Connectivity
--------------------------------------

This module takes as input a ChemicalSystem, breaks it into a set of disjoint
fragments (how this is done is controlled by the "Nodes" submodule). Then uses
the connectivity of the ChemicalSystem's Molecule to determine the edges of the
graph.
)";

MODULE_CTOR(NuclearGraphFromConnectivity) {
    description(module_desc);
    satisfies_property_type<my_pt>();

    add_submodule<pa_pt>("Nodes");
    add_submodule<conn_pt>("Connectivity");
}

MODULE_RUN(NuclearGraphFromConnectivity) {
    using traits_type = pt::NuclearGraphTraits;
    using result_type = traits_type::result_type;

    const auto& [chem_sys] = my_pt::unwrap_inputs(inputs);
    auto& pseudo_atom_mod  = submods.at("Nodes");
    const auto& frags      = pseudo_atom_mod.run_as<pa_pt>(chem_sys);

    auto& conn_mod         = submods.at("Connectivity");
    const auto& atom_conns = conn_mod.run_as<conn_pt>(chem_sys.molecule());

    const auto nnodes = frags.size();
    std::decay_t<decltype(atom_conns)> edges(nnodes);

    for(std::size_t i = 0; i < nnodes; ++i) {
        const auto node_i = frags.nuclear_indices(i);

        // Get a set of all atoms bonded to node_i
        decltype(atom_conns.bonded_atoms(i)) node_i_conns;
        for(const auto atom_i : node_i) {
            const auto conns = atom_conns.bonded_atoms(atom_i);
            node_i_conns.insert(conns.begin(), conns.end());
        }

        // Loop over other nodes
        for(std::size_t j = i + 1; j < nnodes; ++j) {
            const auto node_j = frags.nuclear_indices(j);
            // If an atom in node_j is bonded to node_i, then there's an edge
            for(const auto atom_j : node_j) {
                if(node_i_conns.count(atom_j)) {
                    edges.add_bond(i, j);
                    break;
                }
            }
        }
    }

    result_type graph(frags, std::move(edges));
    auto rv = results();
    return my_pt::wrap_results(rv, std::move(graph));
}

} // namespace ghostfragment::topology
