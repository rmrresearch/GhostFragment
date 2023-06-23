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
        single_hydrogen.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
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
        frag.add_fragment({0, 1});
        frag.add_fragment({0, 2});
        frag.add_fragment({0, 3});
        frag.add_fragment({0, 4});

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
        frag.add_fragment({0, 2});
        frag.add_fragment({0, 3});
        frag.add_fragment({0, 4});
        frag.add_fragment({0, 1, 5, 6, 7});
        frag.add_fragment({1, 5});
        frag.add_fragment({1, 6});
        frag.add_fragment({1, 7});

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
        frag.add_fragment({0, 1, 2, 3, 4});
        frag.add_fragment({0, 1, 5, 6, 7});

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
        frag.add_fragment({0, 1, 2, 3, 4, 5, 6, 7});
        frag.add_fragment({0, 1, 3, 4, 5});
        frag.add_fragment({0, 1, 2, 6, 7});
        frag.add_fragment({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        frag.add_fragment({0, 1, 2, 6, 7, 8, 9, 10});
        frag.add_fragment({1, 2, 8, 9, 10});

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
        REQUIRE(corr.operator==(rv));
    }
}