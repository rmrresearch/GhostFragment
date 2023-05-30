// #include "caps.hpp"
// #include <catch2/catch.hpp>

// using namespace testing;

// /* Testing of capped_water and capped_water_needing_caps explicitly tests the
//  * 0, 1, 2, and 3 water scenarios, assuming it will continue to work for more
//  * water molecules. Internally the caps are built by caps_for_water and
//  * caps_for_water_needing_caps so we test those first.
//  *
//  * Internally capped_water/capped_water_needing_caps rely on
//  * fragmented_water/fragmented_water_needing_caps, which have already been
//  unit
//  * tested (and work). Aside from that it's a matter copying the fragments
//  into
//  * the result and pairing them with the right caps; both of which should be
//  * adequatly tested by comparing against hard-coded values.
//  */

// TEST_CASE("caps_for_water") {
//     ghostfragment::Caps caps;
//     ghostfragment::type::fragmented_caps corr(caps);
//     corr.insert(corr.new_subset());

//     REQUIRE(ghostfragment::type::fragmented_caps(caps) == caps_for_water(0));
//     REQUIRE(corr == caps_for_water(1));
//     REQUIRE(corr == caps_for_water(2));
//     REQUIRE(corr == caps_for_water(3));
// }

// TEST_CASE("caps_for_water_needing_caps") {
//     ghostfragment::Caps caps;
//     using atom_type = typename ghostfragment::type::nuclei_set::value_type;

//     SECTION("Zero waters") {
//         ghostfragment::type::fragmented_caps corr(caps);
//         REQUIRE(corr == caps_for_water_needing_caps(0));
//     }

//     SECTION("One water") {
//         auto frags = fragmented_water_needing_caps(1);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[2].coords()), 2);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[0].coords()), 0);

//         ghostfragment::type::fragmented_caps corr(caps);
//         auto s0 = corr.new_subset();
//         s0.insert(0);

//         auto s1 = corr.new_subset();
//         s1.insert(1);

//         corr.insert(s0);
//         corr.insert(s1);

//         REQUIRE(corr == caps_for_water_needing_caps(1));
//     }

//     SECTION("Two waters") {
//         auto frags = fragmented_water_needing_caps(2);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[2].coords()), 2);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[0].coords()), 0);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[5].coords()), 5);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[3].coords()), 3);

//         ghostfragment::type::fragmented_caps corr(caps);
//         auto s0 = corr.new_subset();
//         s0.insert(0);

//         auto s1 = corr.new_subset();
//         s1.insert(1);

//         auto s2 = corr.new_subset();
//         s2.insert(2);

//         auto s3 = corr.new_subset();
//         s3.insert(3);

//         corr.insert(s0);
//         corr.insert(s1);
//         corr.insert(s2);
//         corr.insert(s3);

//         REQUIRE(corr == caps_for_water_needing_caps(2));
//     }

//     SECTION("Three waters") {
//         auto frags = fragmented_water_needing_caps(3);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[2].coords()), 2);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[0].coords()), 0);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[5].coords()), 5);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[3].coords()), 3);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[8].coords()), 8);
//         caps.add_cap(atom_type("H", 1ul, frags.object()[6].coords()), 6);

//         ghostfragment::type::fragmented_caps corr(caps);
//         auto s0 = corr.new_subset();
//         s0.insert(0);

//         auto s1 = corr.new_subset();
//         s1.insert(1);

//         auto s2 = corr.new_subset();
//         s2.insert(2);

//         auto s3 = corr.new_subset();
//         s3.insert(3);

//         auto s4 = corr.new_subset();
//         s4.insert(4);

//         auto s5 = corr.new_subset();
//         s5.insert(5);

//         corr.insert(s0);
//         corr.insert(s1);
//         corr.insert(s2);
//         corr.insert(s3);
//         corr.insert(s4);
//         corr.insert(s5);

//         REQUIRE(corr == caps_for_water_needing_caps(3));
//     }
// }

// TEST_CASE("capped_water") {
//     ghostfragment::pt::CappedFragmentsTraits::result_type corr;

//     SECTION("Zero waters") { REQUIRE(corr == capped_water(0)); }

//     SECTION("One water") {
//         auto caps = caps_for_water(1);

//         auto water1 = fragmented_water(1);
//         corr.emplace(water1[0], caps[0]);
//         REQUIRE(corr == capped_water(1));
//     }

//     SECTION("Two waters") {
//         auto caps = caps_for_water(2);

//         auto water2 = fragmented_water(2);
//         corr.emplace(water2[0], caps[0]);
//         corr.emplace(water2[1], caps[0]);
//         REQUIRE(corr == capped_water(2));
//     }

//     SECTION("Three waters") {
//         auto caps = caps_for_water(3);

//         auto water3 = fragmented_water(3);
//         corr.emplace(water3[0], caps[0]);
//         corr.emplace(water3[1], caps[0]);
//         corr.emplace(water3[2], caps[0]);
//         REQUIRE(corr == capped_water(3));
//     }
// }

// TEST_CASE("capped_water_needing_caps") {
//     ghostfragment::pt::CappedFragmentsTraits::result_type corr;

//     SECTION("Zero waters") { REQUIRE(corr == capped_water_needing_caps(0)); }

//     SECTION("One water") {
//         auto frags      = fragmented_water_needing_caps(1);
//         const auto caps = caps_for_water_needing_caps(1);

//         corr.emplace(frags[0], caps[0]);
//         corr.emplace(frags[1], caps[1]);
//         REQUIRE(corr == capped_water_needing_caps(1));
//     }

//     SECTION("Two waters") {
//         auto frags      = fragmented_water_needing_caps(2);
//         const auto caps = caps_for_water_needing_caps(2);

//         corr.emplace(frags[0], caps[0]);
//         corr.emplace(frags[1], caps[1]);
//         corr.emplace(frags[2], caps[2]);
//         corr.emplace(frags[3], caps[3]);
//         REQUIRE(corr == capped_water_needing_caps(2));
//     }

//     SECTION("Three waters") {
//         auto frags      = fragmented_water_needing_caps(3);
//         const auto caps = caps_for_water_needing_caps(3);

//         corr.emplace(frags[0], caps[0]);
//         corr.emplace(frags[1], caps[1]);
//         corr.emplace(frags[2], caps[2]);
//         corr.emplace(frags[3], caps[3]);
//         corr.emplace(frags[4], caps[4]);
//         corr.emplace(frags[5], caps[5]);
//         REQUIRE(corr == capped_water_needing_caps(3));
//     }
// }
