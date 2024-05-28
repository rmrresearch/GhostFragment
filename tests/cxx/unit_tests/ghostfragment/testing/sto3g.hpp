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

// #pragma once
// #include <ghostfragment/type/type.hpp>

// namespace testing {

// /// Creates an STO-3G basis set for the provided molecule
// /// (only knows about Z== 1 or 8)
// inline auto sto3g(const ghostfragment::type::nuclei_set& mol) {
//     using ao_basis_set     = ghostfragment::type::ao_basis_set;
//     using atomic_basis_set = typename ao_basis_set::value_type;
//     using shell_type       = typename atomic_basis_set::value_type;
//     using vector_t         = std::vector<double>;

//     // Taken from hard-coded basis sets in NWX
//     // O
//     vector_t c0_o{0.15432897, 0.53532814, 0.44463454};
//     vector_t a0_o{130.7093200, 23.8088610, 6.4436083};
//     vector_t c1{-0.09996723, 0.39951283, 0.70011547};
//     vector_t c2{0.15591627, 0.60768372, 0.39195739};
//     vector_t a1{5.0331513, 1.1695961, 0.3803890};

//     // H
//     vector_t c0{0.1543289673, 0.5353281423, 0.4446345422};
//     vector_t a0{3.425250914, 0.6239137298, 0.1688554040};

//     auto pure = shell_type::pure_type::pure;

//     ao_basis_set bs;
//     for(const auto& atom_i : mol) {
//         atomic_basis_set c;
//         for(std::size_t i = 0; i < 3; ++i) c.coord(i) = atom_i.coord(i);
//         if(atom_i.Z() == 1) {
//             c.add_shell(pure, 0, c0, a0);
//         } else if(atom_i.Z() == 8) {
//             c.add_shell(pure, 0, c0_o, a0_o);
//             c.add_shell(pure, 0, c1, a1);
//             c.add_shell(pure, 1, c2, a1);
//         } else {
//             throw std::out_of_range("No data for atomic number");
//         }
//         bs.add_center(c);
//     }
//     return bs;
// }

// } // namespace testing
