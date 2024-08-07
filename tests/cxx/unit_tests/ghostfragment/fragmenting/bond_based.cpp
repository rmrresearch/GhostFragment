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
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
using namespace ghostfragment;

using graph       = pt::NuclearGraphToFragmentsTraits::graph_type;
using nuclei_type = typename graph::nuclei_type;
using nodes_t     = graph::fragmented_nuclei;
using connect_t   = graph::connectivity_type;
using my_pt       = pt::NuclearGraphToFragments;
using return_t    = pt::NuclearGraphToFragmentsTraits::fragment_type;
using subset_t    = typename return_t::value_type;

TEST_CASE("Bond-Based Fragmenter") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("Bond-Based Fragmenter");

    SECTION("Empty Molecule") {
        const auto& rv = mod.run_as<my_pt>(graph{});
        return_t corr(nuclei_type{});
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Single Atom") {
        chemist::Molecule single_hydrogen;
        single_hydrogen.push_back(chemist::Atom());
        return_t frag(single_hydrogen.nuclei());
        frag.insert({0});

        nodes_t nodes(frag);
        graph input(nodes, connect_t{});
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Methane, nbonds = 0") {
        // Tests methane (single carbon hydrocarbon) with fragments containing
        // all nodes within 0 bonds of the fragment's central node. I.e. one
        // frag for each atom in the system.
        auto methane = testing::hydrocarbon(1);
        return_t frag(methane.nuclei());
        frag.insert({0});
        frag.insert({1});
        frag.insert({2});
        frag.insert({3});
        frag.insert({4});

        chemist::topology::ConnectivityTable bonds(5);
        bonds.add_bond(0, 1);
        bonds.add_bond(0, 2);
        bonds.add_bond(0, 3);
        bonds.add_bond(0, 4);

        nodes_t nodes(frag);
        graph input(nodes, bonds);
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Methane, nbonds = 1") {
        // Tests methane (single carbon hydrocarbon) with fragments containing
        // all nodes within 1 bond of the fragment's central node. I.e. one frag
        // contains the whole molecule, and four others contain the central
        // carbon and one hydrogen.
        auto methane = testing::hydrocarbon(1);
        return_t frag(methane.nuclei());
        frag.insert({0, 1, 2, 3, 4});

        connect_t bonds(5);
        bonds.add_bond(0, 1);
        bonds.add_bond(0, 2);
        bonds.add_bond(0, 3);
        bonds.add_bond(0, 4);

        return_t fragment_nodes(methane.nuclei());
        for(std::size_t i = 0; i < 5; ++i) { fragment_nodes.insert({i}); }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(1));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Methane, nbonds = 2") {
        // Tests methane (single carbon hydrocarbon) with fragments containing
        // all nodes within 2 bonds of the fragment's central node. Should just
        // be a single frag.
        auto methane = testing::hydrocarbon(1);
        return_t frag(methane.nuclei());
        frag.insert({0, 1, 2, 3, 4});

        connect_t bonds(5);
        bonds.add_bond(0, 1);
        bonds.add_bond(0, 2);
        bonds.add_bond(0, 3);
        bonds.add_bond(0, 4);

        return_t fragment_nodes(methane.nuclei());
        for(std::size_t i = 0; i < 5; ++i) { fragment_nodes.insert({i}); }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(2));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Ethane, nbonds = 1") {
        // Tests ethane (two carbon hydrocarbon) with fragments containing all
        // nodes within 1 bond of the fragment's central node.
        auto ethane = testing::hydrocarbon(2);
        return_t frag(ethane.nuclei());
        frag.insert({0, 1, 2, 3, 4});
        frag.insert({0, 1, 5, 6, 7});

        connect_t bonds(8);
        bonds.add_bond(0, 1);
        bonds.add_bond(0, 2);
        bonds.add_bond(0, 3);
        bonds.add_bond(0, 4);
        bonds.add_bond(1, 5);
        bonds.add_bond(1, 6);
        bonds.add_bond(1, 7);

        return_t fragment_nodes(ethane.nuclei());
        for(std::size_t i = 0; i < 8; ++i) { fragment_nodes.insert({i}); }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(1));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Ethane, nbonds = 2") {
        // Tests ethane (two carbon hydrocarbon) with fragments containing all
        // nodes within 2 bonds of the fragment's central node.
        auto ethane = testing::hydrocarbon(2);
        return_t frag(ethane.nuclei());
        frag.insert({0, 1, 2, 3, 4, 5, 6, 7});

        connect_t bonds(8);
        bonds.add_bond(0, 1);
        bonds.add_bond(0, 2);
        bonds.add_bond(0, 3);
        bonds.add_bond(0, 4);
        bonds.add_bond(1, 5);
        bonds.add_bond(1, 6);
        bonds.add_bond(1, 7);

        return_t fragment_nodes(ethane.nuclei());
        for(std::size_t i = 0; i < 8; ++i) { fragment_nodes.insert({i}); }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(2));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Propane, nbonds = 2") {
        // Tests propane (three carbon hydrocarbon) with fragments containing
        // all nodes within 2 bonds of the fragment's central node.
        auto propane = testing::hydrocarbon(3);
        return_t frag(propane.nuclei());
        frag.insert({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

        connect_t bonds(11);
        bonds.add_bond(0, 1);
        bonds.add_bond(0, 3);
        bonds.add_bond(0, 4);
        bonds.add_bond(0, 5);
        bonds.add_bond(1, 2);
        bonds.add_bond(1, 6);
        bonds.add_bond(1, 7);
        bonds.add_bond(2, 8);
        bonds.add_bond(2, 9);
        bonds.add_bond(2, 10);

        return_t fragment_nodes(propane.nuclei());
        for(std::size_t i = 0; i < 11; ++i) { fragment_nodes.insert({i}); }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(2));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(std::as_const(corr)[0] == rv[0]);
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Butane, nbonds = 1, nodes are methyl groups") {
        // Tests butane (four carbon hydrocarbon) with fragments containing all
        // nodes within 1 bond of the fragment's central node.
        auto butane = testing::hydrocarbon(4);
        return_t frag(butane.nuclei());
        frag.insert({0, 1, 2, 4, 5, 6, 7, 8, 9, 10});
        frag.insert({1, 2, 3, 7, 8, 9, 10, 11, 12, 13});

        connect_t bonds(4);
        bonds.add_bond(0, 1);
        bonds.add_bond(1, 2);
        bonds.add_bond(2, 3);

        return_t fragment_nodes(butane.nuclei());
        fragment_nodes.insert({0, 4, 5, 6});
        fragment_nodes.insert({1, 7, 8});
        fragment_nodes.insert({2, 9, 10});
        fragment_nodes.insert({3, 11, 12, 13});

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(1));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Anthracene, nbonds = 7") {
        // Tests anthracene (polycyclic hydrocarbon C14H10) with fragments
        // containing all nodes within 7 bonds of the fragment's central node.
        chemist::Molecule anthracene;
        // first fourteen atoms are carbons, positions are made different such
        // that they aren't all compressed into a single atom
        for(std::size_t i = 0; i < 14; ++i) {
            anthracene.push_back(chemist::Atom("C", 6, 21874.662, i, 0, 0));
        }
        // next ten atoms are hydrogen
        for(std::size_t i = 0; i < 10; ++i) {
            anthracene.push_back(chemist::Atom("H", 1, 1837.289, 0, i, 0));
        }
        return_t frag(anthracene.nuclei());
        frag.insert({0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                     12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23});

        connect_t bonds(24);
        for(std::size_t i = 0; i < 13; ++i) { bonds.add_bond(i, i + 1); }
        bonds.add_bond(0, 13);
        bonds.add_bond(0, 14);
        bonds.add_bond(1, 15);
        bonds.add_bond(2, 16);
        bonds.add_bond(4, 17);
        bonds.add_bond(6, 18);
        bonds.add_bond(7, 19);
        bonds.add_bond(8, 20);
        bonds.add_bond(9, 21);
        bonds.add_bond(11, 22);
        bonds.add_bond(13, 23);
        bonds.add_bond(3, 12);
        bonds.add_bond(5, 10);

        return_t fragment_nodes(anthracene.nuclei());
        for(std::size_t i = 0; i < 24; ++i) { fragment_nodes.insert({i}); }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(7));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("triangle ring, nbonds = 4") {
        // Tests a fictitious construction of nuclei to make sure BondBased can
        // handle rings. Bonds are arranged such that there is a triangular ring
        // at the center with chains extending from two of the nuclei in the
        // triangle.
        chemist::Molecule triangle;
        // atoms are carbons (arbitrary), positions are made different such that
        // they aren't all compressed into a single atom
        for(std::size_t i = 0; i < 11; ++i) {
            triangle.push_back(chemist::Atom("C", 6, 21874.662, i, 0, 0));
        }
        return_t frag(triangle.nuclei());
        frag.insert({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
        frag.insert({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

        connect_t bonds(11);
        for(std::size_t i = 0; i < 10; ++i) { bonds.add_bond(i, i + 1); }
        bonds.add_bond(4, 6);

        return_t fragment_nodes(triangle.nuclei());
        for(std::size_t i = 0; i < 11; ++i) { fragment_nodes.insert({i}); }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(4));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr  = frag;
        REQUIRE(std::as_const(corr)[0] == rv[0]);
        REQUIRE(std::as_const(corr)[1] == rv[1]);
        REQUIRE(corr.size() == rv.size());
        REQUIRE(corr.operator==(rv));
    }
}
