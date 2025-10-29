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

#pragma once
#include <chemist/chemist.hpp>

namespace testing {

/// Creates a system with N waters (waters are in a line along the z-axis)
inline auto water(std::size_t N = 1) {
    using molecule_type = chemist::Molecule;
    using atom_type     = typename molecule_type::atom_type;
    using cart_type     = std::array<double, 3>;
    const double dz     = 3.0;
    molecule_type rv;
    for(std::size_t i = 0; i < N; ++i) {
        const double z = i * dz;
        cart_type rO{0.00000000000000, -0.07579039945857, z};
        cart_type rH0{0.86681456860648, 0.60144316994806, z};
        cart_type rH1{-0.86681456860648, 0.60144316994806, z};
        rv.push_back(atom_type("O", 8ul, 16.0, rO[0], rO[1], rO[2]));
        rv.push_back(atom_type("H", 1ul, 1.0, rH0[0], rH0[1], rH0[2]));
        rv.push_back(atom_type("H", 1ul, 1.0, rH1[0], rH1[1], rH1[2]));
    }
    return rv;
}

/// Fragments a water system created with `water` (fragments are
/// individual water molecules)
inline auto water_fragmented_nuclei(std::size_t N = 1) {
    auto water_n      = water(N);
    using nuclei_type = chemist::Nuclei;
    using return_type = chemist::fragmenting::FragmentedNuclei<nuclei_type>;
    return_type frags(water_n.nuclei());
    for(std::size_t i = 0; i < N; ++i)
        frags.insert({3 * i, 3 * i + 1, 3 * i + 2});
    return frags;
}

// /// Creates a connectivity table for a water cluster. It's assumed that each
// /// water is order O, H, H
inline auto water_connectivity(std::size_t N) {
    chemist::topology::ConnectivityTable connects(3 * N);
    for(std::size_t water_i = 0; water_i < N; ++water_i) {
        std::size_t start = 3 * water_i;     // Index of oxygen for water_i
        connects.add_bond(start, start + 1); // start + 1 is 1st hydrogen
        connects.add_bond(start, start + 2); // start + 2 is 2nd hydrogen
    }
    return connects;
}

inline auto water_sto3g(const chemist::Molecule& mol){
    using ao_basis_t     = chemist::basis_set::AOBasisSetD;
    using atomic_basis_t = typename ao_basis_t::value_type;
    using shell_t        = typename atomic_basis_t::value_type;
    using cg_t           = typename shell_t::cg_type;
    using prim_t         = typename cg_t::value_type;
    using point_t        = typename prim_t::center_type;
    using doubles_t      = std::vector<double>;

    // Oxygen 1s, 2s, and 2p exponents and coefficients, respectively
    doubles_t cs0{0.15432897, 0.53532814, 0.44463454};
    doubles_t es0{130.7093200, 23.8088610, 6.4436083};
    doubles_t cs1{-0.09996723, 0.39951283, 0.70011547};
    doubles_t es1{5.0331513, 1.1695961, 0.3803890};
    doubles_t cs2{0.15591627, 0.60768372, 0.39195739};
    doubles_t es2{5.0331513, 1.1695961, 0.3803890};

    // Hydrogen 1s coefficients and exponents
    doubles_t cs3{0.1543289673, 0.5353281423, 0.4446345422};
    doubles_t es3{3.425250914, 0.6239137298, 0.1688554040};
    
    ao_basis_t bs;
    for(std::size_t i = 0; i < mol.size(); ++i) {
        const auto Z = mol[i].Z();
        const auto r = mol[i].as_point();
        atomic_basis_t center("sto-3g", Z, r);
        if(Z == 8){
            cg_t cg0(cs0.begin(), cs0.end(), es0.begin(), es0.end(), r);
            cg_t cg1(cs1.begin(), cs1.end(), es1.begin(), es1.end(), r);
            cg_t cg2(cs2.begin(), cs2.end(), es2.begin(), es2.end(), r);
            center.add_shell(chemist::ShellType::pure, 0, cg0);
            center.add_shell(chemist::ShellType::pure, 0, cg1);
            center.add_shell(chemist::ShellType::pure, 1, cg2);
        } else{
            cg_t cg3(cs3.begin(), cs3.end(), es3.begin(), es3.end(), r);
            center.add_shell(chemist::ShellType::pure, 0, cg3);
        }
        bs.add_center(center);
    }
    return bs;
}

} // namespace testing
