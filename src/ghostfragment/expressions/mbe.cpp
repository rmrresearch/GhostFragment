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

// #include "expressions.hpp"
// #include <ghostfragment/property_types/expression.hpp>
// #include <utilities/iter_tools/combinations.hpp>

// using my_pt       = ghostfragment::pt::Expression;
// using traits_type = ghostfragment::pt::ExpressionTraits;
// using nmers_type  = traits_type::input_type;
// using nmer_type   = nmers_type::nmer_type;
// using size_type   = nmers_type::size_type;
// using vector_type = std::vector<size_type>;
// using map_type    = std::map<nmer_type, int>;

// namespace ghostfragment::expressions {

// namespace {
// constexpr auto module_desc = R"""(
// ###################
// Many-Body Expansion
// ###################
// )""";
// }

// MODULE_CTOR(MBE) {
//     satisfies_property_type<my_pt>();

//     description(module_desc);
// }

// void compute_intersections(const nmer_type& nmer, std::size_t i,
//                            const nmers_type& nmers, map_type& rv,
//                            int coef = 1) {
//     // Input coef is for n things, interior of loop is for n + 1 things so we
//     // need to flip the sign
//     coef *= -1;
//     for(std::size_t j = i; j < nmers.size(); ++j) {
//         auto intersect = nmer ^ nmers.nmer(j);
//         if(intersect.size() == 0) continue;
//         compute_intersections(intersect, j + 1, nmers, rv, coef);
//         rv.count(intersect) ? rv[intersect] += coef : rv[intersect] = coef;
//     }
// }

// MODULE_RUN(MBE) {
//     const auto& [nmers] = my_pt::unwrap_inputs(inputs);

//     map_type coefs;
//     for(size_type i = 0; i < nmers.size(); ++i) {
//         const auto& nmer_i = nmers.nmer(i);
//         coefs.count(nmer_i) ? ++coefs[nmer_i] : coefs[nmer_i] = 1;
//         compute_intersections(nmer_i, i + 1, nmers, coefs);
//     }

//     traits_type::result_type equation;
//     const auto& frags = nmers.fragments();
//     for(const auto& [kmer, v] : coefs) {
//         auto k_aos       = nmers.ao_basis_set(kmer.begin(), kmer.end());
//         auto k_electrons = nmers.n_electrons(kmer.begin(), kmer.end());
//         auto t = equation::make_term(kmer, k_aos, k_electrons, double(v));
//         equation.add_term(std::move(t));
//     }

//     auto rv = results();
//     return my_pt::wrap_results(rv, equation);
// }

// } // namespace ghostfragment::expressions
