#pragma once
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

// Assigns AOs to nuclei for the
inline auto fragmented_water_to_ao(const simde::type::molecule& mol) {
    using pimpl_type  = ghostfragment::detail_::FragmentedSystemPIMPL;
    using return_type = pimpl_type::idx2ao_map_type;
    return_type atom2aos;
    auto aos = sto3g(mol);
    ghostfragment::type::fragmented_aos ao_sets(aos);
    for(std::size_t atom_i = 0; atom_i < mol.size(); ++atom_i) {
        auto ao_set = ao_sets.new_subset();
        ao_set.insert(atom_i);
        atom2aos.emplace_back(ao_set);
    }
    return atom2aos;
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

inline auto capped_water(std::size_t n_waters) {
    auto water_n      = fragmented_water(n_waters);
    using capped_type = ghostfragment::pt::CappedFragmentsTraits::result_type;
    capped_type capped;
    ghostfragment::Caps caps;
    ghostfragment::type::fragmented_caps no_caps(caps);
    auto empty_set = no_caps.new_subset();
    for(const auto& frag_i : water_n) capped.emplace(frag_i, empty_set);
    return capped;
}

// Capped waters when fragments are generated with fragmented_water_needing_caps
inline auto capped_water_needing_caps(std::size_t n_waters) {
    using capped_type = ghostfragment::pt::CappedFragmentsTraits::result_type;
    auto frags        = fragmented_water_needing_caps(n_waters);
    const auto N      = frags.size();

    ghostfragment::Caps all_the_caps;
    const auto& mol = frags.object();
    for(size_t i = 0; i < n_waters; ++i) {
        // Cap replacing the 2nd H
        simde::type::atom h("H", 1ul, mol[i * 3 + 2].coords());
        // Cap replacing the O
        simde::type::atom o("H", 1ul, mol[i * 3].coords());
        all_the_caps.add_cap(h, i * 3 + 2);
        all_the_caps.add_cap(o, i * 3);
    }

    ghostfragment::type::fragmented_caps caps(all_the_caps);
    capped_type capped;
    for(std::size_t i = 0; i < N; ++i) {
        auto caps4i = caps.new_subset();
        caps4i.insert(i);
        capped.emplace(frags[i], caps4i);
    }
    return capped;
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

inline auto fragmented_water_system(std::size_t N) {
    using pimpl_type   = ghostfragment::detail_::FragmentedSystemPIMPL;
    auto pimpl         = std::make_unique<pimpl_type>();
    auto mol           = fragmented_water(N);
    auto caps          = capped_water(N);
    auto cap_mol       = caps.begin()->second.object().nuclei();
    pimpl->m_frags     = mol;
    pimpl->m_frag2caps = caps;
    pimpl->m_atom2aos  = fragmented_water_to_ao(mol.object());
    pimpl->m_cap2aos   = fragmented_water_to_ao(cap_mol);
    pimpl->m_atom2ne   = std::vector<unsigned int>{};
    pimpl->m_cap2ne    = std::vector<unsigned int>{};

    for(std::size_t water_i = 0; water_i < N; ++water_i) {
        pimpl->m_atom2ne.push_back(8);
        pimpl->m_atom2ne.push_back(1);
        pimpl->m_atom2ne.push_back(1);
    }
    return ghostfragment::FragmentedSystem(std::move(pimpl));
}

} // namespace testing
