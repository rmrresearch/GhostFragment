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
// #include <ghostfragment/property_types/expression.hpp>

// using namespace ghostfragment;
// using namespace ghostfragment::equation;
// using namespace testing;

// using my_pt = ghostfragment::pt::Expression;

// TEST_CASE("Many-Body Expansion") {
//     auto mm   = initialize();
//     auto& mod = mm.at("Many-Body Expansion");

//     using equation_type = ghostfragment::pt::ExpressionTraits::result_type;

//     SECTION("1-body w/ 1 water") {
//         auto waters    = water_nmer_system(1, 1);
//         const auto& w0 = waters.nmer(0);

//         equation_type corr;
//         corr.add_term(make_term(w0, waters.ao_basis_set(w0), 10, 1.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }

//     SECTION("1-body w/ 2 water") {
//         auto waters    = water_nmer_system(2, 1);
//         const auto& w0 = waters.nmer(0);
//         const auto& w1 = waters.nmer(1);

//         equation_type corr;
//         corr.add_term(make_term(w0, waters.ao_basis_set(w0), 10, 1.0));
//         corr.add_term(make_term(w1, waters.ao_basis_set(w1), 10, 1.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }

//     SECTION("2-body w/ 2 water") {
//         auto waters    = water_nmer_system(2, 2);
//         const auto& w0 = waters.nmer(0);

//         equation_type corr;
//         corr.add_term(make_term(w0, waters.ao_basis_set(w0), 20, 1.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }

//     SECTION("1-body w/ 3 water") {
//         auto waters    = water_nmer_system(3, 1);
//         const auto& w0 = waters.nmer(0);
//         const auto& w1 = waters.nmer(1);
//         const auto& w2 = waters.nmer(2);

//         equation_type corr;
//         corr.add_term(make_term(w0, waters.ao_basis_set(w0), 10, 1.0));
//         corr.add_term(make_term(w1, waters.ao_basis_set(w1), 10, 1.0));
//         corr.add_term(make_term(w2, waters.ao_basis_set(w2), 10, 1.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }

//     SECTION("2-body w/ 3 water") {
//         auto waters     = water_nmer_system(3, 2);
//         const auto& w01 = waters.nmer(0);
//         const auto& w02 = waters.nmer(1);
//         const auto& w12 = waters.nmer(2);
//         auto w0         = w01 ^ w02;
//         auto w1         = w01 ^ w12;
//         auto w2         = w02 ^ w12;
//         auto w0_aos     = waters.ao_basis_set(w0.begin(), w0.end());
//         auto w1_aos     = waters.ao_basis_set(w1.begin(), w1.end());
//         auto w2_aos     = waters.ao_basis_set(w2.begin(), w2.end());

//         equation_type corr;
//         corr.add_term(make_term(w0, w0_aos, 10, -1.0));
//         corr.add_term(make_term(w01, waters.ao_basis_set(w01), 20, 1.0));
//         corr.add_term(make_term(w02, waters.ao_basis_set(w02), 20, 1.0));
//         corr.add_term(make_term(w1, w1_aos, 10, -1.0));
//         corr.add_term(make_term(w12, waters.ao_basis_set(w12), 20, 1.0));
//         corr.add_term(make_term(w2, w2_aos, 10, -1.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }

//     SECTION("3-body w/ 3 water") {
//         auto waters    = water_nmer_system(3, 3);
//         const auto& w0 = waters.nmer(0);

//         equation_type corr;
//         corr.add_term(make_term(w0, waters.ao_basis_set(w0), 30, 1.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }

//     SECTION("1-body w/ 4 water") {
//         auto waters    = water_nmer_system(4, 1);
//         const auto& w0 = waters.nmer(0);
//         const auto& w1 = waters.nmer(1);
//         const auto& w2 = waters.nmer(2);
//         const auto& w3 = waters.nmer(3);

//         equation_type corr;
//         corr.add_term(make_term(w0, waters.ao_basis_set(w0), 10, 1.0));
//         corr.add_term(make_term(w1, waters.ao_basis_set(w1), 10, 1.0));
//         corr.add_term(make_term(w2, waters.ao_basis_set(w2), 10, 1.0));
//         corr.add_term(make_term(w3, waters.ao_basis_set(w3), 10, 1.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }

//     SECTION("2-body w/ 4 water") {
//         auto waters     = water_nmer_system(4, 2);
//         const auto& w01 = waters.nmer(0);
//         const auto& w02 = waters.nmer(1);
//         const auto& w03 = waters.nmer(2);
//         const auto& w12 = waters.nmer(3);
//         const auto& w13 = waters.nmer(4);
//         const auto& w23 = waters.nmer(5);

