#pragma once
#include <ghostfragment/equation/term.hpp>
#include <memory>

namespace ghostfragment::equation {
namespace detail_ {
class ExpressionPIMPL;
}

/** @brief A set of terms.
 *
 *  Expressions describe how to combine Term objects to compute a property of
 *  interest.
 */
class Expression {
public:
    using size_type = std::size_t;
    using term_type = Term;

    /// Read-only reference to a term
    using const_term_reference = const term_type&;
    using nmer_type            = term_type::nmer_type;
    using ao_set_type          = term_type::ao_set_type;
    using coefficient_type     = term_type::coefficient_type;
    using pimpl_type           = detail_::ExpressionPIMPL;
    using pimpl_pointer        = std::unique_ptr<pimpl_type>;

    // -------------------------------------------------------------------------
    // -- Ctors, Assignment Operators, Dtor
    // -------------------------------------------------------------------------

    Expression() noexcept;
    explicit Expression(pimpl_pointer pimpl) noexcept;
    Expression(const Expression& other);
    Expression(Expression&& other) noexcept;
    Expression& operator=(const Expression& rhs);
    Expression& operator=(Expression&& rhs) noexcept;
    ~Expression() noexcept;

    // -------------------------------------------------------------------------
    // -- Getters
    // -------------------------------------------------------------------------

    size_type size() const noexcept;
    const_term_reference at(size_type i) const;

    // -------------------------------------------------------------------------
    // -- Setters
    // -------------------------------------------------------------------------

    /** @brief Convenience function for creating and inserting a term.
     *
     */
    void add_term(nmer_type nmer, ao_set_type aos, coefficient_type coef);
    void add_term(term_type term);

    // -------------------------------------------------------------------------
    // -- Utility methods
    // -------------------------------------------------------------------------

    bool empty() const noexcept;
    void swap(Expression& other) noexcept;
    bool operator==(const Expression& rhs) const noexcept;

private:
    void assert_bounds_(size_type i) const;
    pimpl_pointer m_pimpl_;
};

inline bool operator!=(const Expression& lhs, const Expression& rhs) {
    return !(lhs == rhs);
}

} // namespace ghostfragment::equation