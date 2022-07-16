#pragma once
#include <ghostfragment/equation/term.hpp>

namespace ghostfragment::equation::detail_ {

struct TermPIMPL {
    using parent_type      = Term;
    using nmer_type        = parent_type::nmer_type;
    using ao_set_type      = parent_type::ao_set_type;
    using coefficient_type = parent_type::coefficient_type;
    using pimpl_pointer    = parent_type::pimpl_pointer;

    TermPIMPL(nmer_type nmer, ao_set_type aos, coefficient_type coef);

    pimpl_pointer clone() const;

    nmer_type m_nmer;
    ao_set_type m_aos;
    coefficient_type m_coef;
};

inline TermPIMPL::TermPIMPL(nmer_type nmer, ao_set_type aos,
                            coefficient_type coef) :
  m_nmer(std::move(nmer)), m_aos(std::move(aos)), m_coef(std::move(coef)) {}

inline typename TermPIMPL::pimpl_pointer TermPIMPL::clone() const {
    return std::make_unique<TermPIMPL>(*this);
}

} // namespace ghostfragment::equation::detail_