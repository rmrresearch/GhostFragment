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

// #include "test_ghostfragment.hpp"
// #include <ghostfragment/caps.hpp>

// TEST_CASE("Caps") {
//     ghostfragment::Caps defaulted;
//     auto non_default = testing::caps_for_water_needing_caps(2).object();

//     SECTION("size") {
//         REQUIRE(defaulted.size() == 0);
//         REQUIRE(non_default.size() == 4);
//     }

//     SECTION("count") {
//         REQUIRE_FALSE(defaulted.count(non_default[0]));

//         REQUIRE(non_default.count(non_default[0]));
//         REQUIRE(non_default.count(non_default[1]));
//         REQUIRE(non_default.count(non_default[2]));
//         REQUIRE(non_default.count(non_default[3]));

//         auto copy = non_default[2];
//         copy.Z()  = 3;
//         REQUIRE_FALSE(non_default.count(copy));
//     }

//     SECTION("add_cap") {
//         defaulted.add_cap(non_default[0], 0);
//         REQUIRE(defaulted[0] == non_default[0]);
//         REQUIRE(defaulted.replaced_atom(0) == 0);
//     }

//     SECTION("operator[]") {
//         REQUIRE(non_default[0] == non_default.nuclei()[0]);
//         REQUIRE(non_default[1] == non_default.nuclei()[1]);
//         REQUIRE(non_default[2] == non_default.nuclei()[2]);
//         REQUIRE(non_default[3] == non_default.nuclei()[3]);
//     }

//     SECTION("at") {
//         REQUIRE_THROWS_AS(defaulted.at(0), std::out_of_range);
//         REQUIRE(non_default.at(0) == non_default.nuclei()[0]);
//         REQUIRE(non_default.at(1) == non_default.nuclei()[1]);
//         REQUIRE(non_default.at(2) == non_default.nuclei()[2]);
//         REQUIRE(non_default.at(3) == non_default.nuclei()[3]);
//         REQUIRE_THROWS_AS(non_default.at(4), std::out_of_range);
//     }

//     SECTION("replaced_atom") {
//         REQUIRE_THROWS_AS(defaulted.replaced_atom(0), std::out_of_range);
//         REQUIRE(non_default.replaced_atom(0) == 2);
//         REQUIRE(non_default.replaced_atom(1) == 0);
//         REQUIRE(non_default.replaced_atom(2) == 5);
//         REQUIRE(non_default.replaced_atom(3) == 3);
//         REQUIRE_THROWS_AS(non_default.replaced_atom(4), std::out_of_range);
//     }

//     SECTION("nuclei") {
//         using nuclei_type = ghostfragment::type::nuclei_set;
//         REQUIRE(defaulted.nuclei() == nuclei_type{});
//         nuclei_type corr;
//         corr.push_back(non_default[0]);
//         corr.push_back(non_default[1]);
//         corr.push_back(non_default[2]);
//         corr.push_back(non_default[3]);
//         REQUIRE(non_default.nuclei() == corr);
//     }

//     SECTION("comparisons") {
//         auto a0 = non_default[0];
//         auto a1 = non_default[1];
//         ghostfragment::Caps rhs;

//         // Defaulted instances are same
//         REQUIRE(defaulted == rhs);
//         REQUIRE_FALSE(defaulted != rhs);

//         // Defaulted is not the same as a filled
//         REQUIRE(defaulted != non_default);
//         REQUIRE_FALSE(defaulted == non_default);

//         defaulted.add_cap(a0, 0);
//         rhs.add_cap(a1, 0);

//         // Differ by cap value
//         REQUIRE(defaulted != rhs);
//         REQUIRE_FALSE(defaulted == rhs);

//         // Differ by offset of replaced atom
//         ghostfragment::Caps rhs2;
//         rhs2.add_cap(a0, 1);
//         REQUIRE(defaulted != rhs2);
//         REQUIRE_FALSE(defaulted == rhs2);
//     }
// }
