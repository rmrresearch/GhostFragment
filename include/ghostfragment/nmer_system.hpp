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
    using const_ao_set_reference =
      fragmented_system_type::const_ao_set_reference;

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

    NMerSystem(pimpl_pointer pimpl) noexcept;

    ~NMerSystem() noexcept;

    const_fragmented_system_reference fragments() const;

    const_ao_set_reference ao_basis_set(const_nmer_reference nmer) const;
    const_ao_set_reference ao_basis_set(const_fragment_reference frag) const;

    size_type n_electrons(const_nmer_reference nmer) const;
    size_type n_electrons(const_fragment_reference frag) const;

private:
    /// The object actually implementing this class.
    pimpl_pointer m_pimpl_;
};

} // namespace ghostfragment
