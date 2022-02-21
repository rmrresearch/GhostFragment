#pragma once
#include "ghostfragment/types.hpp"

namespace ghostfragment {
namespace detail_ {
class FragmentedSystemPIMPL;
}

/** @brief Abstraction to describe the initial fragmentation of the supersystem.
 *
 *  One of the first major steps in most fragment-based methods is to fragment
 *  the supersystem. To GhostFragment this means: dividing the atoms into sets,
 *  pairing each of those sets with an AO basis set, and assigning electrons to
 *  each of those sets. This class holds the results of fragmenting the
 *  supersystem and holds the information required to create System instances
 *  for each fragment.
 */
class FragmentedSystem {
public:
    /// Type of the entire molecular supersystem
    using molecule_type = simde::type::molecule;

    /// Type of the container holding the fragments
    using fragment_set_type = type::fragmented_molecule;

    /// Type of a fragment, is a mask/view of the molecule_type object
    using fragment_type = typename fragment_set_type::value_type;

    /// Type of a read-only reference to a fragment instance
    using const_fragment_reference = const fragment_type&;

    /// Type of the entire atomic orbital (AO) basis set for the supersystem
    using ao_basis_set_type = simde::type::ao_basis_set;

    /// Type of a fragment's AO basis set, mask/view of the supersystem's basis
    using fragment_basis_type = typename type::fragmented_aos::value_type;

    /// Type of a read-only reference to a fragment's AO basis set
    using const_fragment_basis_reference = const fragment_basis_type&;

    /// Type of a map from fragments to
    using frag2ao_basis_type = type::fragment_to_ao_basis;

    /** @brief Used for offsets and counts.
     *
     *  This is a 32-bit unsigned integer type. The maximum value of a 32-bit
     *  integer is 4,294,967,295. From this class's perspective, that means we
     *  can index 4 billion fragments, each atom and fragment can have up to 4
     *  billion electrons (that's about 43 million uranium atoms in a fragment).
     */
    using size_type = std::uint32_t;

    /// Type of a map from atom offset to number of electrons in the atom
    using atom2nelectron_type = std::vector<size_type>;

    /** @brief Creates a new fragmented system which is empty.
     *
     *  The FragmentedSystem resulting from the default ctor is empty (has no
     *  fragments). At the moment the only way to make the resulting instance
     *  non-empty is to assign to it.
     *
     *  @throw None No throw guarantee.
     */
    FragmentedSystem() noexcept;

    /** @brief Creates a FragmentedSystem with the provided state.
     *
     *  @param[in] frags A container filled with subsets of the parent system.
     *                   Each subset will treated as a fragment. Fragments may
     *                   overlap.
     *  @param[in] frag2aos A map from fragments in @p frags to their molecular
     *                      AO basis sets.
     *  @param[in] atom2ne A map from atoms in the parent system to their number
     *                     of electrons. Indexing of @p atom2ne should match the
     *                     order in the parent system.
     *
     *  @throw std::bad_alloc if there is a problem allocating the internal
     *                        state. Strong throw guarantee.
     */
    FragmentedSystem(fragment_set_type frags, frag2ao_basis_type frags2aos,
                     atom2nelectron_type atom2ne);

    /** @brief Makes a deep-copy of this FragmentedSystem
     *
     *  @param[in] other The instance being copied.
     *
     *  @throw std::bad_alloc if there is a problem allocating the internal
     *                        state. Strong throw guarantee.
     */
    FragmentedSystem(const FragmentedSystem& other);

    /** @brief Takes ownership of another FragmentedSystem's state.
     *
     *  @param[in,out] other The instance whose state is being taken. After this
     *                       call, @p other will in a state which is equivalent
     *                       to default initialization.
     *
     *  @throw None no throw guarantee.
     */
    FragmentedSystem(FragmentedSystem&& other) noexcept;

    /** @brief Sets this instance's state to a deep copy of @p rhs 's state.
     *
     *  After this call any state which this instance may have possessed will be
     *  released.
     *
     *  @param[in] rhs The instance we are copying the state from.
     *
     *  @return The current instance, after setting its state to a copy of
     *          @p rhs 's state.
     *
     *  @throw std::bad_alloc if there is a problem allocating state.
     */
    FragmentedSystem& operator=(const FragmentedSystem& rhs);

