#pragma once
#include "ghostfragment/fragmented_system.hpp"
#include "ghostfragment/types.hpp"
namespace ghostfragment {
namespace detail_ {
class NMerSystemPIMPL;
} // namespace detail_

/** @brief Describes how a supersystem has been broken up into unions of
 *         fragments.
 *
 *  This class models a view of a supersystem after it has been decomposed into
 *  unions of fragments, i.e., n-mers. The n-mers remember their history (i.e.,
 *  know which fragments formed them) and the fragments are accessible as well.
 *
 */
class NMerSystem {
private:
    /// Type of the class storing this instance's state.
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

    /** @brief Copy ctor
     *
     *  This ctor will deep copy the state contained in @p other and use the
     *  deep copy to initialze a new NMerSystem instance.
     *
     *  @param[in] other The NMerSystem being copied.
     *
     *  @throw std::bad_alloc if there is a problem copying @p other. Strong
     *                        throw guarantee.
     */
    NMerSystem(const NMerSystem& other);

    /** @brief Move ctor
     *
     *  This ctor will create a new NMerSystem by taking ownership of the state
     *  contained in @p other.
     *
     *  @param[in,out] other The instance who's state is being taken. After this
     *                       call @p other will be in a state consistent with
     *                       being default initialized.
     *
     * @throw None No throw guarantee.
     */
    NMerSystem(NMerSystem&& other) noexcept;

    /** @brief Copy assingment
     *
     *  This operator will replace the state contained in the current instance
     *  (releasing it in the process) with a deep copy of the state contained in
     *  the @p rhs instance.
     *
     *  @param[in] rhs The instance whose state is being copied.
     *
     *  @return The current instance, after replacing its state with a copy of
     *          the state contained in @p rhs.
     *
     *  @throw std::bad_alloc if there's a problem copying the state. Strong
     *                        throw guarantee.
     */
    NMerSystem& operator=(const NMerSystem& rhs);

    /** @brief Move assignment
     *
     *  This operator will overwrite the state contained in the current instance
     *  (releasing it in the process) with the state contained in @p rhs.
     *
     *  @param[in,out] rhs the instance who's state is being taken. After this
     *                     call @p rhs will be in a state consistent with being
     *                     default initialized.
     *
     *  @return The current instance, after replacing its state with the state
     *          in @p rhs.
     *
     *  @throw None No throw guarantee.
     */
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

    /** @brief Compares two NMerSystem instances for equality.
     *
     *  Two NMerSystem instances are equal if they were created from the same
     *  set of fragments (as determined by comparing the FragmentedSystem
     *  instances) and if they contain the same set of NMers.
     *
     *  @param[in] rhs The NMerSystem being compared to the current instance.
     *
     *  @return True if the NMerSystem
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const NMerSystem& rhs) const noexcept;

    /** @brief Hashes the state in the current instance.
     *
     *  @param[in,out] h The object which will be hashing the state of this
     *                   instance. After this call the internal state of @p h
     *                   will be updated to contain a hash of the present
     *                   instance's state.
     */
    void hash(type::Hasher&) const;

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

/** @brief Determines if two NMerSystem instances are different.
 *  @relates NMerSystem
 *
 *  This operator simply negates NMerSystem::operator==. See
 *  NMerSystem::operator== for details on how NMerSystem instances are compared.
 *
 *  @param[in] lhs The instance on the left side of the operator.
 *  @param[in] rhs The instance being compared to @p lhs.
 *
 *  @return False if @p lhs and @p rhs compare equal and true otherwise.
 *
 *  @throw None No throw guarantee.
 */
inline bool operator!=(const NMerSystem& lhs, const NMerSystem& rhs) noexcept {
    return !(lhs == rhs);
}

} // namespace ghostfragment
