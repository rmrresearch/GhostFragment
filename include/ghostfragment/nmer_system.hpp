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

    /// Type used to map N-mers to their cap set
    using capped_nmers = std::map<nmer_type, fragment_type>;

    /** @brief Creates an empty NMerSystem instance.
     *
     *  The default ctor creates an NMerSystem which is more or less a
     *  placeholder. The resulting instance functions like an empty container.
     *  The only way to add N-mers to the resulting instance is to assign to it
     *  from an instance with state.
     *
     *  @throw None No throw guarantee.
     */
    NMerSystem() noexcept;

    /** @brief Creates an NMerSystem with the provided state.
     *
     *  This is the ctor most users will use. It takes the original
     *  FragmentedSystem and the n-mers formed from the fragments.
     *
     *  @param[in] frags The fragments used to create the n-mers.
     *  @param[in] nmers The n-mers formed from the fragments.
     *
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL. Strong
     *                        throw guarantee.
     */
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

    NMerSystem(const NMerSystem& other);

    NMerSystem(NMerSystem&& other) noexcept;

    NMerSystem& operator=(const NMerSystem& rhs);

    NMerSystem& operator=(NMerSystem&& rhs) noexcept;

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

    /** @brief Retrieves an n-mer by offset.
     *
     *
     *  @param[in] i The 0-based offset of the requested n-mer. @p i must be in
     *               the range [0, size()).
     *
     *  @return A read-only reference to the requested n-mer.
     *
     *  @throw std::out_of_range if @p i is not in the range [0, size()). Strong
     *                           throw guarantee.
     */
    const_nmer_reference nmer(size_type i) const;

    /** @brief Retrieves the fragments used to create the n-mers.
     *
     *  @return A read-only reference to the original fragmented representation
     *          of the supersystem used to create the n-mers.
     *
     *  @throw std::runtime_error if the instance does not have a PIMPL. Strong
     *                            throw guarantee.
     */
    const_fragmented_system_reference fragments() const;

    /** @brief Determines the AO basis set for the given set of fragments.
     *
     *  This function will flatten the provided n-mer into a set of atoms (the
     *  actual process simply takes the union of the atoms in each fragment and
     *  thus works for non-disjoint n-mers and fragments) and then takes the
     *  union of the AO basis sets for each atom in the resulting set.
     *
     *  @param[in] nmer The set of fragments to determine the AO basis set for.
     *                  @p nmer does not neeed to actually be an n-mer;
     *                  however, it does need to be comprised of the same
     *                  fragments as this instance.
     *
     *  @return The AO basis set for @p nmer.
     *
     *  @throw std::runtime_error if this instance does not have a PIMPL. Strong
     *                            throw guarantee.
     *
     *  @throw std::out_of_range if the fragments in @p nmer are not part of the
     *                           fragments used to make this instance. Strong
     *                           throw guarantee.
     */
    ao_set_type ao_basis_set(const_nmer_reference nmer) const;

    /** @brief Determines the AO basis set for a set of atoms.
     *
     *  This function will loop over the set of atoms in the provided fragment
     *  and take the union of the AO basis sets associated with each atom.
     *
     *  This function is a convience function for calling
     *  `fragments().ao_basis_set` with the provided fragment.
     *
     *  @param[in] frag The set of atoms to determine the AO basis set for. The
     *                  actual input does not need to be a fragment f
     *                  used to create this instance. All that matters is that
     *                  @p frag is formed from the same supersystem.
     *
     *  @return The AO basis set for @p frag.
     *
     *  @throw std::runtime_error if the instance does not contain a PIMPL.
     *                            Strong throw guarantee.
     *  @throw std::out_of_range if @p frag is not formed from the same
     *                           supersystem as the current instance. Strong
     *                           throw guarantee.
     *
     */
    ao_set_type ao_basis_set(const_fragment_reference frag) const;

    /** @brief Computes the number of electrons in an n-mer.
     *
     *  This function will flatten the provided n-mer into a set of atoms (the
     *  actual process simply takes the union of the atoms in each fragment and
     *  thus works for non-disjoint n-mers and fragments) and then sum up the
     *  number of electrons for each atom in the resulting set.
     *
     *  @param[in] nmer The set of fragments to compute the number of electrons
     *                  for. The actual input does not need to be an n-mer found
     *                  in this instance. All that matters is that @p nmer is
     *                  formed from the same set of fragments.
     *
     *  @return The number of electrons in @p nmer.
     *
     *  @throw std::runtime_error if the instance does not contain a PIMPL.
     *                            Strong throw guarantee.
     *  @throw std::out_of_range if @p nmer is not formed from the same set of
     *                           fragments as the current instance. Strong throw
     *                           guarantee.
     *
     */
    size_type n_electrons(const_nmer_reference nmer) const;

    /** @brief Computes the number of electrons in a set of atoms.
     *
     *  This function will loop over the set of atoms in the provided fragment
     *  and sum up the number of electrons associated with each atom.
     *
     *  This function is a convience function for calling
     *  `fragments().n_electrons` with the provided fragment.
     *
     *  @param[in] frag The set of atoms to compute the number of electrons
     *                  for. The actual input does not need to be a fragment f
     *                  used to create this instance. All that matters is that
     *                  @p frag is formed from the same supersystem.
     *
     *  @return The number of electrons in @p frag.
     *
     *  @throw std::runtime_error if the instance does not contain a PIMPL.
     *                            Strong throw guarantee.
     *  @throw std::out_of_range if @p frag is not formed from the same
     *                           supersystem as the current instance. Strong
     *                           throw guarantee.
     *
     */
    size_type n_electrons(const_fragment_reference frag) const;

    bool operator==(const NMerSystem& rhs) const noexcept;

private:
    /// Type of a mutable reference to the PIMPL
    using pimpl_reference = pimpl_type&;

    /// Type of a read-only reference to the PIMPL
    using const_pimpl_reference = const pimpl_type&;

    /// Asserts we have a PIMPL and returns a modifiable reference to it
    pimpl_reference pimpl_();

    /// Asserts we have a PIMPL and returns a read-only reference to it
    const_pimpl_reference pimpl_() const;

    /// The object actually implementing this class.
    pimpl_pointer m_pimpl_;
};

inline bool operator!=(const NMerSystem& lhs, const NMerSystem& rhs) noexcept {
    return !(lhs == rhs);
}

} // namespace ghostfragment
