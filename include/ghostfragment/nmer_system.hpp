#pragma once
#include "ghostfragment/fragmented_system.hpp"
#include "ghostfragment/types.hpp"
namespace ghostfragment {
namespace detail_ {
class NMerSystemPIMPL;
} // namespace detail_

/** @brief
 *
 */
class NMerSystem {
private:
    using pimpl_type = detail_::NMerSystemPIMPL;

public:
    /// Type of a pointer to a PIMPL
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    /// Type of an object describing how the fragments were originally made
    using fragmented_system_type = FragmentedSystem;

    /// Type of a read-only reference to the fragments
    using const_fragmented_system_reference = const fragmented_system_type&;

    /// Type used to
    using fragment_type = fragmented_system_type::fragment_type;

    /// Type of a read-only reference to a fragment
    using const_fragment_reference =
      fragmented_system_type::const_fragment_reference;

    /// Type of a read-only reference to a subset of the supersystem's AO basis
    using ao_set_type = fragmented_system_type::ao_set_type;

    /// Type used for modeling, non-negative integers
    using size_type = fragmented_system_type::size_type;

    /// Type used to describe the set of N-Mers
    using nmer_set_type = type::nmers;

    /// Type used to describe an N-Mer
    using nmer_type = typename nmer_set_type::value_type;

    /// Type used to describe a read-only referenc to an N-Mer
    using const_nmer_reference = const nmer_type&;

    using capped_nmers = std::map<nmer_type, fragment_type>;

    NMerSystem() noexcept;

    NMerSystem(fragmented_system_type frags, capped_nmers nmers);

    /** @brief Creates a new NMerSystem with the provided PIMPL
     *
     *  This ctor is primarily envisioned as being used internally for memory
     *  optimizations. It's exposed so: we don't have to rely on friendship to
     *  use it, and/or in case the user wants to do their own optimizations.
     *
     *  @param[in] pimpl The instance powering the class.
     *
     *  @throw None No throw guarantee.
     */
    NMerSystem(pimpl_pointer pimpl) noexcept;

    /// Standard defaulted no-throw dtor
    ~NMerSystem() noexcept;

    /** @brief Returns the number of n-mers in this set.
     *
     *  This function is used to determine the number of n-mers that the
     *  supersystem has been fragmented into.
     *
     *  @return The number of n-mers that the system has been fragmented into.
     *
     *  @throw None No throw guarantee.
     */
    size_type size() const noexcept;

    const_nmer_reference nmer(size_type i) const;

    const_fragmented_system_reference fragments() const;

    ao_set_type ao_basis_set(const_nmer_reference nmer) const;
    ao_set_type ao_basis_set(const_fragment_reference frag) const;

    size_type n_electrons(const_nmer_reference nmer) const;
    size_type n_electrons(const_fragment_reference frag) const;

private:
    /// Type of a mutable reference to the PIMPL
    using pimpl_reference = pimpl_type&;

    /// Type of a read-only reference to the PIMPL
    using const_pimpl_reference = const pimpl_type&;

    pimpl_reference pimpl_();

    const_pimpl_reference pimpl_() const;

    /// The object actually implementing this class.
    pimpl_pointer m_pimpl_;
};

} // namespace ghostfragment
