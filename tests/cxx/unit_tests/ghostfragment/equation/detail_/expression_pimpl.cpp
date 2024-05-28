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

// #include "../../test_ghostfragment.hpp"
// #include <ghostfragment/equation/detail_/expression_pimpl.hpp>

// using namespace ghostfragment::equation::detail_;
// using ghostfragment::equation::make_term;

// TEST_CASE("ExpressionPIMPL") {
//     auto water3 = testing::water_nmer_system(3, 2);
//     auto nmer   = water3.nmer(0);
//     auto aos    = water3.ao_basis_set(nmer);

//     using term_type = ExpressionPIMPL::term_type;
//     auto t          = make_term(nmer, aos, 1, 1.23);

//     ExpressionPIMPL defaulted;
//     ExpressionPIMPL p;
//     p.m_terms.push_back(t);

//     SECTION("Clone") {
//         auto defaulted_copy = defaulted.clone();
//         REQUIRE(*defaulted_copy == ExpressionPIMPL());

//         auto p_copy = p.clone();
//         REQUIRE(*p_copy == p);
//     }

//     SECTION("operator==") {
//         REQUIRE(defaulted == ExpressionPIMPL());

//         ExpressionPIMPL p_copy;
//         p_copy.m_terms.push_back(t);
//         REQUIRE(p == p_copy);

//         // Different terms
//         auto t2 = make_term(nmer, aos, 1, 3.14);
//         ExpressionPIMPL p2;
//         p2.m_terms.push_back(t2);
//         REQUIRE_FALSE(p == p2);
//     }
// }
