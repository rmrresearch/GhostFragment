// #include "../test_ghostfragment.hpp"

// using my_pt       = ghostfragment::pt::NMerScreener;
// using capped_type = ghostfragment::pt::CappedFragmentsTraits::result_type;

// using namespace ghostfragment;
// using namespace testing;

// /* Testing strategy:
//  *
//  * We consider normal water monomers and water monomers which have been
//  * fragmented into OH and H fragments. The former have no caps, the latter
//  have
//  * caps at the location of the missing atom. We consider two thresholds for
//  * screening: essentially none (defaul, cut-off is largest double possible)
//  and
//  * a cut-off of 0. With the former threshold we get all n-mers regardless of
//  * which set of fragments we use. With the 0 threshold and the normal water
//  * monomers we get the fragments back, whereas the 0 threshold and the
//  * fragmented waters includes some dimers (namely dimers that form the
//  original
//  * water molecules).
//  *
//  * N.B. When caps are considered the fragmented waters form a set of
//  overlapping
//  * fragments, which is why we get some dimers back even for a zero threshold.
//  *
//  * N.B. It's worth noting that the zero-threshold avoids the same branches as
//  * any intermediate threshold value would suggesting that they should all
//  work
//  * too.
//  */

// TEST_CASE("Distance Screening") {
//     auto mm  = testing::initialize();
//     auto mod = mm.at("Screen by minimum distance");

//     SECTION("Water monomers") {
//         for(std::size_t n_waters = 2; n_waters < 4; ++n_waters) {
//             SECTION("N = " + std::to_string(n_waters)) {
//                 SECTION("Normal Connectivity") {
//                     auto water_n = fragmented_water(n_waters);

//                     // No caps needed, so just empty sets
//                     capped_type capped;
//                     auto empty_set = fragmented_water(0).new_subset();
//                     for(const auto& frag_i : water_n)
//                         capped.emplace(frag_i, empty_set);

//                     SECTION("No cut-off") {
//                         const auto& [dimers] = mod.run_as<my_pt>(capped, 2u);
//                         REQUIRE(dimers == make_nmers(water_n, 2u));

//                         if(n_waters == 3) {
//                             const auto& [nmers] = mod.run_as<my_pt>(capped,
//                             3u); REQUIRE(nmers == make_nmers(water_n, 3u));
//                         }
//                     }

//                     SECTION("Cut-off of 0") {
//                         mod.change_input("threshold", 0.0);

//                         const auto& [dimers] = mod.run_as<my_pt>(capped, 2u);
//                         REQUIRE(dimers == make_nmers(water_n, 1u));

//                         if(n_waters == 3) {
//                             const auto& [nmers] = mod.run_as<my_pt>(capped,
//                             3u); REQUIRE(nmers == make_nmers(water_n, 1u));
//                         }
//                     }
//                 }

//                 SECTION("HO H fragmentation") {
//                     auto water_n = fragmented_water_needing_caps(n_waters);
//                     const auto N = water_n.size();

//                     // Make correct answer
//                     auto capped = capped_water(n_waters);

//                     SECTION("No cut-off") {
//                         const auto& [nmers] = mod.run_as<my_pt>(capped, 2u);
//                         REQUIRE(nmers == make_nmers(water_n, 2u));

//                         if(N > 2) {
//                             const auto& [nmers] = mod.run_as<my_pt>(capped,
//                             3u); REQUIRE(nmers == make_nmers(water_n, 3ul));
//                         }
//                     }

//                     SECTION("Cut-off == 0") {
//                         mod.change_input("threshold", 0.0);
//                         type::nmers corr(water_n);

//                         SECTION("n == 2") {
//                             for(std::size_t i = 0; i < N; ++i) {
//                                 if(i % 2 == 1) continue;
//                                 auto dimer = corr.new_subset();
//                                 dimer.insert(i);
//                                 dimer.insert(i + 1);
//                                 corr.insert(dimer);
//                             }
//                             const auto& [nmers] = mod.run_as<my_pt>(capped,
//                             2u); REQUIRE(nmers == corr);
//                         }

//                         SECTION("n == 2") {
//                             for(std::size_t i = 0; i < N; ++i) {
//                                 if(i % 2 == 1) continue;
//                                 auto dimer = corr.new_subset();
//                                 dimer.insert(i);
//                                 dimer.insert(i + 1);
//                                 corr.insert(dimer);
//                             }
//                             if(N > 2) {
//                                 const auto& [nmers] =
//                                   mod.run_as<my_pt>(capped, 3u);
//                                 REQUIRE(nmers == corr);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }
