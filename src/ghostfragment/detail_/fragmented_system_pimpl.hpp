#pragma once
#include <ghostfragment/fragmented_system.hpp>
#include <ghostfragment/type/type.hpp>

namespace ghostfragment::detail_ {

/** @brief Stores the state of FragmentedSystem class
 *
 *  Right now we just strore the state as a series of maps. It's assumed that
 *  users will create a PIMPL and then create a FragmentedSystem class by
 *  wrapping that PIPML. This works for the moment, but down the road we may
 *  want to allow users to add frags/caps etc. dynamically which is difficult
 *  with this data layout. If that happens the PIMPL should be made into an
 *  abstract base class and additional implementations added.
 */
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

    /// Retrieves the AO basis set for the specified fragment
    ao_set_type ao_basis_set(const_fragment_reference frag) const {
        ao_set_type rv = m_atom2aos.at(*(frag.begin()));
        for(auto atom_i : frag) rv += m_atom2aos.at(atom_i);
        return rv;
    }

    /// Determines the number of electrons for the fragment
    size_type n_electrons(const_fragment_reference frag) const {
        size_type rv{0};
        for(auto atom_i : frag) rv += m_atom2ne.at(atom_i);
        return rv;
    }

    /// True if each attribute of this compares equal to the one in @p rhs
    bool operator==(const FragmentedSystemPIMPL& rhs) const noexcept {
        return std::tie(m_frags, m_frag2caps, m_atom2aos, m_cap2aos, m_atom2ne,
                        m_cap2ne) == std::tie(rhs.m_frags, rhs.m_frag2caps,
                                              rhs.m_atom2aos, rhs.m_cap2aos,
                                              rhs.m_atom2ne, rhs.m_cap2ne);
    }

    void hash(type::Hasher& h) const {
        h(m_frags, m_frag2caps, m_atom2aos, m_cap2aos, m_atom2ne, m_cap2ne);
    }

    /// FamilyOfSets<Molecule> representing the fragments
    fragment_set_type m_frags;

    /// map from a fragment to the caps for that fragment
    cap_set_type m_frag2caps;

    /// map from an atom to its atomic basis set
    idx2ao_map_type m_atom2aos;

    /// map from a cap to its atomic basis set
    idx2ao_map_type m_cap2aos;

    /// map from an atom to its number of electrons
    idx2ne_map_type m_atom2ne;

    /// map from a cap to its number of electrons
    idx2ne_map_type m_cap2ne;
};

} // namespace ghostfragment::detail_
