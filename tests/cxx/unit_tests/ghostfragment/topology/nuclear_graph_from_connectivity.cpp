#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/topology/connectivity_table.hpp>
#include <ghostfragment/property_types/topology/nuclear_graph.hpp>

using graph_traits         = ghostfragment::pt::NuclearGraphTraits;
using pseudoatom_traits    = ghostfragment::pt::FragmentedNucleiTraits;
using connectivity_traits  = ghostfragment::pt::ConnectivityTableTraits;
using connectivity_pt      = ghostfragment::pt::ConnectivityTable;
using pseudoatom_pt        = ghostfragment::pt::FragmentedNuclei;
using chemical_system_type = graph_traits::input_type;
using graph_type           = graph_traits::result_type;
using conn_type            = connectivity_traits::result_type;
using frags_type           = pseudoatom_traits::result_type;

namespace {

auto pseudoatoms_submod(chemical_system_type sys, frags_type frags) {
    return pluginplay::make_lambda<pseudoatom_pt>([=](auto system) {
        REQUIRE(system == sys);
        return frags;
    });
}

auto conns_submod(chemical_system_type sys, const conn_type& conns) {
    return pluginplay::make_lambda<connectivity_pt>([=](auto mol) {
        REQUIRE(sys.molecule() == mol);
        return conns;
    });
}

} // namespace

/* Testing Strategy:
 *
 * The module assumes that it's given a chemical system, and that the fragments
 * and connectivity it gets back from the submodules are correct. We test that
 * our module correctly calls the submodules and computes the correct nuclear
 * graph for the following situations:
 *
 * - 0 nodes
 * - 1 node
 * - 2 nodes, not connected
 * - 2 nodes, connected
 * - 3 nodes, not connected
 * - 3 nodes, 1 connection
 * - 3 nodes, 2 connections
 * - 3 nodes, 3 connections
 *
 * We use water molecules as nodes so that we get multi-atom nodes. If one
 * likes, then connections between nodes can be thought of as hydrogen bonds. In
 * reality the module doesn't care if there's any physical basis to the edges
 * though.
 */

TEST_CASE("NuclearGraph from Connectivity") {
    using pt = ghostfragment::pt::NuclearGraph;

    auto mm   = testing::initialize();
    auto& mod = mm.at("Nuclear Graph");

    SECTION("Zero nodes") {
        const auto sys   = chemical_system_type(testing::water(0));
        const auto nodes = testing::water_fragmented_nuclei(0);
        conn_type atom_cons(0);

        mod.change_submod("Nodes", pseudoatoms_submod(sys, nodes));
        mod.change_submod("Connectivity", conns_submod(sys, atom_cons));

        graph_type corr(nodes, atom_cons);
        const auto& graph = mod.run_as<pt>(sys);
        REQUIRE(graph == corr);
    }

    SECTION("One node") {
        const auto sys   = chemical_system_type(testing::water(1));
        const auto nodes = testing::water_fragmented_nuclei(1);
        conn_type atom_cons(3);
        atom_cons.add_bond(0, 1);
        atom_cons.add_bond(0, 2);

        mod.change_submod("Nodes", pseudoatoms_submod(sys, nodes));
        mod.change_submod("Connectivity", conns_submod(sys, atom_cons));

        graph_type corr(nodes, conn_type(1));
        const auto& graph = mod.run_as<pt>(sys);
        REQUIRE(graph == corr);
    }

    SECTION("Two nodes") {
        const auto sys   = chemical_system_type(testing::water(2));
        const auto nodes = testing::water_fragmented_nuclei(2);
        conn_type atom_cons(6);
        atom_cons.add_bond(0, 1);
        atom_cons.add_bond(0, 2);
        atom_cons.add_bond(3, 4);
        atom_cons.add_bond(3, 5);

        mod.change_submod("Nodes", pseudoatoms_submod(sys, nodes));

        SECTION("No connection") {
            mod.change_submod("Connectivity", conns_submod(sys, atom_cons));
            graph_type corr(nodes, conn_type(2));
            const auto& graph = mod.run_as<pt>(sys);
            REQUIRE(graph == corr);
        }

        SECTION("Connected") {
            atom_cons.add_bond(0, 3);
            mod.change_submod("Connectivity", conns_submod(sys, atom_cons));

            conn_type corr_cons(2);
            corr_cons.add_bond(0, 1);
            graph_type corr(nodes, corr_cons);
            const auto& graph = mod.run_as<pt>(sys);
            REQUIRE(graph == corr);
        }
    }

    SECTION("Three nodes") {
        const auto sys   = chemical_system_type(testing::water(3));
        const auto nodes = testing::water_fragmented_nuclei(3);
        conn_type atom_cons(9);
        atom_cons.add_bond(0, 1);
        atom_cons.add_bond(0, 2);
        atom_cons.add_bond(3, 4);
        atom_cons.add_bond(3, 5);
        atom_cons.add_bond(6, 7);
        atom_cons.add_bond(6, 8);

        mod.change_submod("Nodes", pseudoatoms_submod(sys, nodes));

        SECTION("No connection") {
            mod.change_submod("Connectivity", conns_submod(sys, atom_cons));

            graph_type corr(nodes, conn_type(3));
            const auto& graph = mod.run_as<pt>(sys);
            REQUIRE(graph == corr);
        }

        SECTION("One connection") {
            atom_cons.add_bond(0, 3);
            mod.change_submod("Connectivity", conns_submod(sys, atom_cons));

            conn_type corr_cons(3);
            corr_cons.add_bond(0, 1);
            graph_type corr(nodes, corr_cons);
            const auto& graph = mod.run_as<pt>(sys);
            REQUIRE(graph == corr);
        }

        SECTION("Two connection") {
            atom_cons.add_bond(0, 3);
            atom_cons.add_bond(3, 6);
            mod.change_submod("Connectivity", conns_submod(sys, atom_cons));

            conn_type corr_cons(3);
            corr_cons.add_bond(0, 1);
            corr_cons.add_bond(1, 2);
            graph_type corr(nodes, corr_cons);
            const auto& graph = mod.run_as<pt>(sys);
            REQUIRE(graph == corr);
        }

        SECTION("Three connection") {
            atom_cons.add_bond(0, 3);
            atom_cons.add_bond(3, 6);
            atom_cons.add_bond(6, 0);
            mod.change_submod("Connectivity", conns_submod(sys, atom_cons));

            conn_type corr_cons(3);
            corr_cons.add_bond(0, 1);
            corr_cons.add_bond(0, 2);
            corr_cons.add_bond(1, 2);
            graph_type corr(nodes, corr_cons);
            const auto& graph = mod.run_as<pt>(sys);
            REQUIRE(graph == corr);
        }
    }
}
