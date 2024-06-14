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
#include <chemist/chemical_system/molecule/atom.hpp>
#include <chemist/chemical_system/molecule/molecule.hpp>
#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <chemist/topology/connectivity_table.hpp>
#include <cstdlib>
#include <string>

namespace testing {

chemist::Molecule hydrocarbon(int num_carbon);

inline auto hydrocarbon_connectivity(std::size_t N) {
    // Probably a better way, but this works
    const auto n_atoms = hydrocarbon(N).size();

    chemist::topology::ConnectivityTable conns(n_atoms);
    if(N == 0) return conns;

    // First N-1 atoms are carbons
    // carbon 0 is bonded to atom N
    // carbon i is bonded to carbon i + 1 (assuming i + 1 != N)
    // carbon i is bonded to hydrogens N + 2*i + 1 and N + 2*i + 2
    // carbon N - 1 is bonded to atom n_atoms - 1
    std::size_t h_counter = N;
    conns.add_bond(0, h_counter);
    for(std::size_t i = 0; i < N; ++i) {
        if(i + 1 < N) conns.add_bond(i, i + 1);
        conns.add_bond(i, ++h_counter);
        conns.add_bond(i, ++h_counter);
    }
    conns.add_bond(N - 1, ++h_counter);
    return conns;
}

/// Fragments a hydrocarbon system (fragments are M carbons
/// with M-1 carbon overlap with adjacent fragments,
/// hydrocarbon is N carbons long)
inline auto hydrocarbon_fragmented_nuclei(std::size_t N, std::size_t M) {
    auto hydrocarbon_n = hydrocarbon(N);
    using return_type = chemist::fragmenting::FragmentedNuclei<chemist::Nuclei>;
    return_type frags(hydrocarbon_n.nuclei());

    // Define fragment to add to fragmented nuclei
    std::vector<std::size_t> frag{};
    for(std::size_t i = 0; i < N - (M - 1); ++i) {
        frag = {};
        for(std::size_t j = i; j < i + M; ++j) {
            frag.push_back(j);
            if(j == 0) { frag.push_back(N); }
            frag.push_back(2 * j + 1 + N);
            frag.push_back(2 * j + 2 + N);
            if(j == N - 1) { frag.push_back(2 * j + 3 + N); }
        }
        frags.insert(frag.begin(), frag.end());
    }
    return frags;
}

} // namespace testing
