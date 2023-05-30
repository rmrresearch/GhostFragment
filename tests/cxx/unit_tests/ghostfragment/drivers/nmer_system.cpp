// #include "../test_ghostfragment.hpp"

// using namespace ghostfragment;
// using namespace testing;

// using nmer_screener_pt = pt::NMerScreener;
// using mod_pt           = pt::NMerSystem;
// using traits_type      = pt::NMerSystemTraits;

// TEST_CASE("NMerSystem Module") {
//     auto mm  = initialize();
//     auto mod = mm.at("NMerSystem Driver");

//     auto monomer = fragmented_water_system(1);
//     auto nmers   = make_nmers(monomer.frags(), 1);

//     auto f2n = pluginplay::make_lambda<nmer_screener_pt>(
//       [=](auto&& frags_in, auto&& n_in) {
//           for(const auto& [frag, cap] : frags_in)
//               REQUIRE(cap == monomer.caps(frag));
//           REQUIRE(n_in == 1);
//           return nmers;
//       });

//     traits_type::result_type corr(monomer, nmers);

//     mod.change_submod("NMer Screener", f2n);

//     const auto& [nmer_system] = mod.run_as<mod_pt>(monomer, 1u);
//     REQUIRE(nmer_system == corr);

//     REQUIRE_THROWS_AS(mod.run_as<mod_pt>(monomer, 2u), std::runtime_error);
// }
