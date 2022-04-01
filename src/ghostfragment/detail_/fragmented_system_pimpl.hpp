#pragma once
#include <ghostfragment/fragmented_system.hpp>
#include <ghostfragment/type/type.hpp>

namespace ghostfragment::detail_ {

struct FragmentedSystemPIMPL {
    /// The type we are implementing
    using parent_type = FragmentedSystem;

    /// How we specify indices and offsets
    using size_type = typename parent_type::size_type;

    /// How we store the fragments
    using fragment_set_type = type::fragmented_molecule;

    /// How we store the caps
    using cap_set_type = type::fragment_to_caps;

    /// How we store the index to ao mapping (for both atom anc cap indices)
    using idx2ao_map_type = type::idx2aos;

    /// How we store the index to n electron mapping
    using idx2ne_map_type = std::vector<size_type>;

    /// How the parent specifies immmutable references to a fragment
    using const_fragment_reference =
      typename parent_type::const_fragment_reference;

    /// How the parent returns a set of AOs
    using ao_set_type = typename parent_type::ao_set_type;

    ao_set_type ao_basis_set(const_fragment_reference frag) const {
        ao_set_type rv = m_atom2aos.at(*(frag.begin()));
        for(auto atom_i : frag) rv += m_atom2aos.at(atom_i);
        return rv;
    }

    size_type n_electrons(const_fragment_reference frag) const {
        size_type rv{0};
        for(auto atom_i : frag) rv += m_atom2ne.at(atom_i);
        return rv;
    }

    bool operator==(const FragmentedSystemPIMPL& rhs) const noexcept {
        return std::tie(m_frags, m_frag2caps, m_atom2aos, m_cap2aos, m_atom2ne,
                        m_cap2ne) == std::tie(rhs.m_frags, rhs.m_frag2caps,
                                              rhs.m_atom2aos, rhs.m_cap2aos,
                                              rhs.m_atom2ne, rhs.m_cap2ne);
    }

    void hash(type::Hasher& h) const {
        h(m_frags, m_frag2caps, m_atom2aos, m_cap2aos, m_atom2ne, m_cap2ne);
    }

    fragment_set_type m_frags;

    cap_set_type m_frag2caps;

    idx2ao_map_type m_atom2aos;

    idx2ao_map_type m_cap2aos;

    idx2ne_map_type m_atom2ne;

    idx2ne_map_type m_cap2ne;
};

} // namespace ghostfragment::detail_
