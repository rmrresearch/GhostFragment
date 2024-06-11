/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/fragmenting/intersections.hpp>
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
#include <ghostfragment/property_types/topology/connectivity_table.hpp>
#include <ghostfragment/property_types/topology/nuclear_graph.hpp>
using namespace ghostfragment;
using namespace testing;

using conn_pt         = pt::ConnectivityTable;
using frags_pt        = pt::FragmentedNuclei;
using graph_pt        = pt::NuclearGraph;
using intersection_pt = pt::Intersections;
using graph2frags_pt  = pt::NuclearGraphToFragments;
using broken_bonds_pt = pt::BrokenBonds;
using cap_pt          = pt::CappedFragments;

using system_type       = typename pt::FragmentedNucleiTraits::system_type;
using molecule_type     = typename system_type::molecule_t;
using frags_type        = typename pt::FragmentedNucleiTraits::result_type;
using graph_type        = typename pt::NuclearGraphTraits::result_type;
using conns_type        = typename graph_type::connectivity_type;
using broken_bonds_type = typename pt::BrokenBondsTraits::result_type;
using n_type            = unsigned int;

namespace {

DECLARE_MODULE(NMerStub);

MODULE_CTOR(NMerStub) {
    satisfies_property_type<graph2frags_pt>();

    add_input<n_type>("n").set_default(n_type(1));
    add_input<n_type>("corr n");
    add_input<graph_type>("corr input");
    add_input<frags_type>("corr result");
}

MODULE_RUN(NMerStub) {
    const auto& [graph_in] = graph2frags_pt::unwrap_inputs(inputs);
    REQUIRE(graph_in == inputs.at("corr input").value<graph_type>());

    auto n = inputs.at("n").value<n_type>();
    REQUIRE(n == inputs.at("corr n").value<n_type>());

    auto rv                = results();
    const auto& corr_frags = inputs.at("corr result").value<frags_type>();
    return graph2frags_pt::wrap_results(rv, corr_frags);
}

auto make_conn_module(const molecule_type& sys, const graph_type& conns) {
    return pluginplay::make_lambda<conn_pt>([=](auto&& mol_in) {
        REQUIRE(mol_in == sys);
        return conns.edges();
    });
}

auto make_graph_module(const system_type& sys, const graph_type& g) {
    return pluginplay::make_lambda<graph_pt>([=](auto&& sys_in) {
        REQUIRE(sys_in == sys);
        return g;
    });
}

auto make_frag_module(const graph_type& g, const frags_type& rv) {
    return pluginplay::make_lambda<graph2frags_pt>([=](auto&& graph_in) {
        REQUIRE(graph_in == g);
        return rv;
    });
}

auto make_intersection_module(const frags_type& frags) {
    return pluginplay::make_lambda<intersection_pt>([=](auto&& frags_in) {
        REQUIRE(frags_in == frags);
        return frags;
    });
}

auto make_bond_module(const frags_type& frags, const graph_type& conns,
                      const broken_bonds_type& broken_bonds) {
    return pluginplay::make_lambda<broken_bonds_pt>(
      [=](auto&& frags_in, auto&& conns_in) {
          REQUIRE(frags_in == frags);
          REQUIRE(conns_in == conns.edges());
          return broken_bonds;
      });
}

auto make_cap_module(const frags_type& frags,
                     const broken_bonds_type& broken_bonds) {
    return pluginplay::make_lambda<cap_pt>(
      [=](auto&& frags_in, auto&& bonds_in) {
          REQUIRE(frags_in == frags);
          REQUIRE(bonds_in == broken_bonds);
          return frags_in;
      });
}

} // namespace

/* Testing strategy:
 *
 * The FragmentDriver module is purely a driver. If we assume the modules it
 * calls work correctly, the only thing we need to test is that the data flows.
 */

