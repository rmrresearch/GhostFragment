/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <ghostfragment/equation/term.hpp>
#include <memory>
#include <ostream>

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
    /// unsigned integral type for counting and offsets
    using size_type = std::size_t;

    /// Type of the terms in the container
    using term_type = Term;

    /// Read-only reference to a term
    using const_term_reference = const term_type&;

    /// Ultimately a typedef of Term::coefficient_type
    using coefficient_type = term_type::coefficient_type;

    /// Type of the class implementing the Expression class
    using pimpl_type = detail_::ExpressionPIMPL;

    /// Type of a pointer to a pimpl_type object
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

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

    /** @brief The number of terms in this expression.
     *
     *  Expressions are essentially linear combinations of terms. This method
     *  returns the number of terms in *this.
     *
     *  @return The number of terms.
     *
     *  @throw None No throw guarantee.
     */
    size_type size() const noexcept;

    /** @brief Returns the @p i-th term in *this.
     *
     *  Expressions are essentially linear combinations of terms. This method
     *  is used to retrieve a term by offset.
     *
     *  @param[in] i The zero-based offset of the requested term. @p i must be
     *               in the range [0, size()).
     *
     *  @return A read-only reference to the requested term.
     *
     *  @throw std::out_of_range if @p i is not in the range [0, size()).
     *                           Strong throw guarantee.
     */
    const_term_reference at(size_type i) const;

    // -------------------------------------------------------------------------
    // -- Setters
    // -------------------------------------------------------------------------

    /** @brief Adds @p term to *this
     *
     *  This method behaves similar to `push_back` in that Expression behaves
     *  like a random access container and that @p term will be added on to
     *  the end of *this. This method does not check if @p term is already in
     *  *this.
     *
     *  @param[in] term The piece of the linear expansion to add.
     *
     *  @throw std::bad_alloc if there is a problem adding @p term to *this.
     *                        Strong throw guarantee.
     */
    void add_term(term_type term);

    // -------------------------------------------------------------------------
    // -- Utility methods
    // -------------------------------------------------------------------------

    /** @brief Determine if an Expression is empty.
     *
     *  An Expression is empty if it has no terms in it.
     *
     *  @return True if Expression is empty and false otherwise.
     *
     *  @throw None no throw guarantee.
     */
    bool empty() const noexcept;

    /** @brief Exchanges the state of @p other with the state of *this.
     *
     *  @param[in,out] other The Expression we are swapping state with. After
     *                       this method is called @p other will contain the
     *                       state which was previously in *this.
     */
    void swap(Expression& other) noexcept;

    /** @brief Determines if *this is value equal to @p rhs.
     *
     *  Two Expression instances are equal if they both are empty, or if they
     *  are both non-empty and contain the same terms, in the same order.
     *
     *  @param[in] rhs The Expression being compared to *this.
     *
     *  @return True if @p rhs is value equal to *this and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const Expression& rhs) const noexcept;

private:
    /// Code factorization for ensuring @p i is in range [0, size())
    void assert_bounds_(size_type i) const;

    /// The object implementing the Expression
    pimpl_pointer m_pimpl_;
};

inline bool operator!=(const Expression& lhs, const Expression& rhs) {
    return !(lhs == rhs);
}

inline std::ostream& operator<<(std::ostream& os, const Expression& exp) {
    if(exp.empty()) return os << "{ empty }";
    for(auto i = 0; i < exp.size(); ++i) os << exp.at(i) << std::endl;
    return os;
}

} // namespace ghostfragment::equation
