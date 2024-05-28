/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
