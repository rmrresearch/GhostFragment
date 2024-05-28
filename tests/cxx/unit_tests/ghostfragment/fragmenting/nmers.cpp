#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>

using my_pt      = ghostfragment::pt::NuclearGraphToFragments;
using traits     = ghostfragment::pt::NuclearGraphToFragmentsTraits;
using graph_type = typename traits::graph_type;
using frags_type = typename traits::fragment_type;
using size_type  = unsigned short;
namespace {

auto make_monomers(const graph_type& corr_graph, const frags_type& frags) {
    return pluginplay::make_lambda<my_pt>([=](auto&& graph_in) {
        REQUIRE(graph_in == corr_graph);
        return frags;
    });
}

} // namespace

TEST_CASE("NMers") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("All nmers");

    SECTION("Disjoint") {
        SECTION("Water 1") {
            size_type n_waters = 1;
            auto conns         = testing::water_connectivity(n_waters);
            auto monomers      = testing::water_fragmented_nuclei(n_waters);

            // Waters as pseudoatoms == heavy-atom partitioning
            graph_type graph(monomers, conns);
            mod.change_submod("Monomer maker", make_monomers(graph, monomers));

            SECTION("monomers") {
                mod.change_input("n", size_type{1});
                auto corr  = testing::water_fragmented_nuclei(n_waters);
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }
        }

        SECTION("Water 2") {
            size_type n_waters = 2;
            auto conns         = testing::water_connectivity(n_waters);
            auto monomers      = testing::water_fragmented_nuclei(n_waters);

            // Waters as pseudoatoms == heavy-atom partitioning
            graph_type graph(monomers, conns);

            mod.change_submod("Monomer maker", make_monomers(graph, monomers));

            SECTION("monomers") {
                mod.change_input("n", size_type{1});
                auto nmers = mod.run_as<my_pt>(graph);
                auto corr  = testing::water_fragmented_nuclei(n_waters);
                REQUIRE(nmers == corr);
            }

            SECTION("dimers") {
                mod.change_input("n", size_type{2});
                frags_type corr(monomers.supersystem().as_nuclei());
                corr.insert({0, 1, 2, 3, 4, 5});
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }
        }

        SECTION("Water 3") {
            size_type n_waters = 3;
            auto conns         = testing::water_connectivity(n_waters);
            auto monomers      = testing::water_fragmented_nuclei(n_waters);

            // Waters as pseudoatoms == heavy-atom partitioning
            graph_type graph(monomers, conns);

            mod.change_submod("Monomer maker", make_monomers(graph, monomers));

            SECTION("monomers") {
                mod.change_input("n", size_type{1});
                auto corr  = testing::water_fragmented_nuclei(n_waters);
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }

            SECTION("dimers") {
                mod.change_input("n", size_type{2});
                frags_type corr(monomers.supersystem().as_nuclei());
                corr.insert({0, 1, 2, 3, 4, 5});
                corr.insert({0, 1, 2, 6, 7, 8});
                corr.insert({3, 4, 5, 6, 7, 8});
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }

            SECTION("trimers") {
                mod.change_input("n", size_type{3});
                frags_type corr(monomers.supersystem().as_nuclei());
                corr.insert({0, 1, 2, 3, 4, 5, 6, 7, 8});
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }
        }
    }

    SECTION("Non-disjoint") {
        using testing::hydrocarbon_fragmented_nuclei;
        SECTION("Propane") {
            size_type n_carbons = 3;
            auto conns          = testing::hydrocarbon_connectivity(n_carbons);
            auto monomers       = hydrocarbon_fragmented_nuclei(n_carbons, 2);

            graph_type graph(monomers, conns);
            mod.change_submod("Monomer maker", make_monomers(graph, monomers));
            frags_type corr(monomers.supersystem().as_nuclei());

            SECTION("monomers") {
                mod.change_input("n", size_type{1});
                corr.insert({0, 1, 3, 4, 5, 6, 7});
                corr.insert({1, 2, 6, 7, 8, 9, 10});
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }

            SECTION("dimers") {
                mod.change_input("n", size_type{2});
                corr.insert({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }
        }

        SECTION("Butane") {
            size_type n_carbons = 4;
            auto conns          = testing::hydrocarbon_connectivity(n_carbons);
            auto monomers       = hydrocarbon_fragmented_nuclei(n_carbons, 2);

            graph_type graph(monomers, conns);
            mod.change_submod("Monomer maker", make_monomers(graph, monomers));
            frags_type corr(monomers.supersystem().as_nuclei());

            SECTION("monomers") {
                mod.change_input("n", size_type{1});
                auto nmers = mod.run_as<my_pt>(graph);
                corr.insert({0, 1, 4, 5, 6, 7, 8});
                corr.insert({1, 2, 7, 8, 9, 10});
                corr.insert({2, 3, 9, 10, 11, 12, 13});
                REQUIRE(nmers == corr);
            }

            SECTION("dimers") {
                mod.change_input("n", size_type{2});
                corr.insert({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }

            SECTION("trimers") {
                mod.change_input("n", size_type{3});
                corr.insert({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }
        }

        // First time the dimers aren't equal to the full system
        SECTION("Pentane") {
            size_type n_carbons = 5;
            auto conns          = testing::hydrocarbon_connectivity(n_carbons);
            auto monomers       = hydrocarbon_fragmented_nuclei(n_carbons, 2);

            graph_type graph(monomers, conns);
            mod.change_submod("Monomer maker", make_monomers(graph, monomers));
            frags_type corr(monomers.supersystem().as_nuclei());

            SECTION("monomers") {
                mod.change_input("n", size_type{1});
                auto nmers = mod.run_as<my_pt>(graph);
                corr.insert({0, 1, 5, 6, 7, 8, 9});
                corr.insert({1, 2, 8, 9, 10, 11});
                corr.insert({2, 3, 10, 11, 12, 13});
                corr.insert({3, 4, 12, 13, 14, 15, 16});
                REQUIRE(nmers == corr);
            }

            SECTION("dimers") {
                mod.change_input("n", size_type{2});
                corr.insert({0, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13});
                corr.insert({0, 1, 3, 4, 5, 6, 7, 8, 9, 12, 13, 14, 15, 16});
                corr.insert({1, 2, 3, 4, 8, 9, 10, 11, 12, 13, 14, 15, 16});
                auto nmers = mod.run_as<my_pt>(graph);
                REQUIRE(nmers == corr);
            }
        }
    }

    SECTION("Throws if n > number-of-fragments") {
        auto conns    = testing::water_connectivity(1);
        auto monomers = testing::water_fragmented_nuclei(1);

        // Waters as pseudoatoms == heavy-atom partitioning
        graph_type graph(monomers, conns);

        mod.change_submod("Monomer maker", make_monomers(graph, monomers));
        mod.change_input("n", size_type{2});
        REQUIRE_THROWS_AS(mod.run_as<my_pt>(graph), std::runtime_error);
    }
}
