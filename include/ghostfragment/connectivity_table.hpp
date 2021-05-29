#pragma once
#include <array>
#include <memory>
#include <vector>

namespace ghostfragment {
namespace detail_ {
class ConnectivityTablePIMPL;
}

class ConnectivityTable {
public:
    /// Type of an object which implements this class
    using pimpl_type = detail_::ConnectivityTablePIMPL;
    /// A pointer to a PIMPL instance
    using pimpl_ptr = std::unique_ptr<pimpl_type>;

    /// Type used for indexing/sizes
    using size_type = std::size_t;
    /// Type used for a bond
    using pair_type = std::array<size_type, 2>;
    /// Type used for a list of bonds
    using bond_list_type = std::vector<pair_type>;

    /** @brief Creates an empty ConnectivityTable.
     *
     *  The instance created with this ctor is capable of holding the
     *  connectivity information for 0 atoms. Users can call `set_n_atoms` to
     *  make the instance suitable for more atoms.
     *
     *  @throw None No throw guarantee.
     */
    ConnectivityTable() noexcept;

    /** @brief Creates an instance which can hold connectivity information for
     *         @p natoms atoms.
     *
     *  @param[in] natoms The number of atoms the table will be for.
     *
     *  @throw std::bad_alloc if there is not enough memory to allocate the
     *                        internal state. Strong throw guarantee.
     */
    ConnectivityTable(size_type natoms);

    /// Default no-throw dtor
    ~ConnectivityTable() noexcept;

    /** @brief Sets the number of atoms the connectivity table is for.
     *
     *  This works similar to std::vector reserve. Basically it will make the
     *  current instance capable of storing connectivity information for
     *  @p natoms. If @p natoms is not the current the number of atoms that the
     *  table is for, the table will reallocate, and be in a state which has no
     *  bonds.
     *
     *  @param[in] natoms The number of atoms the connectivity table should be
     *                    able to hold.
     *
     *  @throw std::bad_alloc if there is insufficient memory to reallocate the
     *                        backend. Strong throw guarantee.
     */
    void set_n_atoms(size_type natoms);

    /** @brief Returns a list of the bonds in the connectivity table.
     *
     *  This function will uses the internal representation of the connectivity
     *  table to return a list of bonds. Each bond is represented as a pair of
     *  zero-based indices such that the pair `{i, j}` means that atoms `i` and
     *  `j` are bonded. Pairs are always such that `i < j`. The final list is
     *  sorted lexicographically.
     *
     *  @return An `nbonds()` long list of the bonds in the table. Bonds are
     *          sorted in lexicographical order.
     *
     *  @throw std::runtime_error if there is no PIMPL. Strong throw guarantee.
     *  @throw std::bad_alloc if there is insufficient memory to create the
     *                        return type. Strong throw guarantee.
     */
    bond_list_type bonds() const;

private:
    /** @brief Returns the PIMPL in a read/write state.
     *
     *  It is rare, but it is possible for a ConnectivityTable instance to have
     *  no PIMPL (for example if the instance was moved from). This function
     *  will simply return the PIMPL if one exists. If the instance does not
     *  currently have a PIMPL, this function will allocate one and then return
     *  it.
     *
     *  @return The PIMPL with read/write permissions.
     *  @throw std::bad_alloc if there is no PIMPL and allocation of a new PIMPL
     *                        fails. Strong throw guarantee.
     */
    pimpl_type& pimpl_();

    /** @brief Returns the PIMPL in a read/write state, throwing if one is not
     *         present.
     *
     *  It is rare, but it is possible for a ConnectivityTable instance to have
     *  no PIMPL (for example if the instance was moved from). This function
     *  will simply return the PIMPL if one exists. If the instance does not
     *  currently have a PIMPL, this function will raise an error (it can not
     *  allocate a PIMPL because the instance is in a read-only state).
     *
     *  @return The PIMPL in a read-only state.
     *
     *  @throw std::runtime_error if there is no PIMPL. Strong throw guarantee.
     */
    const pimpl_type& pimpl_() const;

    /// The object which implements the ConnectivityTable
    pimpl_ptr m_pimpl_;
};

} // namespace ghostfragment