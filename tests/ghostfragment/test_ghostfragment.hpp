#pragma once
#include "ghostfragment/ghostfragment.hpp"
#include <catch2/catch.hpp>
#include <chemist/chemist.hpp>
#include <simde/simde.hpp>
namespace testing {

// Common set-up all tests have
inline auto initialize() {
    pluginplay::ModuleManager mm;
    ghostfragment::load_modules(mm);
    return mm;
}

// Makes a H, He, and O atom centered at the origin
inline auto some_atoms() {
    using molecule = simde::type::molecule;
    using atom     = typename molecule::value_type;
    atom H{"H", 1ul};
    atom He{"He", 2ul};
    atom O{"O", 8ul};
    return std::make_tuple(H, He, O);
}

/// Creates a system with N waters (waters are in a line along the z-axis)
inline auto water(std::size_t N = 1) {
    using molecule_type = simde::type::molecule;
    using atom_type     = typename molecule_type::value_type;
    using cart_type     = typename atom_type::coord_type;
    const double dz     = 3.0;
    molecule_type rv;
    for(std::size_t i = 0; i < N; ++i) {
        const double z = i * dz;
        cart_type rO{0.00000000000000, -0.07579039945857, z};
        cart_type rH0{0.86681456860648, 0.60144316994806, z};
        cart_type rH1{-0.86681456860648, 0.60144316994806, z};
        rv.push_back(atom_type{"O", 8ul, rO});
        rv.push_back(atom_type{"H", 1ul, rH0});
        rv.push_back(atom_type{"H", 1ul, rH1});
    }
    return rv;
}

/// Creates a connectivity table for the system resulting from `water(N)`
inline auto water_connectivity(std::size_t N) {
    simde::type::connectivity_table connects(3 * N);
    for(std::size_t water_i = 0; water_i < N; ++water_i) {
        std::size_t start = 3 * water_i;     // Index of oxygen for water_i
        connects.add_bond(start, start + 1); // start + 1 is 1st hydrogen
        connects.add_bond(start, start + 2); // start + 2 is 2nd hydrogen
    }
    return connects;
}

/// Creates an STO-3G basis set for the provided molecule (assumed to be waters)
inline auto sto3g(const simde::type::molecule& mol) {
    using vector_t = std::vector<double>;
    using namespace chemist;

    // Taken from hard-coded basis sets in NWX
    // O
    vector_t c0_o{0.15432897, 0.53532814, 0.44463454};
    vector_t a0_o{130.7093200, 23.8088610, 6.4436083};
    vector_t c1{-0.09996723, 0.39951283, 0.70011547};
    vector_t c2{0.15591627, 0.60768372, 0.39195739};
    vector_t a1{5.0331513, 1.1695961, 0.3803890};

    // H
    vector_t c0{0.1543289673, 0.5353281423, 0.4446345422};
    vector_t a0{3.425250914, 0.6239137298, 0.1688554040};

    AOBasisSet<double> bs;
    for(const auto& atom_i : mol) {
        AtomicBasisSet<double> c;
        for(std::size_t i = 0; i < 3; ++i) c.coord(i) = atom_i.coords()[i];
        if(atom_i.Z() == 1) {
            c.add_shell(ShellType::pure, 0, c0, a0);
        } else if(atom_i.Z() == 8) {
            c.add_shell(ShellType::pure, 0, c0_o, a0_o);
            c.add_shell(ShellType::pure, 0, c1, a1);
            c.add_shell(ShellType::pure, 1, c2, a1);
        } else {
            throw std::out_of_range("No data for atomic number");
        }
        bs.add_center(c);
    }
    return simde::type::ao_space{bs};
}

// Makes fragments where each water is in a single fragment
inline auto fragmented_water(std::size_t N) {
    auto molecule    = water(N);
    using frag_type  = ghostfragment::type::fragmented_molecule;
    using value_type = frag_type::value_type;
    using size_type  = value_type::size_type;

    frag_type frags(molecule);
    for(size_type i = 0; i < N; ++i) {
        auto water = frags.new_subset();
        for(size_type j = 0; j < 3; ++j) water.insert(i * 3 + j);
        frags.insert(water);
    }
    return frags;
}

inline auto water_nmers(std::size_t N, std::size_t n) {
    auto water_n = fragmented_water(N);
    ghostfragment::type::nmers nmers(water_n);

    if(n == 0) return nmers;

    for(std::size_t i = 0; i < N; ++i) {
        auto frag = nmers.new_subset();
        frag.insert(i);
        nmers.insert(frag);
    }

    if(n == 1) return nmers;

    for(std::size_t i = 0; i < N; ++i) {
        for(std::size_t j = i + 1; j < N; ++j) {
            auto frag = nmers.new_subset();
            frag.insert(i);
            frag.insert(j);
            nmers.insert(frag);
        }
    }

    if(n == 2) return nmers;

    for(std::size_t i = 0; i < N; ++i) {
        for(std::size_t j = i + 1; j < N; ++j) {
            for(std::size_t k = j + 1; k < N; ++k) {
                auto frag = nmers.new_subset();
                frag.insert(i);
                frag.insert(j);
                frag.insert(k);
                nmers.insert(frag);
            }
        }
    }

    if(n == 3) return nmers;

    for(std::size_t i = 0; i < N; ++i) {
        for(std::size_t j = i + 1; j < N; ++j) {
            for(std::size_t k = j + 1; k < N; ++k) {
                for(std::size_t l = k + 1; l < N; ++l) {
                    auto frag = nmers.new_subset();
                    frag.insert(i);
                    frag.insert(j);
                    frag.insert(k);
                    frag.insert(l);
                    nmers.insert(frag);
                }
            }
        }
    }

    if(n == 4) return nmers;

    throw std::runtime_error("Didn't code up higher than n == 4");
}

// Fragments each water as (OH)(H)
inline auto fragmented_water_needing_caps(std::size_t N) {
    auto molecule    = water(N);
    using frag_type  = ghostfragment::type::fragmented_molecule;
    using value_type = frag_type::value_type;
    using size_type  = value_type::size_type;

    frag_type frags(molecule);
    for(size_type i = 0; i < N; ++i) {
        auto oh = frags.new_subset();
        for(size_type j = 0; j < 2; ++j) oh.insert(i * 3 + j);
        frags.insert(oh);
        auto h = frags.new_subset();
        h.insert(i * 3 + 2);
        frags.insert(h);
    }
    return frags;
}

inline auto water_ao_pairs(std::size_t N) {
    const auto water_N = fragmented_water(N);
    const auto aos_N   = sto3g(water_N.object()).basis_set();
    using return_type  = ghostfragment::type::fragment_to_ao_basis;

    return_type pairs;
    ghostfragment::type::fragmented_aos aos(aos_N);
    std::size_t i = 0;
    for(const auto& water : water_N) {
        auto new_subset = aos.new_subset();
        for(std::size_t j = 0; j < 3; ++j) { new_subset.insert(3 * i + j); }
        pairs.emplace(water, new_subset);
        ++i;
    }
    return pairs;
}

} // namespace testing
