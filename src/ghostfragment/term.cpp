#include "detail_/term_pimpl.hpp"

namespace ghostfragment {

Term::Term() noexcept = default;

Term::Term(pimpl_pointer pimpl) noexcept : m_pimpl_(std::move(pimpl)) {}

Term::Term(nmer_type nmer, ao_set_type aos, coefficient_type coef) :
  Term(std::make_unique<pimpl_type>(std::move(nmer), std::move(aos), coef)) {}

Term::Term(const Term& other) :
  m_pimpl_(other.m_pimpl_ ? other.m_pimpl_->clone() : nullptr) {}

Term::Term(Term&& other) noexcept = default;

Term& Term::operator=(const Term& rhs) {
    if(this != &rhs) { Term(rhs).swap(*this); }
    return *this;
}

Term& Term::operator=(Term&& rhs) noexcept = default;

Term::~Term() noexcept = default;

bool Term::empty() const noexcept { return !static_cast<bool>(m_pimpl_); }

void Term::swap(Term& other) noexcept { m_pimpl_.swap(other.m_pimpl_); }

Term::const_nmer_reference Term::nmer() const {
    assert_pimpl_();
    return m_pimpl_->m_nmer;
}

Term::const_ao_set_reference Term::ao_basis_set() const {
    assert_pimpl_();
    return m_pimpl_->m_aos;
}

Term::coefficient_type Term::coefficient() const {
    assert_pimpl_();
    return m_pimpl_->m_coef;
}

void Term::assert_pimpl_() const {
    if(!empty()) return;
    throw std::runtime_error("Term is empty. Did you default construct it or "
                             "move from it?");
}

} // namespace ghostfragment