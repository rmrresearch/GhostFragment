#include "hydrocarbon.hpp"
#include <catch2/catch.hpp>
#include <hydrocarbon.h>

using namespace testing;

TEST_CASE("hydrocarbon_generator") {
    SECTION("Same number of atoms") {
        chemist::Molecule corr(Methane());
        REQUIRE(AreMoleculesEqual(corr, hydrocarbon(1)));
    }
    SECTION("Different number of atoms") {
        chemist::Molecule corr(Methane());
        REQUIRE(!AreMoleculesEqual(corr, hydrocarbon(2)));
    }
}