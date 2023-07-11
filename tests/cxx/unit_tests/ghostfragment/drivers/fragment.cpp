#include "../test_ghostfragment.hpp"
#include "hydrocarbon/hydrocarbon.h"
#include <ghostfragment/property_types/fragmented_nuclei.hpp>

using namespace ghostfragment;
using namespace testing;

using frags_pt       = pt::FragmentedNuclei;
using graph_pt       = pt::MolecularGraph;
using graph2frags_pt = pt::MolecularGraphToFragments;

using frags_type = chemist::FragmentedNuclei;
using graph_type = MolecularGraph;
using conns_type = simde::type::connectivity_table;
using mol_type   = chemist::Molecule;

namespace { 

auto make_patom_module(const chemist::Nuclei& mol, const frags_type& rv) {
    return pluginplay::make_lambda<frags_pt>([=](auto&& mol_in) {
        REQUIRE(mol_in == mol);
        return rv;
    });
}

auto make_graph_module(const frags_type& patoms, const graph_type& g) {
    return pluginplay::make_lambda<graph_pt>([=](auto&& patom_in) {
        REQUIRE(patom_in == patoms);
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
 * Testing is done using the default modules (Heavy Atom for pseudoatom generation,
 * Bond-Based for fragmentation).
 */

TEST_CASE("Fragment Driver") {
    auto mm   = initialize();
    auto& mod = mm.at("Fragment Driver");

    // Factor out so change_submod fits on one line
    const auto g2f_key = "Molecular graph to fragments";

    SECTION("Empty Molecule") {
        chemist::Molecule mol;
        frags_type corr(mol.nuclei());
        graph_type graph(corr, {});

        mod.change_submod("Pseudoatoms", make_patom_module(mol.nuclei(), corr));
        mod.change_submod("Molecular graph", make_graph_module(corr, graph));
        mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
        const auto& rv = mod.run_as<frags_pt>(mol.nuclei());
        REQUIRE(corr == rv);
    }

    SECTION("Single Atom") {
        chemist::Molecule mol;
        mol.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
        frags_type corr(mol.nuclei());
        corr.add_fragment({0});
        graph_type graph(corr, {});

        mod.change_submod("Pseudoatoms", make_patom_module(mol.nuclei(), corr));
        mod.change_submod("Molecular graph", make_graph_module(corr, graph));
        mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
        const auto& rv = mod.run_as<frags_pt>(mol.nuclei());
        REQUIRE(corr == rv);
    }

    SECTION("Methane") {
        auto methane = hydrocarbon(1);
        frags_type corr(methane.nuclei());
        corr.add_fragment({0, 1, 2, 3, 4});
        graph_type graph(corr, {});

        mod.change_submod("Pseudoatoms", make_patom_module(methane.nuclei(), corr));
        mod.change_submod("Molecular graph", make_graph_module(corr, graph));
        mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
        const auto& rv = mod.run_as<frags_pt>(methane.nuclei());
        REQUIRE(corr == rv);
    }

    SECTION("Ethane") {
        auto ethane = hydrocarbon(2);
        frags_type corr(ethane.nuclei());
        corr.add_fragment({0, 2, 3, 4});
        corr.add_fragment({1, 5, 6, 7});
        conns_type c(2);
        c.add_bond(0, 1);
        graph_type graph(corr, c);

        mod.change_submod("Pseudoatoms", make_patom_module(ethane.nuclei(), corr));
        mod.change_submod("Molecular graph", make_graph_module(corr, graph));
        mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
        const auto& rv = mod.run_as<frags_pt>(ethane.nuclei());
        REQUIRE(corr == rv);
    }
}