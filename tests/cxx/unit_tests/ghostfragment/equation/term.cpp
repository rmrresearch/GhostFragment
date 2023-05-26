#include "../test_ghostfragment.hpp"
#include <ghostfragment/equation/equation.hpp>

using namespace ghostfragment::equation;

TEST_CASE("Term") {
    auto water3          = testing::water_nmer_system(3, 2);
    const auto super_sys = testing::water(3);
    Term::molecule_type corr_mol;
    corr_mol.push_back(super_sys[0]);
    corr_mol.push_back(super_sys[1]);
    corr_mol.push_back(super_sys[2]);
    corr_mol.push_back(super_sys[3]);
    corr_mol.push_back(super_sys[4]);
    corr_mol.push_back(super_sys[5]);
    auto corr_aos = testing::sto3g(corr_mol);

    auto nmer0 = water3.nmer(0);
    auto nmer1 = water3.nmer(1);

    auto aos0 = water3.ao_basis_set(nmer0);
    auto aos1 = water3.ao_basis_set(nmer1);

    Term::coefficient_type c0 = 1.2, c1 = 2.3;
    Term::size_type ne0 = 1, ne1 = 2;
    Term defaulted;
    Term t = make_term(nmer0, aos0, ne0, c0);

    SECTION("Ctors") {
        SECTION("Default") { REQUIRE(defaulted.empty()); }

        SECTION("value") {
            // REQUIRE(t.ao_basis_set() == aos0);
            REQUIRE(t.molecule() == corr_mol);
            REQUIRE(t.n_electrons() == ne0);
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

    SECTION("ao_basis_set") {
        REQUIRE_THROWS_AS(defaulted.ao_basis_set(), std::runtime_error);
        REQUIRE(t.ao_basis_set() == corr_aos);
    }

    SECTION("molecule") {
        REQUIRE_THROWS_AS(defaulted.molecule(), std::runtime_error);
        REQUIRE(t.molecule() == corr_mol);
    }

    SECTION("n_electrons") {
        REQUIRE(defaulted.n_electrons() == 0);
        REQUIRE(t.n_electrons() == ne0);
    }

    SECTION("chemical_system") {
        Term::chemical_system_type corr(t.molecule(), t.n_electrons());
        REQUIRE(corr == t.chemical_system());
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
        REQUIRE(t == make_term(nmer0, aos0, ne0, c0));
        REQUIRE_FALSE(t != make_term(nmer0, aos0, ne0, c0));

        // Values differ in the n-mer
        auto diff_nmer = make_term(nmer1, aos0, ne0, c0);
        REQUIRE_FALSE(t == diff_nmer);
        REQUIRE(t != diff_nmer);

        // Values differ in the AOs
        auto diff_aos = make_term(nmer0, aos1, ne0, c0);
        REQUIRE_FALSE(t == diff_aos);
        REQUIRE(t != diff_aos);

        // Values differ in the number of electrons
        auto diff_nes = make_term(nmer0, aos0, ne1, c0);
        REQUIRE_FALSE(t == diff_nes);
        REQUIRE(t != diff_nes);

        // Values differ in the coefficient
        auto diff_cs = make_term(nmer0, aos0, ne0, c1);
        REQUIRE_FALSE(t == diff_cs);
        REQUIRE(t != diff_cs);
    }
}
