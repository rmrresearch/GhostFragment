#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
using namespace ghostfragment;

using my_pt       = pt::NuclearGraphToFragments;
using graph_type  = pt::NuclearGraphToFragmentsTraits::graph_type;
using frags_type  = pt::NuclearGraphToFragmentsTraits::fragment_type;
using nuclei_type = typename graph_type::nuclei_type;
using nodes_t     = graph_type::fragmented_nuclei;
using connect_t   = graph_type::connectivity_type;

TEST_CASE("Cluster Partitioner") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("Cluster Partition");

    // Since we are hard-coding the connectivity tables the coordinates don't
    // matter
    auto h2o = testing::water(1);
    auto h0  = h2o[0].as_nucleus();
    auto h1  = h2o[1].as_nucleus();

    SECTION("Empty Molecule") {
        const auto rv = mod.run_as<my_pt>(graph_type{});
        frags_type corr(nuclei_type{});
        REQUIRE(corr == rv);
    }

    SECTION("One Atom") {
        nuclei_type mol{h0};
        nodes_t nodes(mol, {{0}});
        graph_type input(nodes, connect_t{});
        const auto rv = mod.run_as<my_pt>(input);
        frags_type corr(mol, {{0}});
        REQUIRE(corr == rv);
    }

    SECTION("Two Atoms - Not bonded") {
        nuclei_type mol{h0, h1};
        nodes_t nodes(mol, {{0}, {1}});
        graph_type input(nodes, connect_t{});

        const auto rv = mod.run_as<my_pt>(input);
        frags_type corr(mol, {{0}, {1}});
        REQUIRE(corr == rv);
    }

    SECTION("Two Atoms - Bonded") {
        nuclei_type mol{h0, h1};
        nodes_t nodes(mol, {{0}, {1}});
        connect_t edges(2);
        edges.add_bond(0, 1);
        graph_type input(nodes, edges);

        const auto& rv = mod.run_as<my_pt>(input);
        frags_type corr(mol, {{0, 1}});
        REQUIRE(corr == rv);
    }

    SECTION("Two molecules - nicely partitioned") {
        auto water2 = testing::water(2);
        nodes_t nodes(water2.nuclei(), {{0}, {1}, {2}, {3}, {4}, {5}});
        connect_t edges(6);
        edges.add_bond(0, 2);
        edges.add_bond(1, 2);
        edges.add_bond(3, 5);
        edges.add_bond(4, 5);
        graph_type input(nodes, edges);

        const auto& rv = mod.run_as<my_pt>(input);
        frags_type corr(water2.nuclei(), {{0, 1, 2}, {3, 4, 5}});
        REQUIRE(corr == rv);
    }

    SECTION("Two molecules - mixed up") {
        auto water2 = testing::water(2);
        nodes_t nodes(water2.nuclei(), {{0}, {1}, {2}, {3}, {4}, {5}});
        connect_t edges(6);
        edges.add_bond(1, 3);
        edges.add_bond(0, 2);
        edges.add_bond(2, 4);
        graph_type input(nodes, edges);

        const auto& rv = mod.run_as<my_pt>(input);
        frags_type corr(water2.nuclei(), {{0, 2, 4}, {1, 3}});
        REQUIRE(corr == rv);
    }

    SECTION("Two pseudoatoms - no bond") {
        auto water2 = testing::water(2);
        nodes_t nodes(water2.nuclei(), {{0, 1, 2}, {3, 4, 5}});
        connect_t edges(2);
        graph_type input(nodes, edges);

        const auto& rv = mod.run_as<my_pt>(input);
        frags_type corr(water2.nuclei(), {{0, 1, 2}, {3, 4, 5}});
        REQUIRE(corr == rv);
    }

    SECTION("Two pseudoatoms - bonded") {
        auto water2 = testing::water(2);
        nodes_t nodes(water2.nuclei(), {{0, 1, 2}, {3, 4, 5}});
        connect_t edges(2);
        edges.add_bond(0, 1);
        graph_type input(nodes, edges);

        const auto& rv = mod.run_as<my_pt>(input);
        frags_type corr(water2.nuclei(), {{0, 1, 2, 3, 4}});
        REQUIRE(corr == rv);
    }
}
