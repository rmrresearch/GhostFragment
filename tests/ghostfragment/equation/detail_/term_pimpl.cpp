#include "../../test_ghostfragment.hpp"
#include <ghostfragment/equation/detail_/term_pimpl.hpp>

using namespace ghostfragment::equation::detail_;

TEST_CASE("TermPIMPL"){
    auto water3 = testing::water_nmer_system(3, 2);
    auto nmer0 = water3.nmer(0);
    auto nmer1 = water3.nmer(1);

    auto aos0 = water3.ao_basis_set(nmer0);
    auto aos1 = water3.ao_basis_set(nmer1);

    TermPIMPL::coefficient_type c0 = 1.2, c1 = 2.3;

    TermPIMPL p(nmer0, aos0, c0);
    TermPIMPL diff_nmer(nmer1, aos0, c0);
    TermPIMPL diff_aos(nmer0, aos1, c0);
    TermPIMPL diff_cs(nmer0, aos0, c1);

    SECTION("Ctor"){
        REQUIRE(p.m_nmer == nmer0);
        REQUIRE(p.m_aos == aos0);
        REQUIRE(p.m_coef == c0);

        REQUIRE(diff_nmer.m_nmer == nmer1);
        REQUIRE(diff_nmer.m_aos == aos0);
        REQUIRE(diff_nmer.m_coef == c0);

        REQUIRE(diff_aos.m_nmer == nmer0);
        REQUIRE(diff_aos.m_aos == aos1);
        REQUIRE(diff_aos.m_coef == c0);

        REQUIRE(diff_cs.m_nmer == nmer0);
        REQUIRE(diff_cs.m_aos == aos0);
        REQUIRE(diff_cs.m_coef == c1);
    }

    SECTION("clone"){
        auto p_copy = p.clone();
        REQUIRE(*p_copy == p);

        auto diff_nmer_copy = diff_nmer.clone();
        REQUIRE(*diff_nmer_copy == diff_nmer);

        auto diff_aos_copy = diff_aos.clone();
        REQUIRE(*diff_aos_copy == diff_aos);

        auto diff_cs_copy = diff_cs.clone();
        REQUIRE(*diff_cs_copy == diff_cs);
    }

    SECTION("operator==") {
        REQUIRE(p == TermPIMPL(nmer0, aos0, c0));
        REQUIRE_FALSE(p == diff_nmer);
        REQUIRE_FALSE(p == diff_aos);
        REQUIRE_FALSE(p == diff_cs);
    }
}