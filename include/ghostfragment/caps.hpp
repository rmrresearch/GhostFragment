#pragma once
#include <ghostfragment/type/nuclei.hpp>
#include <ghostfragment/type/utility.hpp>

namespace ghostfragment {

/** @brief A set of caps.
 *
 *  When fragmenting molecular systems we sometimes need to break covalent
 *  bonds. If this happens, the atoms involved in the bond will experience very
 *  different electronic environments in the fragment compared to the
 *  supersystem (typically the atoms in the fragment are radicals without the
 *  bonded atom). To minimize such a perturbation one usually "caps" the
 *  severed bonds. This class models the set of caps needed to cap a set of
 *  fragments.
 *
 *  Conceptually this class is the union of a type::nuclei_set (which contains
 *  the atoms used as caps) and a map detailing which atoms in the supersystem
 *  are replaced by which caps. This means that this class assumes that caps are
 *  single atoms. Conceivably one can use this class for multi-atom caps, if
 *  desired, by a call like:
 *
 *  ```
 *  non_default.add_cap(atom0, 0);
 *  non_default.add_cap(atom1, 0);
 *  ```
 *
 *  i.e., by replacing the same atom with multiple caps. However, this is not
 *  tested and may require refactoring to enable.
 *
 *  N.B. this class does NOT keep a sychronized copy of the supersystem (or
 *  similarly the fragmented supersystem). Hence it is the user's responsibility
 *  to keep the information in this class synchronized with the supersystem
 *  and/or fragments (e.g., changing the indices of the supersystem atoms would
 *  invalidate calls to `replaced_atom` without also modifying the Caps
 *  instance associated with the supersystem). In practice, we have introduced
 *  the FragmentedSystem class for maintaining the various pieces of the
 *  fragmented system and keeping them synchronized.
 */
class Caps {
private:
    /// The type used to store the caps
    using cap_set_type = type::nuclei_set;

public:
    /// A type like chemist::Atom
    using value_type = cap_set_type::value_type;

    /// Type of a read-only reference to a cap
    using const_reference = const value_type&;

    /// An unsigned integer type
    using size_type = cap_set_type::size_type;

    /** @brief Returns the number of caps in this instance.
     *
     *  Each Caps instance contains 0 or more caps. This method is used to
     *  determine how many caps are in the present instance.
     *
     *  @return The number of caps.
     *
     *  @throw None No throw guarantee.
     */
    size_type size() const noexcept { return m_caps_.size(); }

    /** @brief Determines if a cap is in the present set.
     *
     *  The Caps class behaves like an ordered set of caps. This means that a
     *  given cap either appears in the instance or does not.
     *
     *  @param[in] cap The cap we are looking for in the present instance.
     *
     *  @return True if @p cap is in the current instance and false otherwise.
     *
     *  @throw None no throw guarantee
     */
    bool count(const_reference cap) const noexcept;

    /** @brief Adds a cap (and the index of the replaced atom)
     *
     *  To effectively manage caps we need not only the cap (i.e. the atomic
     *  identy and position), but also what atom it replaces. The latter allows
     *  us to automatically work out caps for n-mers.
     *
     *  @param[in] cap The actual atomic identity of the cap (as specified by a
     *                 type::nuclei_set::value_type object).
     *  @param[in] idx_replaced The index of the atom in the supersystem that is
     *                          replaced by this cap.
     *
     *  @throw std::bad_alloc if there is a problem allocating memory for the
     *                        new cap. Weak throw guarantee.
     */
    void add_cap(value_type cap, size_type idx_replaced);

    /** @brief Returns the i-th cap in this instance.
     *
     *  This function is used to retrieve a cap by offset. Functionly this is
     *  similar to the `at` method, but differs in that `at` bounds-checks the
     *  offset whereas this function does not.
     *
     *  @param[in] i The offset for the requested cap. Assumed to be in the
     *               range [0, size()), but no bounds check is performed.
     *
     *  @return An immutable reference to the requested cap (if @p i is in
     *          bounds; undefined behavior ensues if @p i is not in bounds).
     *
     *  @throw None No throw guarantee (even if @p i is not in bounds).
     */
    const_reference operator[](size_type i) const noexcept;

    /** @brief Retursn the i-th cap in this instance (after a boudns check)
     *
     *  This function is the same as `operator[]` except that it throws if the
     *  offset is not in bounds.
     *
     *  @param[in] i The offset for the requested cap. Must be in the range
     *               [0, size()).
     *
     *  @return An immutable reference to the requested cap.
     *
     *  @throw std::out_of_range if @p i is not in the range [0, size()). Strong
     *                           throw guarantee.
     */
    const_reference at(size_type i) const;

    /** @brief Returns the supersystem offset of the atom replaced by a cap
     *
     *  This method is used to figure out which superset atom is replaced by a
     *  cap.
     *
     *  @param[in] i the offset of the cap. Must be in the range [0, size()).
     *
     *  @return The supersystem offset of the cap being replaced.
     *
     *  @throw std::out_of_range if @p i is not in the range [0, size()). Strong
     *                           throw guarantee.
     */
    size_type replaced_atom(size_type i) const;

    /** @brief Returns the set of caps.
     *
     *  This method provides the type::nuclei_set object holding the caps.
     *
     *  @return An immutable reference to the set of caps.
     *
     *  @throw None No throw guarantee.
     */
    const cap_set_type& nuclei() const noexcept { return m_caps_; }

    /** @brief Determines if two Cap instances are value equal.
     *
     *  Two Cap instances are value equal if they contain the same set of caps,
     *  those caps were inserted in the same order, and those caps replace the
     *  same atoms.
     *
     *  @param[in] rhs The instance we are comparing to.
     *
     *  @return True if @p rhs compares value equal to this instance and false
     *          otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const Caps& rhs) const noexcept;

    void hash(type::Hasher& h) const;

private:
    /// Code factorization for asserting @p i is in the range [0, size())
    void assert_offset_(size_type i) const;

    /// The actual set of caps
    cap_set_type m_caps_;

    /// Maps cap offset to the supersystem offset of the replaced atom
    std::vector<size_type> m_atom_replaced_;
};

/** @brief Determines if two Caps instances are different.
 *  @relates Caps
 *
 *  This function simply negates Caps::operator==. See the description there for
 *  details of what it means for two Caps instances to be value equal.
 *
 *  @param[in] lhs The Caps instance on the left of the not-equal-to operator.
 *  @param[in] rhs The Caps instance on the right of the not-equal-to operator.
 *
 *  @return False if @p lhs is value equal to @p rhs and true otherwise.
 *
 *  @throw None No throw guarantee.
 */
inline bool operator!=(const Caps& lhs, const Caps& rhs) noexcept {
    return !(lhs == rhs);
}

} // namespace ghostfragment
