#include "test_ghostfragment.hpp"

namespace ghostfragment {

/* Testing Strategy:
 *
 * We test with water clusters. Since water molecules as nodes are not bonded,
 * we let the trimer and tetramer have artificial bonds.
 */

TEST_CASE("MolecularGraph") {
    using frags_t   = MolecularGraph::partitioned_mol_type;
    using connect_t = MolecularGraph::connectivity_type;

    auto water0 = testing::fragmented_water(0);
    auto water1 = testing::fragmented_water(1);
    auto water2 = testing::fragmented_water(2);
    auto water3 = testing::fragmented_water(3);
    auto water4 = testing::fragmented_water(4);

    connect_t water0_conns(0);
    connect_t water1_conns(1);
    connect_t water2_conns(2);
    connect_t water3_conns(3);
    water3_conns.add_bond(0, 1);
    connect_t water4_conns(4);
    water4_conns.add_bond(1, 2);
    water4_conns.add_bond(2, 3);

    MolecularGraph defaulted;
    MolecularGraph empty(water0, water0_conns);
    MolecularGraph monomer(water1, water1_conns);
    MolecularGraph dimer(water2, water2_conns);
    MolecularGraph trimer(water3, water3_conns);
    MolecularGraph tetramer(water4, water4_conns);

    SECTION("CTors") {
        SECTION("Default") {
            REQUIRE(defaulted.nedges() == 0);
            REQUIRE(defaulted.nnodes() == 0);
        }

        SECTION("Value") {
            REQUIRE(empty.nedges() == 0);
            REQUIRE(empty.nnodes() == 0);

            REQUIRE(monomer.nedges() == 0);
            REQUIRE(monomer.nnodes() == 1);

            REQUIRE(dimer.nedges() == 0);
            REQUIRE(dimer.nnodes() == 2);

            REQUIRE(trimer.nedges() == 1);
            REQUIRE(trimer.nnodes() == 3);

            REQUIRE(tetramer.nedges() == 2);
            REQUIRE(tetramer.nnodes() == 4);
        }

        SECTION("Copy") {
            MolecularGraph copy(tetramer);
            REQUIRE(copy == tetramer);
        }

        SECTION("Move") {
            MolecularGraph corr(tetramer);
            MolecularGraph moved(std::move(tetramer));
            REQUIRE(moved == corr);
        }

        SECTION("Copy Assignment") {
            MolecularGraph copy;
            auto pcopy = &(copy = tetramer);
            REQUIRE(pcopy == &copy);
            REQUIRE(copy == tetramer);
        }

        SECTION("Move Assignment") {
            MolecularGraph corr(tetramer);
            MolecularGraph moved;
            auto pmoved = &(moved = std::move(tetramer));
            REQUIRE(pmoved == &moved);
            REQUIRE(moved == corr);
        }
    }

    SECTION("hash") {
        SECTION("LHS is default") {
            auto lhs = pluginplay::hash_objects(defaulted);
            REQUIRE(lhs == pluginplay::hash_objects(MolecularGraph{}));

            REQUIRE(lhs != pluginplay::hash_objects(empty));
            REQUIRE(lhs != pluginplay::hash_objects(monomer));
        }

        SECTION("LHS is filled") {
            SECTION("RHS is same") {
                auto lhs = pluginplay::hash_objects(tetramer);
                MolecularGraph copy(water4, water4_conns);
                REQUIRE(lhs == pluginplay::hash_objects(copy));
            }

            SECTION("RHS has different partition") {
                auto lhs = pluginplay::hash_objects(monomer);

                frags_t w2(testing::water(2));
                auto x = w2.new_subset();
                for(std::size_t i = 0; i < 6; ++i) x.insert(i);
                w2.insert(x);

                MolecularGraph rhs(w2, water1_conns);

                REQUIRE(lhs != pluginplay::hash_objects(rhs));
            }

            SECTION("Different connections") {
                auto lhs = pluginplay::hash_objects(tetramer);
                auto x   = MolecularGraph(water4, connect_t(4));
                REQUIRE(lhs != pluginplay::hash_objects(x));
            }
        }
    }

    SECTION("Comparisons") {
        SECTION("LHS is default") {
            REQUIRE(defaulted == MolecularGraph{});
            REQUIRE_FALSE(defaulted != MolecularGraph{});

            REQUIRE(defaulted != empty);
            REQUIRE_FALSE(defaulted == empty);

            REQUIRE(defaulted != monomer);
            REQUIRE_FALSE(defaulted == monomer);
        }

        SECTION("LHS is filled") {
            // Same
            REQUIRE(tetramer == MolecularGraph(water4, water4_conns));
            REQUIRE_FALSE(tetramer != MolecularGraph(water4, water4_conns));

            frags_t w2(testing::water(2));
            auto x = w2.new_subset();
            for(std::size_t i = 0; i < 6; ++i) x.insert(i);
            w2.insert(x);
            REQUIRE(monomer != MolecularGraph(w2, water1_conns));
            REQUIRE_FALSE(monomer == MolecularGraph(w2, water1_conns));

            // Different connections
            REQUIRE(tetramer != MolecularGraph(water4, connect_t(4)));
            REQUIRE_FALSE(tetramer == MolecularGraph(water4, connect_t(4)));
        }
    }
}

} // namespace ghostfragment