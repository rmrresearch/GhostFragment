#include "../test_ghostfragment.hpp"

using namespace ghostfragment;

using molecule  = simde::type::molecule;
using graph     = pt::MolecularGraphToFragmentsTraits::graph_type;
using nodes_t   = graph::partitioned_mol_type;
using connect_t = graph::connectivity_type;
using my_pt     = pt::MolecularGraphToFragments;
using return_t  = pt::MolecularGraphToFragmentsTraits::fragment_type;
using subset_t  = typename return_t::value_type;

TEST_CASE("Cluster Partitioner") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("Cluster Partition");

    // Since we are hard-coding the connectivity tables the coordinates don't
    // matter
    auto [H, He, O] = testing::some_atoms();

    SECTION("Empty Molecule") {
        const auto& [rv] = mod.run_as<my_pt>(graph{});
        return_t corr(molecule{});
        REQUIRE(corr == rv);
    }

    SECTION("One Atom") {
        molecule mol{He};
        nodes_t nodes(mol, {{0}});
        graph input(nodes, connect_t{});
        const auto& [rv] = mod.run_as<my_pt>(input);
        return_t corr(mol, {{0}});
        REQUIRE(corr == rv);
    }

    SECTION("Two Atoms - Not bonded") {
        molecule mol{He, H};
        nodes_t nodes(mol, {{0}, {1}});
        graph input(nodes, connect_t{});

        const auto& [rv] = mod.run_as<my_pt>(input);
        return_t corr(mol, {{0}, {1}});
        REQUIRE(corr == rv);
    }

    SECTION("Two Atoms - Bonded") {
        molecule mol{He, H};
        nodes_t nodes(mol, {{0}, {1}});
        connect_t edges(2);
        edges.add_bond(0, 1);
        graph input(nodes, edges);

        const auto& [rv] = mod.run_as<my_pt>(input);
        return_t corr(mol, {{0, 1}});
        REQUIRE(corr == rv);
    }

    SECTION("Two molecules - nicely partitioned") {
        molecule mol{H, H, O, H, H};
        nodes_t nodes(mol, {{0}, {1}, {2}, {3}, {4}});
        connect_t edges(5);
        edges.add_bond(0, 2);
        edges.add_bond(1, 2);
        edges.add_bond(3, 4);
        graph input(nodes, edges);

        const auto& [rv] = mod.run_as<my_pt>(input);
        return_t corr(mol, {{0, 1, 2}, {3, 4}});
        REQUIRE(corr == rv);
    }

    SECTION("Two molecules - mixed up") {
        molecule mol{H, H, O, H, H};
        nodes_t nodes(mol, {{0}, {1}, {2}, {3}, {4}});
        connect_t edges(5);
        edges.add_bond(1, 3);
        edges.add_bond(0, 2);
        edges.add_bond(2, 4);
        graph input(nodes, edges);

        const auto& [rv] = mod.run_as<my_pt>(input);
        return_t corr(mol, {{0, 2, 4}, {1, 3}});
        REQUIRE(corr == rv);
    }

    SECTION("Two pseudoatoms - no bond") {
        molecule mol{H, H, O, H, H};
        nodes_t nodes(mol, {{0, 1, 2}, {3, 4}});
        connect_t edges(2);
        graph input(nodes, edges);

        const auto& [rv] = mod.run_as<my_pt>(input);
        return_t corr(mol, {{0, 1, 2}, {3, 4}});
        REQUIRE(corr == rv);
    }

    SECTION("Two pseudoatoms - bonded") {
        molecule mol{H, H, O, H, H};
        nodes_t nodes(mol, {{0, 1, 2}, {3, 4}});
        connect_t edges(2);
        edges.add_bond(0, 1);
        graph input(nodes, edges);

        const auto& [rv] = mod.run_as<my_pt>(input);
        return_t corr(mol, {{0, 1, 2, 3, 4}});
        REQUIRE(corr == rv);
    }
}