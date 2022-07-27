#pragma once
#include <ghostfragment/equation/expression.hpp>

namespace ghostfragment::equation::detail_ {

/// Implements the Expression class
struct ExpressionPIMPL {
    /// Type of the class this PIMPL implements
    using parent_type = Expression;

    /// Ultimately a typedef of Expression::term_type
    using term_type = parent_type::term_type;

    /// Random access container filled with term_type objects
    using term_container = std::vector<term_type>;

    /// Type of pointer parent_type stores its PIMPL as
    using pimpl_pointer = parent_type::pimpl_pointer;

    /// Makes a deep copy of this instance on the heap
    pimpl_pointer clone() const {
        return std::make_unique<ExpressionPIMPL>(*this);
    }

    /// Compares the Terms in *this to those in @p rhs
    bool operator==(const ExpressionPIMPL& rhs) const noexcept;

    /// Set of terms in the container
    term_container m_terms;
};

// -----------------------------------------------------------------------------
// -- Inline definitions
// -----------------------------------------------------------------------------

bool ExpressionPIMPL::operator==(const ExpressionPIMPL& rhs) const noexcept {
    return m_terms == rhs.m_terms;
}

} // namespace ghostfragment::equation::detail_