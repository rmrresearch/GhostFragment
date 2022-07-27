#include "../test_ghostfragment.hpp"
#include <ghostfragment/equation/expression.hpp>

using namespace ghostfragment::equation;

TEST_CASE("Expression") {
    auto water3 = testing::water_nmer_system(3, 2);
    auto nmer   = water3.nmer(0);
    auto aos    = water3.ao_basis_set(nmer);

    using term_type = Expression::term_type;
    term_type t0(nmer, aos, 1.23);
    term_type t1(nmer, aos, 3.15);

    Expression defaulted;
    Expression i0, i1;
    i0.add_term(t0);
    i1.add_term(t1);

    SECTION("CTor") {
        SECTION("default") {
            REQUIRE(defaulted.empty());
            REQUIRE(defaulted.size() == 0);
        }

        SECTION("copy") {
            Expression defaulted_copy(defaulted);
            REQUIRE(defaulted_copy == defaulted);

            Expression i0_copy(i0);
            REQUIRE(i0_copy == i0);

            Expression i1_copy(i1);
            REQUIRE(i1_copy == i1);
        }

        SECTION("move") {
            Expression defaulted_copy(defaulted);
            Expression defaulted_move(std::move(defaulted));
            REQUIRE(defaulted_copy == defaulted_move);

            Expression i0_copy(i0);
            Expression i0_move(std::move(i0));
            REQUIRE(i0_copy == i0_move);

            Expression i1_copy(i1);
            Expression i1_move(std::move(i1));
            REQUIRE(i1_copy == i1_move);
        }

        SECTION("copy assignment") {
            Expression defaulted_copy;
            auto pdefaulted_copy = &(defaulted_copy = defaulted);
            REQUIRE(pdefaulted_copy == &defaulted_copy);
            REQUIRE(defaulted_copy == defaulted);

            Expression i0_copy;
            auto pi0_copy = &(i0_copy = i0);
            REQUIRE(pi0_copy == &i0_copy);
            REQUIRE(i0_copy == i0);

            Expression i1_copy;
            auto pi1_copy = &(i1_copy = i1);
            REQUIRE(pi1_copy == &i1_copy);
            REQUIRE(i1_copy == i1);
        }

        SECTION("move assignment") {
            Expression defaulted_copy(defaulted);
            Expression defaulted_move;
            auto pdefaulted_move = &(defaulted_move = std::move(defaulted));
            REQUIRE(pdefaulted_move == &defaulted_move);
            REQUIRE(defaulted_copy == defaulted_move);

            Expression i0_copy(i0);
            Expression i0_move;
            auto pi0_move = &(i0_move = std::move(i0));
            REQUIRE(pi0_move == &i0_move);
            REQUIRE(i0_copy == i0_move);

            Expression i1_copy(i1);
            Expression i1_move;
            auto pi1_move = &(i1_move = std::move(i1));
            REQUIRE(pi1_move == &i1_move);
            REQUIRE(i1_copy == i1_move);
        }
    }
}