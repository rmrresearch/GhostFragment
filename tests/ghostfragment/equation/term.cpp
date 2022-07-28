#include "../test_ghostfragment.hpp"
#include <ghostfragment/equation/term.hpp>

using namespace ghostfragment::equation;

TEST_CASE("Term") {
    auto water3 = testing::water_nmer_system(3, 2);
    auto nmer0  = water3.nmer(0);
    auto nmer1  = water3.nmer(1);

    auto aos0 = water3.ao_basis_set(nmer0);
    auto aos1 = water3.ao_basis_set(nmer1);

    Term::coefficient_type c0 = 1.2, c1 = 2.3;

    Term defaulted;
    Term t(nmer0, aos0, c0);

    SECTION("Ctors") {
        SECTION("Default") { REQUIRE(defaulted.empty()); }

        SECTION("value") {
            REQUIRE(t.nmer() == nmer0);
            REQUIRE(t.ao_basis_set() == aos0);
            REQUIRE(t.coefficient() == c0);
        }

        SECTION("copy") {
            Term defaulted_copy(defaulted);
            REQUIRE(defaulted_copy == defaulted);

            Term t_copy(t);
            REQUIRE(t_copy == t);
        }

        SECTION("move") {
            Term defaulted_copy(defaulted);
            Term defaulted_move(std::move(defaulted));
            REQUIRE(defaulted_copy == defaulted_move);

            Term t_copy(t);
            Term t_move(std::move(t));
            REQUIRE(t_copy == t_move);
        }

        SECTION("copy assignment") {
            Term defaulted_copy;
            auto pdefaulted_copy = &(defaulted_copy = defaulted);
            REQUIRE(pdefaulted_copy == &defaulted_copy);
            REQUIRE(defaulted_copy == defaulted);

            Term t_copy;
            auto pt_copy = &(t_copy = t);
            REQUIRE(pt_copy == &t_copy);
            REQUIRE(t_copy == t);
        }

        SECTION("move") {
            Term defaulted_copy(defaulted);
            Term defaulted_move;
            auto pdefaulted_move = &(defaulted_move = std::move(defaulted));
            REQUIRE(pdefaulted_move == &defaulted_move);
            REQUIRE(defaulted_copy == defaulted_move);

            Term t_copy(t);
            Term t_move;
            auto pt_move = &(t_move = std::move(t));
            REQUIRE(pt_move == &t_move);
            REQUIRE(t_copy == t_move);
        }
    }

    SECTION("nmer") {
        REQUIRE_THROWS_AS(defaulted.nmer(), std::runtime_error);
        REQUIRE(t.nmer() == nmer0);
    }

    SECTION("ao_basis_set") {
        REQUIRE_THROWS_AS(defaulted.ao_basis_set(), std::runtime_error);
        REQUIRE(t.ao_basis_set() == aos0);
    }

    SECTION("coefficient") {
        REQUIRE_THROWS_AS(defaulted.coefficient(), std::runtime_error);
        REQUIRE(t.coefficient() == c0);
    }

    SECTION("empty") {
        REQUIRE(defaulted.empty());
        REQUIRE_FALSE(t.empty());
    }

    SECTION("swap") {
        Term copy_default(defaulted);
        Term copy_t(t);

        defaulted.swap(t);
        REQUIRE(t == copy_default);
        REQUIRE(defaulted == copy_t);
    }

    SECTION("operator==/operator!=") {
        // Default to default
        REQUIRE(defaulted == Term());
        REQUIRE_FALSE(defaulted != Term());

        // Default to non-default
        REQUIRE_FALSE(defaulted == t);
        REQUIRE(defaulted != t);

        // Has value to Term with same value
        REQUIRE(t == Term(nmer0, aos0, c0));
        REQUIRE_FALSE(t != Term(nmer0, aos0, c0));

        // Values differ in the n-mer
        Term diff_nmer(nmer1, aos0, c0);
        REQUIRE_FALSE(t == diff_nmer);
        REQUIRE(t != diff_nmer);

        // Values differ in the AOs
        Term diff_aos(nmer0, aos1, c0);
        REQUIRE_FALSE(t == diff_aos);
        REQUIRE(t != diff_aos);

        // Values differ in the coefficient
        Term diff_cs(nmer0, aos0, c1);
        REQUIRE_FALSE(t == diff_cs);
        REQUIRE(t != diff_cs);
    }
}