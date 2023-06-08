#pragma once
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/fragmented_nuclei.hpp>

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
    auto water_n = water(N);
    chemist::FragmentedNuclei frags(water_n.nuclei());
    for(std::size_t i = 0; i < N; ++i)
        frags.add_fragment({3 * i, 3 * i + 1, 3 * i + 2});
    return frags;
}

} // namespace testing
