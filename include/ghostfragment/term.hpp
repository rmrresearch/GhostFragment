#pragma once
#include <ghostfragment/fragment_based_method.hpp>

namespace ghostfragment {
namespace detail_ {
class TermPIMPL;
}

class Term {
private:
    using fbm_type = FragmentBasedMethod;

public:
    using nmer_system = fbm_type::nmer_system;

    using nmer_type              = nmer_system::nmer_type;
    using const_nmer_reference   = nmer_system::const_nmer_reference;
    using ao_set_type            = nmer_system::ao_set_type;
    using const_ao_set_reference = const ao_set_type&;

    using coefficient_type = double;

    using pimpl_type    = detail_::TermPIMPL;
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

    const_nmer_reference nmer() const;
    const_ao_set_reference ao_basis_set() const;
    coefficient_type coefficient() const;

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

} // namespace ghostfragment