#pragma once
#include <ghostfragment/equation/term.hpp>
#include <memory>

namespace ghostfragment::equation {
namespace detail_ {
class InteractionPIMPL;
}

class Interaction {
public:
    using size_type            = std::size_t;
    using term_type            = Term;
    using const_term_reference = const term_type&;
    using nmer_type            = term_type::nmer_type;
    using ao_set_type          = term_type::ao_set_type;
    using coefficient_type     = term_type::coefficient_type;
    using pimpl_type           = detail_::InteractionPIMPL;
    using pimpl_pointer        = std::unique_ptr<pimpl_type>;

    Interaction() noexcept;
    explicit Interaction(pimpl_pointer pimpl) noexcept;
    Interaction(const Interaction& other);
    Interaction(Interaction&& other) noexcept;
    Interaction& operator=(const Interaction& rhs);
    Interaction& operator=(Interaction&& rhs) noexcept;
    ~Interaction() noexcept;

    size_type size() const noexcept;
    const_term_reference at(size_type i) const;

    /** @brief Convenience function for creating and inserting a term.
     *
     */
    void add_term(nmer_type nmer, ao_set_type aos, coefficient_type coef);
    void add_term(term_type term);

    bool empty() const noexcept;
    void swap(Interaction& other) noexcept;
    bool operator==(const Interaction& rhs) const noexcept;

private:
    void assert_bounds_(size_type i) const;
    pimpl_pointer m_pimpl_;
};

inline bool operator!=(const Interaction& lhs, const Interaction& rhs) {
    return !(lhs == rhs);
}

} // namespace ghostfragment::equation