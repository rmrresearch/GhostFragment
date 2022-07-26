#pragma once
#include <ghostfragment/equation/term.hpp>

namespace ghostfragment::equation::detail_ {

struct TermPIMPL {
    /// Type of the class this PIMPL implements
    using parent_type      = Term;

    /// Ultimately a typedef of NMerSystem::nmer_type
    using nmer_type        = parent_type::nmer_type;

    /// Ultimately a typedef of NMerSystem::ao_set_type
    using ao_set_type      = parent_type::ao_set_type;

    /// Ultimately a typedef of Term::coefficient_type
    using coefficient_type = parent_type::coefficient_type;

    /// Type of the pointer used to manage the lifetime of a TermPIMPl
    using pimpl_pointer    = parent_type::pimpl_pointer;

    TermPIMPL(nmer_type nmer, ao_set_type aos, coefficient_type coef);

    pimpl_pointer clone() const;

    bool operator==(const TermPIMPL& rhs) const noexcept;

    nmer_type m_nmer;
    ao_set_type m_aos;
    coefficient_type m_coef;
};

// -----------------------------------------------------------------------------
// -- Inline implementations
// -----------------------------------------------------------------------------

inline TermPIMPL::TermPIMPL(nmer_type nmer, ao_set_type aos,
                            coefficient_type coef) :
  m_nmer(std::move(nmer)), m_aos(std::move(aos)), m_coef(std::move(coef)) {}

inline typename TermPIMPL::pimpl_pointer TermPIMPL::clone() const {
    return std::make_unique<TermPIMPL>(*this);
}

inline bool TermPIMPL::operator==(const TermPIMPL& rhs) const noexcept{
    std::tie(m_nmer, m_aos, m_coef) == std::tie(rhs.m_nmer, rhs.m_aos, rhs.m_coef);
}

} // namespace ghostfragment::equation::detail_