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

#include "test_ghostfragment.hpp"
#include <ghostfragment/nuclear_graph.hpp>
namespace ghostfragment {

/* Testing Strategy:
 *
 * We test with water clusters. Since water molecules as nodes are not bonded,
 * we let the trimer and tetramer have artificial bonds.
 */

TEST_CASE("NuclearGraph") {
    using frags_t   = NuclearGraph::fragmented_nuclei;
    using connect_t = NuclearGraph::connectivity_type;
    using edge_list = NuclearGraph::edge_list_type;
    using pair_t    = typename edge_list::value_type;

    auto water0 = testing::water_fragmented_nuclei(0);
    auto water1 = testing::water_fragmented_nuclei(1);
    auto water2 = testing::water_fragmented_nuclei(2);
    auto water3 = testing::water_fragmented_nuclei(3);
    auto water4 = testing::water_fragmented_nuclei(4);

    connect_t water0_conns(0);
    connect_t water1_conns(1);
    connect_t water2_conns(2);
    connect_t water3_conns(3);
    water3_conns.add_bond(0, 1);
    connect_t water4_conns(4);
    water4_conns.add_bond(1, 2);
    water4_conns.add_bond(2, 3);

    NuclearGraph defaulted;
    NuclearGraph empty(water0, water0_conns);
    NuclearGraph monomer(water1, water1_conns);
    NuclearGraph dimer(water2, water2_conns);
    NuclearGraph trimer(water3, water3_conns);
    NuclearGraph tetramer(water4, water4_conns);

    SECTION("CTors") {
        SECTION("Default") {
            REQUIRE(defaulted.edges_size() == 0);
            REQUIRE(defaulted.nodes_size() == 0);
        }

        SECTION("Value") {
            REQUIRE(empty.edges_size() == 0);
            REQUIRE(empty.nodes_size() == 0);

            REQUIRE(monomer.edges_size() == 0);
            REQUIRE(monomer.nodes_size() == 1);

            REQUIRE(dimer.edges_size() == 0);
            REQUIRE(dimer.nodes_size() == 2);

            REQUIRE(trimer.edges_size() == 1);
            REQUIRE(trimer.nodes_size() == 3);

            REQUIRE(tetramer.edges_size() == 2);
            REQUIRE(tetramer.nodes_size() == 4);
        }

        SECTION("Copy") {
            NuclearGraph copy(tetramer);
            REQUIRE(copy == tetramer);
        }

        SECTION("Move") {
            NuclearGraph corr(tetramer);
            NuclearGraph moved(std::move(tetramer));
            REQUIRE(moved == corr);
        }

        SECTION("Copy Assignment") {
            NuclearGraph copy;
            auto pcopy = &(copy = tetramer);
            REQUIRE(pcopy == &copy);
            REQUIRE(copy == tetramer);
        }

        SECTION("Move Assignment") {
            NuclearGraph corr(tetramer);
            NuclearGraph moved;
            auto pmoved = &(moved = std::move(tetramer));
            REQUIRE(pmoved == &moved);
            REQUIRE(moved == corr);
        }
    }

    SECTION("nuclei()") {
        REQUIRE_THROWS_AS(defaulted.nuclei(), std::runtime_error);
        REQUIRE(empty.nuclei() == water0.supersystem());
        REQUIRE(monomer.nuclei() == water1.supersystem());
        REQUIRE(dimer.nuclei() == water2.supersystem());
        REQUIRE(trimer.nuclei() == water3.supersystem());
        REQUIRE(tetramer.nuclei() == water4.supersystem());
    }

    SECTION("nodes_size()") {
        REQUIRE(defaulted.nodes_size() == 0);
        REQUIRE(empty.nodes_size() == 0);
        REQUIRE(monomer.nodes_size() == 1);
        REQUIRE(dimer.nodes_size() == 2);
        REQUIRE(trimer.nodes_size() == 3);
        REQUIRE(tetramer.nodes_size() == 4);
    }

    SECTION("edges_size()") {
        REQUIRE(defaulted.edges_size() == 0);
        REQUIRE(empty.edges_size() == 0);
        REQUIRE(monomer.edges_size() == 0);
        REQUIRE(dimer.edges_size() == 0);
        REQUIRE(trimer.edges_size() == 1);
        REQUIRE(tetramer.edges_size() == 2);
    }

    SECTION("edge_list()") {
        REQUIRE(defaulted.edge_list() == edge_list{});
        REQUIRE(empty.edge_list() == edge_list{});
        REQUIRE(monomer.edge_list() == edge_list{});
        REQUIRE(dimer.edge_list() == edge_list{});
        REQUIRE(trimer.edge_list() == edge_list{pair_t{0, 1}});
        REQUIRE(tetramer.edge_list() == edge_list{pair_t{1, 2}, pair_t{2, 3}});
    }

    SECTION("node()") {
        REQUIRE_THROWS_AS(defaulted.node(0), std::out_of_range);

        REQUIRE_THROWS_AS(empty.node(0), std::out_of_range);

        REQUIRE(monomer.node(0) == water1[0]);
        REQUIRE_THROWS_AS(monomer.node(1), std::out_of_range);

        REQUIRE(dimer.node(0) == water2[0]);
        REQUIRE(dimer.node(1) == water2[1]);
        REQUIRE_THROWS_AS(dimer.node(2), std::out_of_range);

        REQUIRE(trimer.node(0) == water3[0]);
        REQUIRE(trimer.node(1) == water3[1]);
        REQUIRE(trimer.node(2) == water3[2]);
        REQUIRE_THROWS_AS(trimer.node(3), std::out_of_range);

        REQUIRE(tetramer.node(0) == water4[0]);
        REQUIRE(tetramer.node(1) == water4[1]);
        REQUIRE(tetramer.node(2) == water4[2]);
        REQUIRE(tetramer.node(3) == water4[3]);
        REQUIRE_THROWS_AS(tetramer.node(4), std::out_of_range);
    }

    SECTION("Comparisons") {
        SECTION("LHS is default") {
            REQUIRE(defaulted == NuclearGraph{});
            REQUIRE_FALSE(defaulted != NuclearGraph{});

            REQUIRE(defaulted != empty);
            REQUIRE_FALSE(defaulted == empty);

            REQUIRE(defaulted != monomer);
            REQUIRE_FALSE(defaulted == monomer);
        }

        SECTION("LHS is filled") {
            // Same
            REQUIRE(tetramer == NuclearGraph(water4, water4_conns));
            REQUIRE_FALSE(tetramer != NuclearGraph(water4, water4_conns));

            frags_t w2(testing::water(2).nuclei());
            w2.insert({0, 1, 2, 3, 4, 5});
            REQUIRE(monomer != NuclearGraph(w2, water1_conns));
            REQUIRE_FALSE(monomer == NuclearGraph(w2, water1_conns));

            // Different connections
            REQUIRE(tetramer != NuclearGraph(water4, connect_t(4)));
            REQUIRE_FALSE(tetramer == NuclearGraph(water4, connect_t(4)));
        }
    }
}

} // namespace ghostfragment
