#include "../../test_ghostfragment.hpp"
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
    }

    SECTION("swap") {
        Term copy_default(defaulted);
        Term copy_t(t);

        defaulted.swap(t);
        REQUIRE(t == copy_default);
        REQUIRE(defaulted == copy_t);
    }

    SECTION("operator==") {
        REQUIRE(t == Term(nmer0, aos0, c0));
        REQUIRE_FALSE(t != Term(nmer0, aos0, c0));

        REQUIRE_FALSE(p == diff_nmer);
        REQUIRE_FALSE(p == diff_aos);
        REQUIRE_FALSE(p == diff_cs);
    }
}