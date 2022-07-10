#include "detail_/interaction_pimpl.hpp"

namespace ghostfragment {

// -- Ctors, Assignment Operators, Dtor

Interaction::Interaction() noexcept = default;

Interaction::Interaction(pimpl_pointer pimpl) noexcept :
  m_pimpl_(std::move(pimpl)) {}

Interaction::Interaction(const Interaction& other) :
  m_pimpl_(!other.empty() ? other.m_pimpl_->clone() : nullptr) {}

Interaction::Interaction(Interaction&& other) noexcept = default;

Interaction& Interaction::operator=(const Interaction& rhs) {
    if(this != &rhs) { Interaction(rhs).swap(*this); }
    return *this;
}

Interaction& Interaction::operator=(Interaction&& rhs) noexcept = default;

Interaction::~Interaction() noexcept = default;

// -- Getters

Interaction::size_type Interaction::size() const noexcept {
    return !empty() ? m_pimpl_->m_terms.size() : 0;
}

Interaction::const_term_reference Interaction::at(size_type i) const {
    assert_bounds_(i);
    return m_pimpl_->m_terms[i];
}

// -- Setters

void Interaction::add_term(nmer_type nmer, ao_set_type aos,
                           coefficient_type coef) {
    add_term(term_type(std::move(nmer), std::move(aos), std::move(coef)));
}

void Interaction::add_term(term_type term) {
    if(!m_pimpl_) std::make_unique<pimpl_type>().swap(m_pimpl_);
    m_pimpl_->m_terms.emplace_back(std::move(term));
}

// -- Utility

bool Interaction::empty() const noexcept {
    return !static_cast<bool>(m_pimpl_);
}

void Interaction::swap(Interaction& other) noexcept {
    m_pimpl_.swap(other.m_pimpl_);
}

bool Interaction::operator==(const Interaction& rhs) const noexcept {
    // Check if one is empty and other isn't
    if(empty() != rhs.empty()) return false;

    // Both are either empty or not empty, return if empty
    if(empty()) return true;

    return std::tie(m_pimpl_->m_terms) == std::tie(rhs.m_pimpl_->m_terms);
}

// -- Private Methods

void Interaction::assert_bounds_(size_type i) const {
    if(i < size()) return;

    throw std::out_of_range("Offset " + std::to_string(i) +
                            " is not in the range [0, " +
                            std::to_string(size()) + ").");
}

} // namespace ghostfragment