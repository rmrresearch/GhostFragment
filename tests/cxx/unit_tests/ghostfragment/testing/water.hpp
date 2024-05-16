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
#include <chemist/chemical_system/molecule/molecule.hpp>
#include <chemist/fragmenting/fragmented_nuclei.hpp>

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

} // namespace testing
