#pragma once
#include <ghostfragment/nmer_system.hpp>

namespace ghostfragment::equation {
namespace detail_ {
class TermPIMPL;
}

class Term {
public:
    /// Type of the NMersystem *this is associated with
    using nmer_system = NMerSystem;

    /// Ultimately a typedef of NMerSystem::nmer_type
    using nmer_type              = nmer_system::nmer_type;

    /// Ultimately a typedef of NMerSystem::const_nmer_reference
    using const_nmer_reference   = nmer_system::const_nmer_reference;
    
    /// Ultimately a typedef of NMerSystem::ao_set_type
    using ao_set_type            = nmer_system::ao_set_type;

    /// Read-only reference to an ao_set_type
    using const_ao_set_reference = const ao_set_type&;

    /// Floating-point type of this term's scale factor
    using coefficient_type = double;

    /// Type of the object implementing Term
    using pimpl_type    = detail_::TermPIMPL;

    /// Type of a pointer to the PIMPL
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    // -- CTors, Assignment Operators, and DTor

    Term() noexcept;
    Term(nmer_type nmer, ao_set_type aos, coefficient_type coef);
    Term(pimpl_pointer pimpl) noexcept;
    Term(const Term& other);
    Term(Term&& other) noexcept;
    Term& operator=(const Term& rhs);
    Term& operator=(Term&& rhs) noexcept;
    ~Term() noexcept;

    // -- Getters

    const_nmer_reference nmer() const;
    const_ao_set_reference ao_basis_set() const;
    coefficient_type coefficient() const;

    // -- Utility methods

    bool empty() const noexcept;
    void swap(Term& other) noexcept;
    bool operator==(const Term& rhs) const noexcept;

private:
    void assert_pimpl_() const;
    pimpl_pointer m_pimpl_;
};

inline bool operator!=(const Term& lhs, const Term& rhs) {
    return !(lhs == rhs);
}

} // namespace ghostfragment::equation