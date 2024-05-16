// #include "connectivity.hpp"
// #include <catch2/catch.hpp>

// using namespace testing;

// /* For unit testing we test against the hard-coded answers for 0, 1, 2, and 3
//  * water molecules. It's assumed that it if it works for those scenarios it'll
//  * work for any other scenario as well.
//  */

// TEST_CASE("water_connectivity") {
//     using ctable_type = simde::type::connectivity_table;

//     SECTION("Zero waters") {
//         ctable_type corr(0);
//         REQUIRE(corr == water_connectivity(0));
//     }

//     SECTION("One water") {
//         ctable_type corr(3);
//         corr.add_bond(0, 1);
//         corr.add_bond(0, 2);
//         REQUIRE(corr == water_connectivity(1));
//     }

//     SECTION("Two waters") {
//         ctable_type corr(6);
//         corr.add_bond(0, 1);
//         corr.add_bond(0, 2);
//         corr.add_bond(3, 4);
//         corr.add_bond(3, 5);
//         REQUIRE(corr == water_connectivity(2));
//     }

//     SECTION("Three waters") {
//         ctable_type corr(9);
//         corr.add_bond(0, 1);
//         corr.add_bond(0, 2);
//         corr.add_bond(3, 4);
//         corr.add_bond(3, 5);
//         corr.add_bond(6, 7);
//         corr.add_bond(6, 8);
//         REQUIRE(corr == water_connectivity(3));
//     }
// }
