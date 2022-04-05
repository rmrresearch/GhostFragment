#pragma once
#include <ghostfragment/type/type.hpp>

namespace ghostfragment {
namespace detail_ {
class FragmentedSystemPIMPL;
}

/** @brief Abstraction to describe the initial fragmentation of the supersystem.
 *
 *  This class is meant to function similar to a FamilyOfSets<ChemicalSystem>
 *
 *  One of the first major steps in most fragment-based methods is to fragment
 *  the supersystem. To GhostFragment this means:
 *
 *  - establishing some fundamental disjoint representation of the supersystem
 *    (we use atoms for now, but pseudoatoms would work too)
 *  - form the fragments in terms of memebers of the disjoint representation
 *    (for now the fragments are written in terms of atoms). The fragments need
 *    not be disjoint themselves.
 *  - capping the fragments.
 *  - establish a mapping from the disjoint representation to AOs (for now this
 *    means mapping an atom to the AOs associated with it)
 *  - establish a mapping from the disjoint representation to the number of
 *    electrons (for now this is assigning electrons to atoms)
 *
 *  With the above information, this class holds the results of fragmenting the
 *  supersystem and the information required to create ChemicalSystem instances
 *  for each fragment.
 */
class FragmentedSystem {
private:
    /// Type of the PIMPL
    using pimpl_type = detail_::FragmentedSystemPIMPL;

    /// Type of a mutable reference to the PIMPL
    using pimpl_reference = pimpl_type&;

    /// Type of a read-only reference to the PIMPL
    using const_pimpl_reference = const pimpl_type&;

    /// Type of a pointer to the PIMPL
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

public:
    /// Type of the entire molecular supersystem
    using molecule_type = simde::type::molecule;

    /// Type of the container holding the fragments
    using fragment_set_type = type::fragmented_molecule;

    /// Type of a immutable reference to the container holding fragments
    using const_fragment_set_reference = const fragment_set_type&;

    /// Type of a fragment, is a mask/view of the molecule_type object
    using fragment_type = typename fragment_set_type::value_type;

    /// Type of a read-only reference to a fragment instance
    using const_fragment_reference = const fragment_type&;

    /// Type of the entire atomic orbital (AO) basis set for the supersystem
    using ao_basis_set_type = simde::type::ao_basis_set;

    /// Type of a subset of AOs, mask/view of the supersystem's basis
    using ao_set_type = type::ao_set;

    /// Type of a read-only reference to a subset of the AO basis set
    using const_ao_set_reference = const ao_set_type&;

    using capped_type = type::fragment_to_caps::mapped_type;

    using const_capped_reference = const capped_type&;

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

    explicit FragmentedSystem(pimpl_pointer pimpl) noexcept;

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

    const_fragment_set_reference frags() const;

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

    const_capped_reference caps(const_fragment_reference f) const;

    /** @brief Retrieves the molecular AO basis set for the provided set of
     *         atoms.
     *
     *  To actually make ChemicalSystem instances we will need the AO basis sets
     *  for sets of atoms. These sets of atoms will sometimes be fragments, but
     *  they can also be intersections of fragments, unions of fragments, etc.
     *  This function will loop over the atoms in the input and return the AO
     *  basis set which is the union of the AO bases for the atoms.
     *
     *  @param[in] f The set of atoms to form the AO basis set for.
     *
     *  @return The molecular AO basis set for fragment @p f.
     *
     *  @throw std::out_of_range if @p f is not a fragment in the current
     *                           instance. Strong throw guarantee.
     */
    ao_set_type ao_basis_set(const_fragment_reference f) const;

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
    /// Wraps asserting that the instance has a PIMPL, returns it if it does
    pimpl_reference pimpl_();

    /// Wraps asserting that the instance has a PIMPL, returns it if it does
    const_pimpl_reference pimpl_() const;

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
