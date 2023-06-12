#include "../../../../../src/ghostfragment/connectivity/hydrocarbon_fragment.hpp"
#include "hc_fragment.hpp"

using namespace testing;

TEST_CASE("Hydrocarbon Fragment"){
    SECTION("Ethane fragment (size 1)"){
        chemist::FragmentedNuclei corr(frag_two_two());
        REQUIRE(corr == hydrocarbon_fragmented_nuclei(2, 1));
    }
}