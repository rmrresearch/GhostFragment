#pragma once
#include <memory>

namespace ghostfragment {
namespace detail _ {
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

    ConnectivityTable() noexcept;
    ConnectivityTable(size_type natoms);
    ~ConnectivityTable() noexcept;

    /** @brief Sets the number of atoms the connectivity table is for.
     *
     *  Think of this like std::vector reserve. Basically it will make sure that
     *  the current instance is capable of holding a connectivity table for at
     *  least @p natoms.
     *
     *  @param[in] natoms The number of atoms the connectivity table should be
     *                    able to hold.
     *
     *  @throw std::bad_alloc if there is insufficient memory to reallocate the
     *                        backend.
     */
    void set_n_atoms(size_type natoms);

private:
    /// The object which implements the ConnectivityTable
    pimpl_ptr m_pimpl_;
};

} // namespace ghostfragment