#include "../../test_ghostfragment.hpp"
#include <ghostfragment/equation/detail_/term_pimpl.hpp>

using namespace ghostfragment::equation::detail_;

TEST_CASE("TermPIMPL") {
    auto water3 = testing::water_nmer_system(3, 2);
    TermPIMPL::molecule_type corr_mol0, corr_mol1;
    const auto super_sys = testing::water(3);
    corr_mol0.push_back(super_sys[0]);
    corr_mol0.push_back(super_sys[1]);
    corr_mol0.push_back(super_sys[2]);
    corr_mol0.push_back(super_sys[3]);
    corr_mol0.push_back(super_sys[4]);
    corr_mol0.push_back(super_sys[5]);
    auto corr_aos0 = testing::sto3g(corr_mol0);

    corr_mol1.push_back(super_sys[0]);
    corr_mol1.push_back(super_sys[1]);
    corr_mol1.push_back(super_sys[2]);
    corr_mol1.push_back(super_sys[6]);
    corr_mol1.push_back(super_sys[7]);
    corr_mol1.push_back(super_sys[8]);
    auto corr_aos1 = testing::sto3g(corr_mol1);

    auto nmer0 = water3.nmer(0);
    auto nmer1 = water3.nmer(1);

    auto aos0 = water3.ao_basis_set(nmer0);
    auto aos1 = water3.ao_basis_set(nmer1);

    TermPIMPL::coefficient_type c0 = 1.2, c1 = 2.3;
    TermPIMPL::size_type ne0 = 0, ne1 = 2;
    TermPIMPL p(nmer0, aos0, ne0, c0);
    TermPIMPL diff_nmer(nmer1, aos0, ne0, c0);
    TermPIMPL diff_aos(nmer0, aos1, ne0, c0);
    TermPIMPL diff_nes(nmer0, aos0, ne1, c0);
    TermPIMPL diff_cs(nmer0, aos0, ne0, c1);

    SECTION("Ctor") {
        REQUIRE(p.m_nmer == nmer0);
        REQUIRE(p.m_aos == aos0);
        REQUIRE(p.m_n_electrons == ne0);
        REQUIRE(p.m_coef == c0);

        REQUIRE(diff_nmer.m_nmer == nmer1);
        REQUIRE(diff_nmer.m_aos == aos0);
        REQUIRE(diff_nmer.m_n_electrons == ne0);
        REQUIRE(diff_nmer.m_coef == c0);

        REQUIRE(diff_aos.m_nmer == nmer0);
        REQUIRE(diff_aos.m_aos == aos1);
        REQUIRE(diff_aos.m_n_electrons == ne0);
        REQUIRE(diff_aos.m_coef == c0);

        REQUIRE(diff_nes.m_nmer == nmer0);
        REQUIRE(diff_nes.m_aos == aos0);
        REQUIRE(diff_nes.m_n_electrons == ne1);
        REQUIRE(diff_nes.m_coef == c0);

        REQUIRE(diff_cs.m_nmer == nmer0);
        REQUIRE(diff_cs.m_aos == aos0);
        REQUIRE(diff_cs.m_n_electrons == ne0);
        REQUIRE(diff_cs.m_coef == c1);
    }

    SECTION("ao_basis_set()") {
        REQUIRE(p.ao_basis_set() == corr_aos0);
        REQUIRE(diff_nmer.ao_basis_set() == corr_aos0);
        REQUIRE(diff_aos.ao_basis_set() == corr_aos1);
        REQUIRE(diff_nes.ao_basis_set() == corr_aos0);
        REQUIRE(diff_cs.ao_basis_set() == corr_aos0);
    }

    SECTION("molecule()") {
        REQUIRE(p.molecule() == corr_mol0);
        REQUIRE(diff_nmer.molecule() == corr_mol1);
        REQUIRE(diff_aos.molecule() == corr_mol0);
        REQUIRE(diff_nes.molecule() == corr_mol0);
        REQUIRE(diff_cs.molecule() == corr_mol0);
    }

    SECTION("clone") {
        auto p_copy = p.clone();
        REQUIRE(*p_copy == p);

        auto diff_nmer_copy = diff_nmer.clone();
        REQUIRE(*diff_nmer_copy == diff_nmer);

        auto diff_aos_copy = diff_aos.clone();
        REQUIRE(*diff_aos_copy == diff_aos);

        auto diff_nes_copy = diff_nes.clone();
        REQUIRE(*diff_nes_copy == diff_nes);

        auto diff_cs_copy = diff_cs.clone();
        REQUIRE(*diff_cs_copy == diff_cs);
    }

    SECTION("operator==") {
        REQUIRE(p == TermPIMPL(nmer0, aos0, ne0, c0));
        REQUIRE_FALSE(p == diff_nmer);
        REQUIRE_FALSE(p == diff_aos);
        REQUIRE_FALSE(p == diff_nes);
        REQUIRE_FALSE(p == diff_cs);
    }
}
