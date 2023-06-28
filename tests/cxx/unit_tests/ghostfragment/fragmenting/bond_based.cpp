#include "../test_ghostfragment.hpp"
#include "hydrocarbon/hydrocarbon.h"

using namespace ghostfragment;

using molecule  = simde::type::molecule;
using graph     = pt::MolecularGraphToFragmentsTraits::graph_type;
using nodes_t   = graph::partitioned_mol_type;
using connect_t = graph::connectivity_type;
using my_pt     = pt::MolecularGraphToFragments;
using return_t  = pt::MolecularGraphToFragmentsTraits::fragment_type;
using subset_t  = typename return_t::value_type;

TEST_CASE("Bond-Based Fragmenter") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("Bond-Based Fragmenter");

    SECTION("Empty Molecule") {
        const auto& rv = mod.run_as<my_pt>(graph{});
        const auto& corr = return_t{typename graph::molecule_type{}};
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Single Atom") {
        chemist::Molecule single_hydrogen;
<<<<<<< HEAD
        single_hydrogen.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
=======
        single_hydrogen.push_back(chemist::Atom());
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(single_hydrogen.nuclei());
        frag.add_fragment({0});

        nodes_t nodes(frag);
        graph input(nodes, connect_t{});
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Methane, nbonds = 0") {
        // Tests methane (single carbon hydrocarbon) with fragments containing all nodes 
        // within 0 bonds of the fragment's central node. I.e. one frag for each atom in 
        // the system.
        chemist::Molecule methane = hydrocarbon(1);
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(methane.nuclei());
        frag.add_fragment({0});
        frag.add_fragment({1});
        frag.add_fragment({2});
        frag.add_fragment({3});
        frag.add_fragment({4});

        connect_t bonds = chemist::topology::ConnectivityTable(5);
        bonds.add_bond(0,1);
        bonds.add_bond(0,2);
        bonds.add_bond(0,3);
        bonds.add_bond(0,4);

        nodes_t nodes(frag);
        graph input(nodes, connect_t{});
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Methane, nbonds = 1") {
        // Tests methane (single carbon hydrocarbon) with fragments containing all nodes 
        // within 1 bond of the fragment's central node. I.e. one frag contains the whole
        // molecule, and four others contain the central carbon and one hydrogen.
        chemist::Molecule methane = hydrocarbon(1);
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(methane.nuclei());
        frag.add_fragment({0, 1, 2, 3, 4});
<<<<<<< HEAD
        frag.add_fragment({0, 1});
        frag.add_fragment({0, 2});
        frag.add_fragment({0, 3});
        frag.add_fragment({0, 4});
=======
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f

        connect_t bonds = chemist::topology::ConnectivityTable(5);
        bonds.add_bond(0,1);
        bonds.add_bond(0,2);
        bonds.add_bond(0,3);
        bonds.add_bond(0,4);

        chemist::FragmentedNuclei fragment_nodes = chemist::FragmentedNuclei(methane.nuclei());
        for(std::size_t i = 0; i < 5; ++ i) {
            fragment_nodes.add_fragment({i});
        }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(1));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Methane, nbonds = 2") {
        // Tests methane (single carbon hydrocarbon) with fragments containing all nodes 
        // within 2 bonds of the fragment's central node. Should just be a single frag.
        chemist::Molecule methane = hydrocarbon(1);
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(methane.nuclei());
        frag.add_fragment({0, 1, 2, 3, 4});

        connect_t bonds = chemist::topology::ConnectivityTable(5);
        bonds.add_bond(0,1);
        bonds.add_bond(0,2);
        bonds.add_bond(0,3);
        bonds.add_bond(0,4);

        chemist::FragmentedNuclei fragment_nodes = chemist::FragmentedNuclei(methane.nuclei());
        for(std::size_t i = 0; i < 5; ++ i) {
            fragment_nodes.add_fragment({i});
        }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(2));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Ethane, nbonds = 1") {
        // Tests ethane (two carbon hydrocarbon) with fragments containing all nodes 
        // within 1 bond of the fragment's central node. 
        chemist::Molecule ethane = hydrocarbon(2);
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(ethane.nuclei());
        frag.add_fragment({0, 1, 2, 3, 4});
<<<<<<< HEAD
        frag.add_fragment({0, 2});
        frag.add_fragment({0, 3});
        frag.add_fragment({0, 4});
        frag.add_fragment({0, 1, 5, 6, 7});
        frag.add_fragment({1, 5});
        frag.add_fragment({1, 6});
        frag.add_fragment({1, 7});
=======
        frag.add_fragment({0, 1, 5, 6, 7});
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f

        connect_t bonds = chemist::topology::ConnectivityTable(8);
        bonds.add_bond(0,1);
        bonds.add_bond(0,2);
        bonds.add_bond(0,3);
        bonds.add_bond(0,4);
        bonds.add_bond(1,5);
        bonds.add_bond(1,6);
        bonds.add_bond(1,7);

        chemist::FragmentedNuclei fragment_nodes = chemist::FragmentedNuclei(ethane.nuclei());
        for(std::size_t i = 0; i < 8; ++ i) {
            fragment_nodes.add_fragment({i});
        }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(1));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Ethane, nbonds = 2") {
        // Tests ethane (two carbon hydrocarbon) with fragments containing all nodes 
        // within 2 bonds of the fragment's central node. 
        chemist::Molecule ethane = hydrocarbon(2);
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(ethane.nuclei());
        frag.add_fragment({0, 1, 2, 3, 4, 5, 6, 7});
<<<<<<< HEAD
        frag.add_fragment({0, 1, 2, 3, 4});
        frag.add_fragment({0, 1, 5, 6, 7});
