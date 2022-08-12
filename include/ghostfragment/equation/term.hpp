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
    /// Type of a Chemical System
    using chemical_system_type = simde::type::chemical_system;

    /// Ultimately typedef of ChemicalSystem::molecule_t
    using molecule_type = chemical_system_type::molecule_t;

    /// Type used to represent the molecular basis set
    using ao_basis_set_type = simde::type::ao_basis_set;

    /// Unsigned integral type used for indexing and offsets
    using size_type = std::size_t;

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
    Term(pimpl_pointer pimpl) noexcept;
    Term(const Term& other);
    Term(Term&& other) noexcept;
    Term& operator=(const Term& rhs);
    Term& operator=(Term&& rhs) noexcept;

    /// Standard no-throw dtor
    ~Term() noexcept;

    // -- Getters

    /** @brief Returns the set of nuclei in *this.
     *
     *  Each Term has a set of nuclei, the number of electrons, and the AO
     *  basis set for the term. This method is used to retrieve the set of
     *  nuclei.
     *
     *  @return The set of nuclei for this term.
     *
     *  @throw std::runtime_error if *this has no PIMPL. Strong throw guarantee.
     */
    molecule_type molecule() const;

    /** @brief Returns the number of electrons in the term
     *
     *  Each Term has a set of nuclei, the number of electrons, and the AO
     *  basis set for the term. This method is used to retrieve the number of
     *  electrons.
     *
     *  @throw None No throw guarantee.
     */
    size_type n_electrons() const noexcept;

    /** @brief Returns the chemical system stored in *this
     *
     *  Each Term has a set of nuclei, the number of electrons, and the AO
     *  basis set for the term. Together the nuclei and electrons constitute
     *  a ChemicalSystem. This method returns that ChemicalSystem.
     *
     *  @return The ChemicalSystem associated with *this.
     *
     *  @throw std::runtime_error if *this has no PIMPL. Strong throw guarantee.
     */
    chemical_system_type chemical_system() const;

    /** @brief Returns the AO basis set associated with *this.
     *
     *  Each Term has a set of nuclei, the number of electrons, and the AO
     *  basis set for the term. This method is used to retrieve the AO basis
     *  set.
     *
     *  @return The AO basis set contained in *this.
     *
     *  @throw std::runtime_error if *this has no PIMPL. Strong throw guarantee.
     */
    ao_basis_set_type ao_basis_set() const;

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

std::ostream& operator<<(std::ostream& os, const Term& t);

} // namespace ghostfragment::equation
