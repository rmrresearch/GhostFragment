#include "hc_fragment.hpp"
#include "hydrocarbon/hydrocarbon_fragment.hpp"

using namespace testing;

TEST_CASE("Hydrocarbon Fragment") {
    SECTION("Methane fragment (size 1)") {
        chemist::FragmentedNuclei corr(frag_methane_one());
        REQUIRE(corr == hydrocarbon_fragmented_nuclei(1, 1));
    }
    SECTION("Ethane fragment (size 1)") {
        chemist::FragmentedNuclei corr(frag_ethane_one());
        REQUIRE(corr == hydrocarbon_fragmented_nuclei(2, 1));
    }

    SECTION("Propane fragment (size 1)") {
        chemist::FragmentedNuclei corr(frag_propane_one());
        REQUIRE(corr == hydrocarbon_fragmented_nuclei(3, 1));
    }

    SECTION("Propane fragment (size 2)") {
        chemist::FragmentedNuclei corr(frag_propane_two());
        REQUIRE(corr == hydrocarbon_fragmented_nuclei(3, 2));
    }
}