#include "../test_ghostfragment.hpp"
#include "ghostfragment/property_types/molecular_graph.hpp"

using traits_type = ghostfragment::pt::MolecularGraphTraits;
using input_type  = traits_type::input_type;
using result_type = traits_type::result_type;
using conn_type   = result_type::connectivity_type;
namespace {

auto make_submod(const input_type& frags, const conn_type& conns) {
    return pluginplay::make_lambda<simde::Connectivity>([=](const auto& mol) {
        REQUIRE(frags.object() == mol);
        return conns;
    });
}

} // namespace

/* Testing Strategy:
 *
 * The module assumes that it's given disjoint fragments, and that connectivity
 * it gets back is correct. We test that we get the correct graph back for the
 * following situations:
 *
 * - 0 nodes
 * - 1 node
 * - 2 nodes, not connected
 * - 2 nodes, connected
 * - 3 nodes, not connected
 * - 3 nodes, 1 connection
 *
 * We use water molecules as nodes so that we get multi-atom nodes. If one
 * likes, then connections between nodes can be thought of as hydrogen bonds. In
 * reality the module doesn't care if there's any physical basis though.
 */

TEST_CASE("MolecularGraph from atomic connectivity") {
    using pt = ghostfragment::pt::MolecularGraph;

    auto mm   = testing::initialize();
    auto& mod = mm.at("Molecular Graph");

    SECTION("One node") {
        const auto nodes = testing::fragmented_water(1);
        conn_type atom_cons(3);
        atom_cons.add_bond(0, 1);
        atom_cons.add_bond(0, 2);
        mod.change_submod("Atomic connectivity", make_submod(nodes, atom_cons));

        result_type corr(nodes, conn_type(1));
        const auto& [graph] = mod.run_as<pt>(nodes);
        REQUIRE(graph == corr);
    }

    SECTION("Two nodes") {
        const auto nodes = testing::fragmented_water(1);
        conn_type atom_cons(6);
        atom_cons.add_bond(0, 1);
        atom_cons.add_bond(0, 2);
        atom_cons.add_bond(3, 4);
        atom_cons.add_bond(3, 5);

        SECTION("No connection") {
            mod.change_submod("Atomic connectivity",
                              make_submod(nodes, atom_cons));

            result_type corr(nodes, conn_type(2));
            const auto& [graph] = mod.run_as<pt>(nodes);
            REQUIRE(graph == corr);
        }

        SECTION("Connected") {
            atom_cons.add_bond(0, 3);
            mod.change_submod("Atomic connectivity",
                              make_submod(nodes, atom_cons));

            conn_type corr_cons(2);
            corr_cons.add_bond(0, 1);
            result_type corr(nodes, corr_cons);
            const auto& [graph] = mod.run_as<pt>(nodes);
            REQUIRE(graph == corr);
        }
    }
}