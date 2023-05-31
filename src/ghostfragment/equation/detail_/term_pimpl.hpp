// #pragma once
// #include <ghostfragment/equation/term.hpp>

// namespace ghostfragment::equation::detail_ {

// struct TermPIMPL {
//     /// Type of the class this PIMPL implements
//     using parent_type = Term;

//     /// Type of object fragmented data comes from
//     using nmer_system_type = NMerSystem;

//     /// Ultimately a typedef of NMerSystem::nmer_type
//     using nmer_type = nmer_system_type::nmer_type;

//     /// Ultimately a typedef of Term::molecule_type
//     using molecule_type = parent_type::molecule_type;

//     /// Ultimately a typedef of NMerSystem::ao_set_type
//     using ao_set_type = nmer_system_type::ao_set_type;

//     /// Ultimately a typedef of Term::ao_basis_set_type
//     using ao_basis_set_type = parent_type::ao_basis_set_type;

//     /// Ultimately a typedef of Term::size_type
//     using size_type = parent_type::size_type;

//     /// Ultimately a typedef of Term::coefficient_type
//     using coefficient_type = parent_type::coefficient_type;

//     /// Type of the pointer used to manage the lifetime of a TermPIMPl
//     using pimpl_pointer = parent_type::pimpl_pointer;

//     TermPIMPL(nmer_type nmer, ao_set_type aos, size_type n_electrons,
//               coefficient_type coef);

//     /** @brief Returns the set of nuclei contained in *this.
//      *
//      *  @return The set of nuclei *this holds.
//      */
//     molecule_type molecule() const;

//     /// Returns the AO basis set *this holds
//     ao_basis_set_type ao_basis_set() const;

//     /// Makes a deep copy of *this
//     pimpl_pointer clone() const;

//     /// Element-wise comparison
//     bool operator==(const TermPIMPL& rhs) const noexcept;

//     nmer_type m_nmer;
//     ao_set_type m_aos;
//     size_type m_n_electrons;
//     coefficient_type m_coef;
// };

// //
// -----------------------------------------------------------------------------
// // -- Inline implementations
// //
// -----------------------------------------------------------------------------

// inline TermPIMPL::TermPIMPL(nmer_type nmer, ao_set_type aos,
//                             size_type n_electrons, coefficient_type coef) :
//   m_nmer(std::move(nmer)),
//   m_aos(std::move(aos)),
//   m_n_electrons(n_electrons),
//   m_coef(std::move(coef)) {}

// inline typename TermPIMPL::molecule_type TermPIMPL::molecule() const {
//     molecule_type mol;
//     const auto& frags = m_nmer.object();
//     std::set<size_type> m_indices;
//     for(const auto& fragment_index : m_nmer) {
//         const auto& frag = frags.at(fragment_index);
//         m_indices.insert(frag.begin(), frag.end());
//     }

//     const auto& parent_mol = frags.object();
//     for(const auto atom_index : m_indices)
//         mol.push_back(parent_mol.at(atom_index));
//     return mol;
// }

// inline typename TermPIMPL::ao_basis_set_type TermPIMPL::ao_basis_set() const
// {
//     ao_basis_set_type aos;
//     const auto& parent_aos = m_aos.object();
//     for(const auto& ao_index : m_aos) { aos.add_center(parent_aos[ao_index]);
//     } return aos;
// }

// inline typename TermPIMPL::pimpl_pointer TermPIMPL::clone() const {
//     return std::make_unique<TermPIMPL>(*this);
// }

// inline bool TermPIMPL::operator==(const TermPIMPL& rhs) const noexcept {
//     return std::tie(m_nmer, m_aos, m_n_electrons, m_coef) ==
//            std::tie(rhs.m_nmer, rhs.m_aos, rhs.m_n_electrons, rhs.m_coef);
// }

// } // namespace ghostfragment::equation::detail_
