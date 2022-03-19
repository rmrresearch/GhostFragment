// #include "../test_ghostfragment.hpp"

// using namespace ghostfragment;
// using namespace testing;

// using frag_pt = ghostfragment::pt::CappedFragments;
// using nmer_pt = ghostfragment::pt::CappedNMers;

// using capped_frags_traits = pt::CappedFragmentsTraits;
// using frags_type   = std::decay_t<typename capped_frags_traits::input_type>;
// using capped_frags = typename capped_frags_traits::result_type;

// using capped_nmers_traits = pt::CappedNMersTraits;
// using return_type         = typename capped_nmers_traits::result_type;

// namespace {

// template<typename NMersType>
// auto flatten(NMersType&& nmers) {
//     const auto& frags = nmers.object();
//     frags_type flattened_nmers(frags.object());

//     for(const auto& nmer : nmers) {
//         auto frag = flattened_nmers.new_subset();
//         for(const auto& i : nmer) frag += frags[i];
//         flattened_nmers.insert(frag);
//     }
//     return flattened_nmers;
// }

// template<typename NMersType>
// auto corr_caps(NMersType&& nmers, std::size_t n_waters) {
//     const auto& frags = nmers.object();
//     const auto& mol   = frags.object();
//     frags_type caps(mol);
//     frags_type flattened_nmers(mol);

//     capped_frags rv;
//     return_type corr;
//     for(const auto& nmer : nmers) {
//         auto frag = flattened_nmers.new_subset();
//         auto cap  = caps.new_subset();
//         for(const auto& i : nmer) frag += frags[i];
//         for(auto atom : frag) {
//             if(atom % 3 == 0) { // Has the HO part of a water
//                 // If doesn't have the 2nd H add it
//                 if(!frag.count(mol.at(atom + 2))) cap.insert(atom + 2);
//             } else if(atom % 3 == 2) { // Has the 2nd H
//                 // If doesn't have the O add it
//                 if(!frag.count(mol.at(atom - 1))) cap.insert(atom - 1);
//             }
//         }
//         rv.emplace(frag, cap);
//         corr.emplace(nmer, cap);
//     }
//     return std::make_tuple(std::move(rv), std::move(corr));
// }

// } // namespace

// /* Testing Strategy.
//  *
//  * The NMer Capper module really does three things:
//  * - flattens the n-mers,
//  * - calls a submodule that caps the flattened fragments, and
//  * - maps the results back to the n-mers.
//  *
//  * If we assume the submodule works correctly we need to test:
//  * - that the n-mers get flattened correctly (done inside the lambda module)
//  * - we forward the flattened n-mers correcty (same check)
//  * - we map the results back correctly (final check)
//  *
//  */
// TEST_CASE("NMer Capping") {
//     auto mm   = initialize();
//     auto& mod = mm.at("NMer Capper");

//     SECTION("Water monomers") {
//         for(std::size_t n_waters = 1; n_waters < 4; ++n_waters) {
//             SECTION("N = " + std::to_string(n_waters)) {
//                 auto water_n = fragmented_water(n_waters);
//                 for(std::size_t n = 1; n <= 4; ++n) {
//                     SECTION("n = " + std::to_string(n)) {
//                         auto nmers = make_nmers(water_n, n);

//                         // No caps needed, so just empty sets
//                         auto empty_set = fragmented_water(0).new_subset();

//                         auto submod = pluginplay::make_lambda<frag_pt>(
//                           [=](auto&& frags_in) {
//                               REQUIRE(frags_in == flatten(nmers));
//                               capped_frags rv;
//                               for(const auto& frag : frags_in)
//                                   rv.emplace(frag, empty_set);
//                               return rv;
//                           });

//                         return_type corr;
//                         for(const auto& nmer_i : nmers)
//                             corr.emplace(nmer_i, empty_set);

//                         mod.change_submod("Fragment Capper", submod);
//                         const auto& [capped_nmers] =
//                         mod.run_as<nmer_pt>(nmers); REQUIRE(capped_nmers ==
//                         corr);
//                     }
//                 }
//             }
//         }
//     }

//     SECTION("(HO) (H) monomers") {
//         for(std::size_t n_waters = 1; n_waters < 4; ++n_waters) {
//             SECTION("N = " + std::to_string(n_waters)) {
//                 auto water_n = fragmented_water_needing_caps(n_waters);
//                 for(std::size_t n = 1; n <= 4; ++n) {
//                     SECTION("n = " + std::to_string(n)) {
//                         auto nmers = make_nmers(water_n, n);

//                         auto&& [rv, corr] = corr_caps(nmers, n_waters);

//                         auto submod = pluginplay::make_lambda<frag_pt>(
//                           [=](auto&& frags_in) {
//                               REQUIRE(frags_in == flatten(nmers));
//                               return rv;
//                           });

//                         mod.change_submod("Fragment Capper", submod);
//                         const auto& [capped_nmers] =
//                         mod.run_as<nmer_pt>(nmers); REQUIRE(capped_nmers ==
//                         corr);
//                     }
//                 }
//             }
//         }
//     }
// }