TEST_CASE("Fragment Driver") {
    auto mm   = initialize();
    auto& mod = mm.at("Fragment Driver");

    // Factor out so change_submod fits on one line
    const auto conn_key = "Atomic connectivity";
    const auto nmer_key = "N-mer builder";
    const auto frag_key = "Fragment builder";
    const auto int_key  = "Intersection finder";
    const auto bond_key = "Find broken bonds";
    const auto cap_key  = "Cap broken bonds";

    auto make_nmer_module = [&](const graph_type& graph,
                                const frags_type& frags) {
        mm.add_module<NMerStub>(nmer_key);
        mm.change_submod("Fragment Driver", "N-mer builder", nmer_key);

        // When eventually called we will pass n == 2, if called before we're
        // ready we'll gen an error because n defaults to 1.
        mm.change_input(nmer_key, "corr n", n_type(2));
        mm.change_input(nmer_key, "corr input", graph);
        mm.change_input(nmer_key, "corr result", frags);
    };

    SECTION("Empty Molecule") {
        molecule_type mol;
        system_type system(mol);
        frags_type corr(mol.nuclei());
        graph_type graph(corr, {});
        broken_bonds_type bonds;

        mod.change_submod(conn_key, make_conn_module(mol, graph));
        mod.change_submod("Molecular graph", make_graph_module(system, graph));
        mod.change_submod(frag_key, make_frag_module(graph, corr));
        mod.change_submod(int_key, make_intersection_module(corr));
        mod.change_submod(bond_key, make_bond_module(corr, graph, bonds));
        mod.change_submod(cap_key, make_cap_module(corr, bonds));
        make_nmer_module(graph, corr);
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
        broken_bonds_type bonds;

        mod.change_submod(conn_key, make_conn_module(mol, graph));
        mod.change_submod("Molecular graph", make_graph_module(system, graph));
        mod.change_submod(frag_key, make_frag_module(graph, corr));
        mod.change_submod(int_key, make_intersection_module(corr));
        mod.change_submod(bond_key, make_bond_module(corr, graph, bonds));
        mod.change_submod(cap_key, make_cap_module(corr, bonds));
        make_nmer_module(graph, corr);
        const auto& rv = mod.run_as<frags_pt>(system);
        REQUIRE(corr == rv);
    }

    SECTION("Methane") {
        auto methane = hydrocarbon(1);
        system_type system(methane);
        frags_type corr(methane.nuclei());
        corr.insert({0, 1, 2, 3, 4});
        graph_type graph(corr, {});
        broken_bonds_type bonds;

        mod.change_submod(conn_key, make_conn_module(methane, graph));
        mod.change_submod("Molecular graph", make_graph_module(system, graph));
        mod.change_submod(frag_key, make_frag_module(graph, corr));
        mod.change_submod(int_key, make_intersection_module(corr));
        mod.change_submod(bond_key, make_bond_module(corr, graph, bonds));
        mod.change_submod(cap_key, make_cap_module(corr, bonds));
        make_nmer_module(graph, corr);
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
        broken_bonds_type bonds{{0, 1}};

        mod.change_submod(conn_key, make_conn_module(ethane, graph));
        mod.change_submod("Molecular graph", make_graph_module(system, graph));
        mod.change_submod(frag_key, make_frag_module(graph, corr));
        mod.change_submod(int_key, make_intersection_module(corr));
        mod.change_submod(bond_key, make_bond_module(corr, graph, bonds));
        mod.change_submod(cap_key, make_cap_module(corr, bonds));
        make_nmer_module(graph, corr);
        const auto& rv = mod.run_as<frags_pt>(system);
        REQUIRE(corr == rv);
    }

    SECTION("Dispatches to N-mer builder when n > 1") {
        auto ethane = hydrocarbon(2);
        system_type system(ethane);
        frags_type corr(ethane.nuclei());
        corr.insert({0, 2, 3, 4});
        corr.insert({1, 5, 6, 7});
        conns_type c(2);
        c.add_bond(0, 1);
        graph_type graph(corr, c);
        broken_bonds_type bonds{{0, 1}};

        mod.change_submod(conn_key, make_conn_module(ethane, graph));
        mod.change_submod("Molecular graph", make_graph_module(system, graph));
        mod.change_submod(frag_key, make_frag_module(graph, corr));
        mod.change_submod(int_key, make_intersection_module(corr));
        mod.change_submod(bond_key, make_bond_module(corr, graph, bonds));
        mod.change_submod(cap_key, make_cap_module(corr, bonds));
        make_nmer_module(graph, corr);
        mod.change_input("n", n_type(2));
        const auto& rv = mod.run_as<frags_pt>(system);
        REQUIRE(corr == rv);
    }
}