    /** @brief Overwrites this instance's state with @p rhs 's state.
     *
     *  @param[in] rhs The instance whose state is being taken. After this call
     *                 @p rhs will have a state which is equivalent to default
     *                 initialization.
     *
     *  @return The current instance, after taking ownership of @p rhs's state.
     *
     *  @throw None No throw guarantee.
     */
    FragmentedSystem& operator=(FragmentedSystem&& rhs) noexcept;

    /// Defaulted nothrow dtor
    ~FragmentedSystem() noexcept;

    /** @brief Returns the number of fragments
     *
     *  This accessor is used to determine how many fragments the supersystem
     *  has been subdivided in to.
     *
     *  @return The number of fragments the supersystem has been subdivided in
     *          to.
     *
     *  @throw None No throw guarantee.
     */
    size_type nfrags() const noexcept;

    /** @brief Retrieves the @p i -th fragment.
     *
     *  This function is used to retrive a fragment by index. The ordering of
     *  the fragments is the same as the input order.
     *
     *  @param[in] i The (zero-based) index of the requested fragment.
     *
     *  @throw std::out_of_range if @p i is not in the range [0, nfrags()).
     *                           Strong throw guarantee.
     */
    const_fragment_reference fragment(size_type i) const;

    /** @brief Retrieves the molecular AO basis set for the provided fragment.
     *
     *  @param[in] f The fragment who's AO basis set is being requested.
     *
     *  @return The molecular AO basis set for fragment @p f.
     *
     *  @throw std::out_of_range if @p f is not a fragment in the current
     *                           instance. Strong throw guarantee.
     */
    const_fragment_basis_reference ao_basis_set(
      const_fragment_reference f) const;

    /** @brief Retrieves the number of electrons for the provided fragment.
     *
     *  This function determines the number of electrons in fragment @p f. Note
     *  that if the fragments overlap then summing up `n_electrons` for each
     *  fragment will not equal the total number of electrons in the
     *  supersystem.
     *
     *  @param[in] f This function determines how many electrons are in this
     *               fragment.
     *
     *  @throw std::out_of_range if @f is not a fragment in this instance.
     *                           Strong throw guarantee.
     */
    size_type n_electrons(const_fragment_reference f) const;

    /** @brief Determines if two FragmentedSystem instances are equal.
     *
     *  Two FragmentedSystem instances are equal if:
     *  - the associated parent objects are equal,
     *  - the parent objects are fragmented the same way,
     *  - the fragments map to the same molecular AO basis sets, and
     *  - the fragments contain the same number of electrons.
     *
     *  If any of the above points do not hold, then the FragmentedSystem
     *  instances are different.
     *
     *  @param[in] rhs The FragmentedSystem instance to which the present
     *                 instance is being compared.
     *
     *  @throw None no throw guarantee.
     */
    bool operator==(const FragmentedSystem& rhs) const noexcept;

    /** @brief Hashes the current instance.
     *
     *  @param[in] h The object which will be hashing the state of this
     *               instance. After this call, the internal state of @p h will
     *               be updated to contain a hash of the present instance's
     *               state.
     */
    void hash(type::Hasher& h) const;

private:
    /// Type of the PIMPL
    using pimpl_type = detail_::FragmentedSystemPIMPL;

    /// Type of a pointer to the PIMPL
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    /// Wraps he process of checking if @p f is in this instance
    void assert_frag_(const_fragment_reference f) const;

    /// Contains the actual state of the class
    pimpl_pointer m_pimpl_;
};

/** @brief Determines if two FragmentedSystem instances are different.
 *
 *  @relates FragmentedSystem
 *
 *  This function simply negates FragmentedSystem::operator==. See there for a
 *  complete description of what equality entails.
 *
 *  @param[in] lhs The FragmentedSystem instance on the left of the not-equal
 *                 operator.
 *  @param[in] rhs The FragmentedSystem instance on the right of the not-equal
 *                 operator.
 *
 *  @return False if @p lhs is equivalent to @p rhs and true otherwise.
 *
 *  @throw None No throw guarantte.
 */
inline bool operator!=(const FragmentedSystem& lhs,
                       const FragmentedSystem& rhs) {
    return !(lhs == rhs);
}

} // namespace ghostfragment