//         auto w0 = w01 ^ w02;
//         auto w1 = w01 ^ w12;
//         auto w2 = w02 ^ w12;
//         auto w3 = w03 ^ w13;

//         auto w0_basis = waters.ao_basis_set(w0.begin(), w0.end());
//         auto w1_basis = waters.ao_basis_set(w1.begin(), w1.end());
//         auto w2_basis = waters.ao_basis_set(w2.begin(), w2.end());
//         auto w3_basis = waters.ao_basis_set(w3.begin(), w3.end());

//         equation_type corr;
//         corr.add_term(make_term(w0, w0_basis, 10, -2.0));
//         corr.add_term(make_term(w01, waters.ao_basis_set(w01), 20, 1.0));
//         corr.add_term(make_term(w02, waters.ao_basis_set(w02), 20, 1.0));
//         corr.add_term(make_term(w03, waters.ao_basis_set(w03), 20, 1.0));
//         corr.add_term(make_term(w1, w1_basis, 10, -2.0));
//         corr.add_term(make_term(w12, waters.ao_basis_set(w12), 20, 1.0));
//         corr.add_term(make_term(w13, waters.ao_basis_set(w13), 20, 1.0));
//         corr.add_term(make_term(w2, w2_basis, 10, -2.0));
//         corr.add_term(make_term(w23, waters.ao_basis_set(w23), 20, 1.0));
//         corr.add_term(make_term(w3, w3_basis, 10, -2.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }

//     SECTION("3-body w/ 4 water") {
//         auto waters      = water_nmer_system(4, 3);
//         const auto& w012 = waters.nmer(0);
//         const auto& w013 = waters.nmer(1);
//         const auto& w023 = waters.nmer(2);
//         const auto& w123 = waters.nmer(3);

//         auto w01 = w012 ^ w013;
//         auto w02 = w012 ^ w023;
//         auto w03 = w013 ^ w023;
//         auto w12 = w012 ^ w123;
//         auto w13 = w013 ^ w123;
//         auto w23 = w023 ^ w123;

//         auto w01_basis = waters.ao_basis_set(w01.begin(), w01.end());
//         auto w02_basis = waters.ao_basis_set(w02.begin(), w02.end());
//         auto w03_basis = waters.ao_basis_set(w03.begin(), w03.end());
//         auto w12_basis = waters.ao_basis_set(w12.begin(), w12.end());
//         auto w13_basis = waters.ao_basis_set(w13.begin(), w13.end());
//         auto w23_basis = waters.ao_basis_set(w23.begin(), w23.end());

//         auto w0 = w01 ^ w02;
//         auto w1 = w01 ^ w12;
//         auto w2 = w02 ^ w12;
//         auto w3 = w03 ^ w13;

//         auto w0_basis = waters.ao_basis_set(w0.begin(), w0.end());
//         auto w1_basis = waters.ao_basis_set(w1.begin(), w1.end());
//         auto w2_basis = waters.ao_basis_set(w2.begin(), w2.end());
//         auto w3_basis = waters.ao_basis_set(w3.begin(), w3.end());

//         equation_type corr;
//         corr.add_term(make_term(w0, w0_basis, 10, 1.0));
//         corr.add_term(make_term(w01, w01_basis, 20, -1.0));
//         corr.add_term(make_term(w012, waters.ao_basis_set(w012), 30, 1.0));
//         corr.add_term(make_term(w013, waters.ao_basis_set(w013), 30, 1.0));
//         corr.add_term(make_term(w02, w02_basis, 20, -1.0));
//         corr.add_term(make_term(w023, waters.ao_basis_set(w023), 30, 1.0));
//         corr.add_term(make_term(w03, w03_basis, 20, -1.0));
//         corr.add_term(make_term(w1, w1_basis, 10, 1.0));
//         corr.add_term(make_term(w12, w12_basis, 20, -1.0));
//         corr.add_term(make_term(w123, waters.ao_basis_set(w123), 30, 1.0));
//         corr.add_term(make_term(w13, w13_basis, 20, -1.0));
//         corr.add_term(make_term(w2, w2_basis, 10, 1.0));
//         corr.add_term(make_term(w23, w23_basis, 20, -1.0));
//         corr.add_term(make_term(w3, w3_basis, 10, 1.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }

//     SECTION("4-body w/ 4 water") {
//         auto waters    = water_nmer_system(4, 4);
//         const auto& w0 = waters.nmer(0);

//         equation_type corr;
//         corr.add_term(make_term(w0, waters.ao_basis_set(w0), 40, 1.0));
//         const auto& [expression] = mod.run_as<my_pt>(waters);
//         REQUIRE(expression == corr);
//     }
// }
