// #include "test_ghostfragment.hpp"
// #include <ghostfragment/nmer_system.hpp>

// using namespace ghostfragment;
// using namespace testing;

// TEST_CASE("NMerSystem") {
//     auto dimers  = make_nmers(fragmented_water(3), 2);
//     auto trimers = make_nmers(fragmented_water(4), 3);

//     auto frags = testing::fragmented_water_system(3);

//     NMerSystem defaulted;
//     NMerSystem has_value(frags, dimers);

//     SECTION("CTors") {
//         SECTION("Default") { REQUIRE(defaulted.size() == 0); }
//         SECTION("Value") {
//             REQUIRE(has_value.size() == 3);
//             REQUIRE(has_value.fragments() == frags);
//         }
//         SECTION("Copy") {
//             NMerSystem default_copy(defaulted);
//             REQUIRE(default_copy == defaulted);

//             NMerSystem copy(has_value);
//             REQUIRE(copy == has_value);
//         }
//         SECTION("Move") {
//             NMerSystem default_moved(std::move(defaulted));
//             REQUIRE(default_moved == NMerSystem{});

//             NMerSystem corr(has_value);
//             NMerSystem value_moved(std::move(has_value));
//             REQUIRE(corr == value_moved);
//         }
//         SECTION("Copy Assignment") {
//             NMerSystem copy;
//             auto pcopy = &(copy = has_value);
//             REQUIRE(pcopy == &copy);
//             REQUIRE(copy == has_value);
//         }
//         SECTION("Move Assignment") {
//             NMerSystem default_moved;
//             auto pdefault = &(default_moved = std::move(defaulted));
//             REQUIRE(pdefault == &default_moved);
//             REQUIRE(default_moved == NMerSystem{});

//             NMerSystem corr(has_value);
//             NMerSystem value_moved;
//             auto pvalue = &(value_moved = std::move(has_value));
//             REQUIRE(pvalue == &value_moved);
//             REQUIRE(corr == value_moved);
//         }
//     }

//     SECTION("size") {
//         REQUIRE(defaulted.size() == 0);
//         REQUIRE(has_value.size() == 3);
//     }

//     SECTION("new_nmer") {
//         REQUIRE_THROWS_AS(defaulted.new_nmer(), std::runtime_error);
//         REQUIRE(has_value.new_nmer() == dimers.new_subset());
//     }

//     SECTION("nmer") {
//         REQUIRE_THROWS_AS(defaulted.nmer(0), std::out_of_range);
//         REQUIRE(has_value.nmer(0) == dimers[0]);
//         REQUIRE(has_value.nmer(1) == dimers[1]);
//         REQUIRE(has_value.nmer(2) == dimers[2]);
//         REQUIRE_THROWS_AS(has_value.nmer(3), std::out_of_range);
//     }

//     SECTION("count") {
//         REQUIRE_FALSE(defaulted.count(dimers[0]));

//         REQUIRE(has_value.count(dimers[0]));
//         REQUIRE(has_value.count(dimers[1]));
//         REQUIRE(has_value.count(dimers[2]));
//         REQUIRE_FALSE(has_value.count(dimers[0] + dimers[1]));
//         REQUIRE_FALSE(has_value.count(trimers[0]));
//     }

//     SECTION("fragments") {
//         REQUIRE_THROWS_AS(defaulted.fragments(), std::runtime_error);
//         REQUIRE(has_value.fragments() == frags);
//     }

//     // Make AOs for each water
//     auto water0_aos = frags.ao_basis_set(frags.fragment(0));
//     auto water1_aos = frags.ao_basis_set(frags.fragment(1));
//     auto water2_aos = frags.ao_basis_set(frags.fragment(2));

//     SECTION("ao_basis_set(nmer)") {
//         using rerror = std::runtime_error;
//         REQUIRE_THROWS_AS(defaulted.ao_basis_set(dimers[0]), rerror);

//         auto d0_aos = water0_aos + water1_aos;
//         REQUIRE(has_value.ao_basis_set(dimers[0]) == d0_aos);

//         auto d1_aos = water0_aos + water2_aos;
//         REQUIRE(has_value.ao_basis_set(dimers[1]) == d1_aos);

//         auto d2_aos = water1_aos + water2_aos;
//         REQUIRE(has_value.ao_basis_set(dimers[2]) == d2_aos);

//         using oerror = std::out_of_range;
//         REQUIRE_THROWS_AS(has_value.ao_basis_set(trimers[0]), oerror);
//     }

//     SECTION("ao_basis_set(frag)") {
//         using rerror = std::runtime_error;
//         REQUIRE_THROWS_AS(defaulted.ao_basis_set(frags.fragment(0)), rerror);

//         REQUIRE(has_value.ao_basis_set(frags.fragment(0)) == water0_aos);
//         REQUIRE(has_value.ao_basis_set(frags.fragment(1)) == water1_aos);
//         REQUIRE(has_value.ao_basis_set(frags.fragment(2)) == water2_aos);

//         using oerror   = std::out_of_range;
//         auto bad_water = fragmented_water(4)[0];
//         REQUIRE_THROWS_AS(has_value.ao_basis_set(bad_water), oerror);
//     }

//     SECTION("n_electrons(nmer)") {
//         REQUIRE_THROWS_AS(defaulted.n_electrons(dimers[0]), std::runtime_error);
//         REQUIRE(has_value.n_electrons(dimers[0]) == 20);
//         REQUIRE(has_value.n_electrons(dimers[1]) == 20);
//         REQUIRE(has_value.n_electrons(dimers[2]) == 20);
//         REQUIRE_THROWS_AS(has_value.n_electrons(trimers[0]), std::out_of_range);
//     }

//     SECTION("n_electrons(frag)") {
//         auto bad_water = fragmented_water(4)[0];
//         REQUIRE_THROWS_AS(defaulted.n_electrons(bad_water), std::runtime_error);
//         REQUIRE(has_value.n_electrons(frags.fragment(0)) == 10);
//         REQUIRE(has_value.n_electrons(frags.fragment(1)) == 10);
//         REQUIRE(has_value.n_electrons(frags.fragment(2)) == 10);
//         REQUIRE_THROWS_AS(has_value.n_electrons(bad_water), std::out_of_range);
//     }

//     SECTION("Comparisons") {
//         // default is the same as default
//         REQUIRE(defaulted == NMerSystem{});
//         REQUIRE_FALSE(defaulted != NMerSystem{});

//         // Default != stateful
//         REQUIRE_FALSE(has_value == defaulted);
//         REQUIRE(has_value != defaulted);

//         // Same n-mers and fragments
//         REQUIRE(has_value == NMerSystem(frags, dimers));
//         REQUIRE_FALSE(has_value != NMerSystem(frags, dimers));

//         // Different fragments
//         auto empty_frags = fragmented_water_system(0);
//         REQUIRE_FALSE(has_value == NMerSystem(empty_frags, dimers));
//         REQUIRE(has_value != NMerSystem(empty_frags, dimers));

//         // Different n-mers
//         REQUIRE_FALSE(has_value == NMerSystem(frags, trimers));
//         REQUIRE(has_value != NMerSystem(frags, trimers));
//     }
// }
