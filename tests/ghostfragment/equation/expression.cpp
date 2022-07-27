#include "../test_ghostfragment.hpp"
#include <ghostfragment/equation/Expression.hpp>

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
    }
}