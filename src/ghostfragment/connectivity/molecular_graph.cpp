#include "connectivity.hpp"
#include <ghostfragment/property_types/molecular_graph.hpp>

namespace ghostfragment::connectivity {

using my_pt   = ghostfragment::pt::MolecularGraph;
using conn_pt = simde::Connectivity;

const auto module_desc = R"(
Molecular Graph From Atomic Connectivity
----------------------------------------

This module takes as input a set of disjoint fragments. Then using the atomic
connectivity of the parent molecular system it determines the edges of the
graph (the nodes of the graph are the input disjoint fragments).
)";

MODULE_CTOR(MolecularGraph) {
    satisfies_property_type<my_pt>();

    add_submodule<conn_pt>("Atomic connectivity");
}

MODULE_RUN(MolecularGraph) {
    using traits_type = pt::MolecularGraphTraits;
    using result_type = traits_type::result_type;

    const auto& [frags] = my_pt::unwrap_inputs(inputs);

    auto& conn_mod           = submods.at("Atomic connectivity");
    const auto& [atom_conns] = conn_mod.run_as<conn_pt>(frags.object());

    const auto nnodes = frags.size();
    std::decay_t<decltype(atom_conns)> edges(nnodes);

    for(std::size_t i = 0; i < nnodes; ++i) {
        const auto& node_i = frags[i];

        // Get a set of all atoms bonded to node_i
        decltype(atom_conns.bonded_atoms(i)) node_i_conns;
        for(const auto atom_i : node_i) {
            const auto conns = atom_conns.bonded_atoms(atom_i);
            node_i_conns.insert(conns.begin(), conns.end());
        }

        // Loop over other nodes
        for(std::size_t j = i + 1; j < nnodes; ++j) {
            const auto& node_j = frags[j];
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

} // namespace ghostfragment::connectivity
