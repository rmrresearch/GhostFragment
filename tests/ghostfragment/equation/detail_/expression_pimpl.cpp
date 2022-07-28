#include "../../test_ghostfragment.hpp"
#include <ghostfragment/equation/detail_/expression_pimpl.hpp>

using namespace ghostfragment::equation::detail_;

TEST_CASE("ExpressionPIMPL") {
    auto water3 = testing::water_nmer_system(3, 2);
    auto nmer   = water3.nmer(0);
    auto aos    = water3.ao_basis_set(nmer);

    using term_type = ExpressionPIMPL::term_type;
    term_type t(nmer, aos, 1.23);

    ExpressionPIMPL defaulted;
    ExpressionPIMPL p;
    p.m_terms.push_back(t);

    SECTION("Clone") {
        auto defaulted_copy = defaulted.clone();
        REQUIRE(*defaulted_copy == ExpressionPIMPL());

        auto p_copy = p.clone();
        REQUIRE(*p_copy == p);
    }

    SECTION("operator==") {
        REQUIRE(defaulted == ExpressionPIMPL());

        ExpressionPIMPL p_copy;
        p_copy.m_terms.push_back(t);
        REQUIRE(p == p_copy);

        // Different terms
        term_type t2(nmer, aos, 3.14);
        ExpressionPIMPL p2;
        p2.m_terms.push_back(t2);
        REQUIRE_FALSE(p == p2);
    }
}