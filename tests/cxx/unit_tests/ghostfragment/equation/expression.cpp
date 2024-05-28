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
// #include <ghostfragment/equation/equation.hpp>

// using namespace ghostfragment::equation;

// TEST_CASE("Expression") {
//     auto water3 = testing::water_nmer_system(3, 2);
//     auto nmer   = water3.nmer(0);
//     auto aos    = water3.ao_basis_set(nmer);

//     using term_type = Expression::term_type;
//     term_type t0    = make_term(nmer, aos, 1, 1.23);
//     term_type t1    = make_term(nmer, aos, 1, 3.14);

//     Expression defaulted;
//     Expression i0, i1;
//     i0.add_term(t0);
//     i1.add_term(t1);

//     SECTION("CTor") {
//         SECTION("default") {
//             REQUIRE(defaulted.empty());
//             REQUIRE(defaulted.size() == 0);
//         }

//         SECTION("copy") {
//             Expression defaulted_copy(defaulted);
//             REQUIRE(defaulted_copy == defaulted);

//             Expression i0_copy(i0);
//             REQUIRE(i0_copy == i0);

//             Expression i1_copy(i1);
//             REQUIRE(i1_copy == i1);
//         }

//         SECTION("move") {
//             Expression defaulted_copy(defaulted);
//             Expression defaulted_move(std::move(defaulted));
//             REQUIRE(defaulted_copy == defaulted_move);

//             Expression i0_copy(i0);
//             Expression i0_move(std::move(i0));
//             REQUIRE(i0_copy == i0_move);

//             Expression i1_copy(i1);
//             Expression i1_move(std::move(i1));
//             REQUIRE(i1_copy == i1_move);
//         }

//         SECTION("copy assignment") {
//             Expression defaulted_copy;
//             auto pdefaulted_copy = &(defaulted_copy = defaulted);
//             REQUIRE(pdefaulted_copy == &defaulted_copy);
//             REQUIRE(defaulted_copy == defaulted);

//             Expression i0_copy;
//             auto pi0_copy = &(i0_copy = i0);
//             REQUIRE(pi0_copy == &i0_copy);
//             REQUIRE(i0_copy == i0);

//             Expression i1_copy;
//             auto pi1_copy = &(i1_copy = i1);
//             REQUIRE(pi1_copy == &i1_copy);
//             REQUIRE(i1_copy == i1);
//         }

//         SECTION("move assignment") {
//             Expression defaulted_copy(defaulted);
//             Expression defaulted_move;
//             auto pdefaulted_move = &(defaulted_move = std::move(defaulted));
//             REQUIRE(pdefaulted_move == &defaulted_move);
//             REQUIRE(defaulted_copy == defaulted_move);

//             Expression i0_copy(i0);
//             Expression i0_move;
//             auto pi0_move = &(i0_move = std::move(i0));
//             REQUIRE(pi0_move == &i0_move);
//             REQUIRE(i0_copy == i0_move);

//             Expression i1_copy(i1);
//             Expression i1_move;
//             auto pi1_move = &(i1_move = std::move(i1));
//             REQUIRE(pi1_move == &i1_move);
//             REQUIRE(i1_copy == i1_move);
//         }
//     }

//     SECTION("size") {
//         REQUIRE(defaulted.size() == 0);
//         REQUIRE(i0.size() == 1);
//         REQUIRE(i1.size() == 1);
//     }

//     SECTION("at") {
//         REQUIRE_THROWS_AS(defaulted.at(0), std::out_of_range);

//         REQUIRE(i0.at(0) == t0);
//         REQUIRE_THROWS_AS(i0.at(1), std::out_of_range);

//         REQUIRE(i1.at(0) == t1);
//         REQUIRE_THROWS_AS(i1.at(1), std::out_of_range);
//     }

//     SECTION("add_term(term)") {
//         defaulted.add_term(t0);
//         REQUIRE(defaulted == i0);

//         i0.add_term(t1);
//         REQUIRE(i0.size() == 2);
//         REQUIRE(i0.at(0) == t0);
//         REQUIRE(i0.at(1) == t1);
//     }

//     SECTION("empty") {
//         REQUIRE(defaulted.empty());
//         REQUIRE_FALSE(i0.empty());
//         REQUIRE_FALSE(i1.empty());
//     }

//     SECTION("swap") {
//         Expression i0_copy(i0);
//         Expression i1_copy(i1);

//         i0.swap(i1);
//         REQUIRE(i0 == i1_copy);
//         REQUIRE(i1 == i0_copy);
//     }

//     SECTION("operator==/operator!=") {
//         // defaulted compared to defaulted
//         REQUIRE(defaulted == Expression());
//         REQUIRE_FALSE(defaulted != Expression());

//         // defaulted compared to non-default
//         REQUIRE(defaulted != i0);
//         REQUIRE_FALSE(defaulted == i0);

//         // non-defaulted to non-defaulted with same state
//         Expression i0_2;
//         i0_2.add_term(t0);
//         REQUIRE(i0 == i0_2);
//         REQUIRE_FALSE(i0 != i0_2);

//         // non-defaulted to non-defaulted with different state
//         REQUIRE(i0 != i1);
//         REQUIRE_FALSE(i0 == i1);

//         // Order matters
//         i0.add_term(t1);
//         i1.add_term(t0);
//         REQUIRE(i0 != i1);
//         REQUIRE_FALSE(i0 == i1);
//     }
// }
