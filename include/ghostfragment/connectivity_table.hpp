#pragma once
#include <memory>

namespace ghostfragment {
namespace detail_ {
class ConnectivityTablePIMPL;
}

class ConnectivityTable {
public:
    /// Type used for indexing/sizes
    using size_type = std::size_t;
    /// Type of an object which implements this class
    using pimpl_type = detail_::ConnectivityTablePIMPL;
    /// A pointer to a PIMPL instance
    using pimpl_ptr = std::unique_ptr<pimpl_type>;

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

private:
    /// The object which implements the ConnectivityTable
    pimpl_ptr m_pimpl_;
};

} // namespace ghostfragment