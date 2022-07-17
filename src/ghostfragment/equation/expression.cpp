#include "detail_/expression_pimpl.hpp"

namespace ghostfragment::equation {

Expression::Expression() noexcept : Expression(nullptr) {}

Expression::Expression(pimpl_pointer pimpl) noexcept :
  m_pimpl_(std::move(pimpl)) {}

Expression::Expression(const Expression& other) :
  Expression(other.has_pimpl_() ? other.m_pimpl_->clone() : nullptr) {}

Expression::Expression(Expression&& other) noexcept = default;

Expression& Expression::operator=(const Expression& rhs) {
    if(this != &rhs) Expression(rhs).swap(*this);
    return *this;
}

Expression& Expression::operator=(Expression&& rhs) noexcept = default;

Expression::~Expression() noexcept = default;

Expression::size_type Expression::size() const noexcept {
    return has_pimpl_() ? m_pimpl_->m_interactions.size() : 0;
}

void Expression::emplace_back(interaction_type interaction) {
    if(!has_pimpl_()) m_pimpl_ = std::make_unique<pimpl_type>();
    m_pimpl_->m_interactions.emplace_back(std::move(interaction));
}

Expression::const_interaction_reference Expression::at(size_type i) const {
    bounds_check_(i);
    return m_pimpl_->m_interactions[i];
}

bool Expression::empty() const noexcept {
    return has_pimpl_() ? m_pimpl_->m_interactions.empty() : true;
}

void Expression::swap(Expression& other) noexcept {
    m_pimpl_.swap(other.m_pimpl_);
}

bool Expression::operator==(const Expression& rhs) const noexcept {
    // If one instance has PIMPL and the other doesn't return false
    if(has_pimpl_() != has_pimpl_()) return false;

    // Either they both have, or both do not have a PIMPL, early return if
    // latter
    if(!has_pimpl_()) return true;

    return m_pimpl_->m_interactions == rhs.m_pimpl_->m_interactions;
}

bool Expression::operator!=(const Expression& rhs) const noexcept {
    return !(*this == rhs);
}

bool Expression::has_pimpl_() const noexcept {
    return static_cast<bool>(m_pimpl_);
}

void Expression::bounds_check_(size_type i) const {
    if(i < size()) return;
    throw std::out_of_range("Offset " + std::to_string(i) +
                            " is not in the range [0, " +
                            std::to_string(size()) + ").");
}

} // namespace ghostfragment::equation