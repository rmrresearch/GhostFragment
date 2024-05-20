#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
#include <ghostfragment/property_types/topology/nuclear_graph.hpp>
using namespace ghostfragment;
using namespace testing;

using frags_pt       = pt::FragmentedNuclei;
using graph_pt       = pt::NuclearGraph;
using graph2frags_pt = pt::NuclearGraphToFragments;

using system_type   = typename pt::FragmentedNucleiTraits::system_type;
using molecule_type = typename system_type::molecule_t;
using frags_type    = typename pt::FragmentedNucleiTraits::result_type;
using graph_type    = typename pt::NuclearGraphTraits::result_type;
using conns_type    = typename graph_type::connectivity_type;

namespace {

auto make_graph_module(const system_type& sys, const graph_type& g) {
    return pluginplay::make_lambda<graph_pt>([=](auto&& sys_in) {
        REQUIRE(sys_in == sys);
        return g;
    });
}

auto make_g2frag_module(const graph_type& g, const frags_type& rv) {
    return pluginplay::make_lambda<graph2frags_pt>([=](auto&& graph_in) {
        REQUIRE(graph_in == g);
        return rv;
    });
}
} // namespace

/* Testing strategy:
 *
 * The FragmentDriver module is purely a driver. If we assume the modules it
 * calls work correctly, the only thing we need to test is that the data flows.
 * Testing is done using the default modules (Heavy Atom for pseudoatom
 * generation, Bond-Based for fragmentation).
 */

TEST_CASE("Fragment Driver") {
    auto mm   = initialize();
    auto& mod = mm.at("Fragment Driver");

    // Factor out so change_submod fits on one line
    const auto g2f_key = "Molecular graph to fragments";

    SECTION("Empty Molecule") {
        molecule_type mol;
        system_type system(mol);
        frags_type corr(mol.nuclei());
        graph_type graph(corr, {});

        mod.change_submod("Molecular graph", make_graph_module(system, graph));
        mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
        const auto& rv = mod.run_as<frags_pt>(system);
        REQUIRE(corr == rv);
    }

    SECTION("Single Atom") {
        molecule_type mol;
        mol.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
        system_type system(mol);
        frags_type corr(mol.nuclei());
        corr.insert({0});
        graph_type graph(corr, {});

        mod.change_submod("Molecular graph", make_graph_module(system, graph));
        mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
        const auto& rv = mod.run_as<frags_pt>(system);
        REQUIRE(corr == rv);
    }

    SECTION("Methane") {
        auto methane = hydrocarbon(1);
        system_type system(methane);
        frags_type corr(methane.nuclei());
        corr.insert({0, 1, 2, 3, 4});
        graph_type graph(corr, {});

        mod.change_submod("Molecular graph", make_graph_module(system, graph));
        mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
        const auto& rv = mod.run_as<frags_pt>(system);
        REQUIRE(corr == rv);
    }

    SECTION("Ethane") {
        auto ethane = hydrocarbon(2);
        system_type system(ethane);
        frags_type corr(ethane.nuclei());
        corr.insert({0, 2, 3, 4});
        corr.insert({1, 5, 6, 7});
        conns_type c(2);
        c.add_bond(0, 1);
        graph_type graph(corr, c);

        mod.change_submod("Molecular graph", make_graph_module(system, graph));
        mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
        const auto& rv = mod.run_as<frags_pt>(system);
        REQUIRE(corr == rv);
    }
}