=======
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f

        connect_t bonds = chemist::topology::ConnectivityTable(8);
        bonds.add_bond(0,1);
        bonds.add_bond(0,2);
        bonds.add_bond(0,3);
        bonds.add_bond(0,4);
        bonds.add_bond(1,5);
        bonds.add_bond(1,6);
        bonds.add_bond(1,7);

        chemist::FragmentedNuclei fragment_nodes = chemist::FragmentedNuclei(ethane.nuclei());
        for(std::size_t i = 0; i < 8; ++ i) {
            fragment_nodes.add_fragment({i});
        }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(2));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Propane, nbonds = 2") {
        // Tests propane (three carbon hydrocarbon) with fragments containing all nodes 
        // within 2 bonds of the fragment's central node. 
        chemist::Molecule propane = hydrocarbon(3);
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(propane.nuclei());
<<<<<<< HEAD
        frag.add_fragment({0, 1, 2, 3, 4, 5, 6, 7});
        frag.add_fragment({0, 1, 3, 4, 5});
        frag.add_fragment({0, 1, 2, 6, 7});
        frag.add_fragment({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        frag.add_fragment({0, 1, 2, 6, 7, 8, 9, 10});
        frag.add_fragment({1, 2, 8, 9, 10});
=======
        frag.add_fragment({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f

        connect_t bonds = chemist::topology::ConnectivityTable(11);
        bonds.add_bond(0,1);
        bonds.add_bond(0,3);
        bonds.add_bond(0,4);
        bonds.add_bond(0,5);
        bonds.add_bond(1,2);
        bonds.add_bond(1,6);
        bonds.add_bond(1,7);
        bonds.add_bond(2,8);
        bonds.add_bond(2,9);
        bonds.add_bond(2,10);

        chemist::FragmentedNuclei fragment_nodes = chemist::FragmentedNuclei(propane.nuclei());
        for(std::size_t i = 0; i < 11; ++ i) {
            fragment_nodes.add_fragment({i});
        }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(2));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
<<<<<<< HEAD
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Propane, nbonds = 1, nodes are methyl groups") {
        // Tests propane (three carbon hydrocarbon) with fragments containing all nodes 
        // within 1 bond of the fragment's central node. 
        chemist::Molecule propane = hydrocarbon(3);
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(propane.nuclei());
        frag.add_fragment({0, 1, 3, 4, 5, 6, 7});
        frag.add_fragment({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        frag.add_fragment({1, 2, 6, 7, 8, 9, 10});

        connect_t bonds = chemist::topology::ConnectivityTable(3);
        bonds.add_bond(0,1);
        bonds.add_bond(1,2);

        chemist::FragmentedNuclei fragment_nodes = chemist::FragmentedNuclei(propane.nuclei());
        fragment_nodes.add_fragment({0, 3, 4, 5});
        fragment_nodes.add_fragment({1, 6, 7});
        fragment_nodes.add_fragment({2, 8, 9, 10});
=======
        REQUIRE(corr[0] == rv[0]);
        REQUIRE(corr.operator==(rv));
    }

    SECTION("Butane, nbonds = 1, nodes are methyl groups") {
        // Tests butane (four carbon hydrocarbon) with fragments containing all nodes 
        // within 1 bond of the fragment's central node. 
        chemist::Molecule butane = hydrocarbon(4);
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(butane.nuclei());
        frag.add_fragment({0, 1, 2, 4, 5, 6, 7, 8, 9, 10});
        frag.add_fragment({1, 2, 3, 7, 8, 9, 10, 11, 12, 13});

        connect_t bonds = chemist::topology::ConnectivityTable(4);
        bonds.add_bond(0,1);
        bonds.add_bond(1,2);
        bonds.add_bond(2,3);

        chemist::FragmentedNuclei fragment_nodes = chemist::FragmentedNuclei(butane.nuclei());
        fragment_nodes.add_fragment({0, 4, 5, 6});
        fragment_nodes.add_fragment({1, 7, 8});
        fragment_nodes.add_fragment({2, 9, 10});
        fragment_nodes.add_fragment({3, 11, 12, 13});
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(1));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
        REQUIRE(corr.operator==(rv));
    }
<<<<<<< HEAD
=======

    SECTION("Anthracene, nbonds = 7") {
        // Tests anthracene (polycyclic hydrocarbon C14H10) with fragments containing all nodes 
        // within 7 bonds of the fragment's central node. 
        chemist::Molecule anthracene = chemist::Molecule();
        // first fourteen atoms are carbons, positions are made different such that they aren't 
        // all compressed into a single atom
        for(std::size_t i = 0; i < 14; ++i) {
            anthracene.push_back(chemist::Atom("C", 6, 21874.662, i, 0, 0));
        }
        // next ten atoms are hydrogen
        for(std::size_t i = 0; i < 10; ++i) {
            anthracene.push_back(chemist::Atom("H", 1, 1837.289, 0, i, 0));
        }
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(anthracene.nuclei());
        frag.add_fragment({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23});

        connect_t bonds = chemist::topology::ConnectivityTable(24);
        for(std::size_t i = 0; i < 13; ++i) {
            bonds.add_bond(i, i + 1);
        }
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

        chemist::FragmentedNuclei fragment_nodes = chemist::FragmentedNuclei(anthracene.nuclei());
        for(std::size_t i = 0; i < 24; ++i) {
            fragment_nodes.add_fragment({i});
        }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(7));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
        REQUIRE(corr.operator==(rv));
    }

    SECTION("triangle ring, nbonds = 4") {
        // Tests a fictitious construction of nuclei to make sure BondBased can handle
        // rings. Bonds are arranged such that there is a triangular ring at the center
        // with chains extending from two of the nuclei in the triangle.
        chemist::Molecule triangle = chemist::Molecule();
        // atoms are carbons (arbitrary), positions are made different such that they aren't 
        // all compressed into a single atom
        for(std::size_t i = 0; i < 11; ++i) {
            triangle.push_back(chemist::Atom("C", 6, 21874.662, i, 0, 0));
        }
        chemist::FragmentedNuclei frag = chemist::FragmentedNuclei(triangle.nuclei());
        frag.add_fragment({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
        frag.add_fragment({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

        connect_t bonds = chemist::topology::ConnectivityTable(11);
        for(std::size_t i = 0; i < 10; ++i) {
            bonds.add_bond(i, i + 1);
        }
        bonds.add_bond(4,6);

        chemist::FragmentedNuclei fragment_nodes = chemist::FragmentedNuclei(triangle.nuclei());
        for(std::size_t i = 0; i < 11; ++i) {
            fragment_nodes.add_fragment({i});
        }

        nodes_t nodes(fragment_nodes);
        graph input(nodes, bonds);
        mod.change_input("nbonds", std::size_t(4));
        const auto& rv = mod.run_as<my_pt>(input);
        return_t corr = frag;
        REQUIRE(corr[0] == rv[0]);
        REQUIRE(corr[1] == rv[1]);
        REQUIRE(corr.size() == rv.size());
        REQUIRE(corr.operator==(rv));
    }
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f
}