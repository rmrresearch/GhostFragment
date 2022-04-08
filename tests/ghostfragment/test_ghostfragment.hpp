#pragma once
#include "testing/aos.hpp"
#include "testing/caps.hpp"
#include "testing/connectivity.hpp"
#include "testing/fragment.hpp"
#include "testing/sto3g.hpp"
#include "testing/water.hpp"
#include <catch2/catch.hpp>
#include <chemist/chemist.hpp>
#include <ghostfragment/detail_/fragmented_system_pimpl.hpp>
#include <ghostfragment/ghostfragment.hpp>
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

inline auto make_nmers(ghostfragment::type::fragmented_molecule water_n,
                       std::size_t n) {
    const auto N = water_n.size();
    ghostfragment::type::nmers nmers(water_n);

    if(n == 0)
        return nmers;
    else if(n == 1) {
        for(std::size_t i = 0; i < N; ++i) {
            auto frag = nmers.new_subset();
            frag.insert(i);
            nmers.insert(frag);
        }
        return nmers;
    } else if(n == 2) {
        for(std::size_t i = 0; i < N; ++i) {
            for(std::size_t j = i + 1; j < N; ++j) {
                auto frag = nmers.new_subset();
                frag.insert(i);
                frag.insert(j);
                nmers.insert(frag);
            }
        }
        return nmers;
    } else if(n == 3) {
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
        return nmers;
    } else if(n == 4) {
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
        return nmers;
    }

    throw std::runtime_error("Didn't code up higher than n == 4");
}

inline auto water_ao_pairs(std::size_t N) {
    const auto water_N = fragmented_water(N);
    const auto aos_N   = sto3g(water_N.object());
    using return_type  = ghostfragment::type::fragment_to_ao_basis;

    return_type pairs;
    ghostfragment::type::fragmented_aos aos(aos_N);
    std::size_t i = 0;
    for(std::size_t atom = 0; atom < 3 * N; ++atom) {
        auto atom_set = water_N.new_subset();
        atom_set.insert(atom);
        auto ao_set = aos.new_subset();
        ao_set.insert(atom);
        pairs.emplace(atom_set, ao_set);
    }
    return pairs;
}

inline auto fragmented_water_system_pimpl(std::size_t N) {
    using pimpl_type   = ghostfragment::detail_::FragmentedSystemPIMPL;
    auto pimpl         = std::make_unique<pimpl_type>();
    auto mol           = fragmented_water(N);
    auto caps          = caps_for_water(N);
    pimpl->m_frags     = mol;
    pimpl->m_frag2caps = capped_water(N);
    pimpl->m_atom2aos  = atom_to_ao(mol.object());
    pimpl->m_cap2aos   = atom_to_ao(caps.object().nuclei());
    pimpl->m_atom2ne   = std::vector<unsigned int>{};
    pimpl->m_cap2ne    = std::vector<unsigned int>{};

    for(std::size_t water_i = 0; water_i < N; ++water_i) {
        pimpl->m_atom2ne.push_back(8);
        pimpl->m_atom2ne.push_back(1);
        pimpl->m_atom2ne.push_back(1);
    }
    return pimpl;
}

inline auto fragmented_water_system(std::size_t N) {
    return ghostfragment::FragmentedSystem(fragmented_water_system_pimpl(N));
}

} // namespace testing
