#pragma once
#include <ghostfragment/nmer_system.hpp>

namespace ghostfragment::equation {
namespace detail_ {
class TermPIMPL;
}

/** @brief Desribes a term in an expression
 *
 *  Terms map to individual calculations. Superficially a Term is just a
 *  ChemicalSystem and a coefficient for scaling the result.
 *
 */
class Term {
public:
    /// Type of the NMersystem *this is associated with
    using nmer_system = NMerSystem;

    /// Ultimately a typedef of NMerSystem::nmer_type
    using nmer_type = nmer_system::nmer_type;

    /// Ultimately a typedef of NMerSystem::const_nmer_reference
    using const_nmer_reference = nmer_system::const_nmer_reference;

    /// Ultimately a typedef of NMerSystem::ao_set_type
    using ao_set_type = nmer_system::ao_set_type;

    /// Read-only reference to an ao_set_type
    using const_ao_set_reference = const ao_set_type&;

    /// Floating-point type of this term's scale factor
    using coefficient_type = double;

    /// Type of the object implementing Term
    using pimpl_type = detail_::TermPIMPL;

    /// Type of a pointer to the PIMPL
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    // -- CTors, Assignment Operators, and DTor

    /** @brief Creates a null Term object.
     *
     *  The instance resulting from the default ctor is largely a place holder.
     *  At the moment the only way to give a default constructed Term state is
     *  to assign to it. The resulting Term is empty.
     *
     *  @throw None No throw guarantee
     */
    Term() noexcept;
    Term(nmer_type nmer, ao_set_type aos, coefficient_type coef);
    Term(pimpl_pointer pimpl) noexcept;
    Term(const Term& other);
    Term(Term&& other) noexcept;
    Term& operator=(const Term& rhs);
    Term& operator=(Term&& rhs) noexcept;

    /// Standard no-throw dtor
    ~Term() noexcept;

    // -- Getters

    /** @brief Returns the molecular system involved in *this.
     *
     *  The most primitive input for most electronic structure calculations is
     *  the molecular system. This method returns the molecular system for this
     *  term.
     *
     *  @return a read-only reference to this term's molecular system
     *
     *  @throw std::runtime_error if *this does not have a molecular system set.
     *                            Strong throw guarantee.
     *
     */
    const_nmer_reference nmer() const;

    /** @brief Returns the AO basis set for the term
     *
     *  In addition to a chemical system, the other input for most electronic
     *  structure calculations is an AO basis set. This method returns the
     *  AO basis set for this term.
     *
     *  @return A read-only reference to the AO basis set
     *
     *  @throw std::runtime_error if *this does not have an AO basis set.
     *                            Strong throw guarantee.
     */
    const_ao_set_reference ao_basis_set() const;

    /** @brief The scale factor for this term.
     *
     *  Terms are meant to be used as part of interactions. When a term shows
     *  up in an interaction it is weighted. This method returns the scale
     *  factor for this term.
     *
     *  @return The scale factor
     *
     *  @throw std::runtime_error if *this does not have a coefficent set.
     *                            Strong throw guarantee.
     */
    coefficient_type coefficient() const;

    // -- Utility methods

    /** @brief Determines if the Term's state has been set
     *
     *  A term is empty if no part of its state (molecular system,
     *  AO basis, or coefficient) has been set.
     *
     *  @return True if this Term is empty and false otherwise.
     *
     *  @throw None no throw guarantee.
     */
    bool empty() const noexcept;

    /** @brief Exchanges the state in *this with the state in @p other.
     *
     *  @param[in,out] other The instance whose state is being swapped with the
     *                       state in *this. After this call @p other will
     *                       contain the state which was previously in *this.
     *
     *  @throw None No throw guarantee.
     */
    void swap(Term& other) noexcept;

    /** @brief Compares *this to @p rhs for value equality.
     *
     *  Two Term instances are value equal if they are both empty, or if they
     *  both contain the same state. In comparing state the molecular system,
     *  AO basis set, and scaling coefficient are compared. N.B. all floating
     *  point comparisons are also value equality (i.e., floating point values
     *  are compared to machine epsilon).
     *
     *  @param[in] rhs The Term being compared to *this.
     *
     *  @throw None No throw guarantee
     */
    bool operator==(const Term& rhs) const noexcept;

private:
    /// Code factorization for asserting that *this has a PIMPL
    void assert_pimpl_() const;

    /// The object actually implementing this Term
    pimpl_pointer m_pimpl_;
};

/** @brief Determines if two terms are different.
 *
 *  @relates Term
 *
 *  This method simply negates Term::operator==. See Term::operator== for the
 *  definition of value equality.
 *
 *  @param[in] lhs The Term to the left of the operator.
 *  @param[in] rhs The Term to the right of the operator.
 *
 *  @return False if @p lhs is value equal to @p rhs and true otherwise.
 *
 *  @throw None No throw guarantee.
 */
inline bool operator!=(const Term& lhs, const Term& rhs) {
    return !(lhs == rhs);
}

} // namespace ghostfragment::equation