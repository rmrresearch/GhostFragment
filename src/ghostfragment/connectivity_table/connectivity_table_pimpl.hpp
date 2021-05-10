#include "ghostfragment/connectivity_table.hpp"
#include <numeric>
#include <vector>

namespace ghostfragment::detail_ {

/** @brief PIMPL which stores the bonds in an adjacency matrix.
 *
 *  This PIMPL uses an natoms by natoms adjacency matrix to store the bonds. It
 *  only manipulates the elements (i,j) for which i <= j.
 */
class ConnectivityTablePIMPL {
public:
    using size_type = typename ConnectivityTable::size_type;

    ConnectivityTablePIMPL() = default;
    ConnectivityTablePIMPL(size_type natoms) : m_connections_(natoms, false) {}

    void set_natoms(size_type natoms);
    size_type nbonds() const { return std::accumulate(m_connections_.begin) }
    void add_bond(size_type i, size_type j);

private:
    size_type m_natoms_;
    // An adjaceny matrix storing the connections
    std::vector<bool> m_connections_;
};

// ---------------------------- Implementations --------------------------------

void ConnectivityTablePIMPL::set_natoms(size_type natoms) {
    if(natoms == m_natoms_) return;
    if(natoms > m_natoms_) {
        std::vector<bool> temp(max * max, false);
        for(size_type i = 0; i < m_natoms_; ++i) {
            const auto old_row = i * m_natoms_;
            const auto new_row = i * max;
            for(size_type j = i; j < m_natoms_; ++j)
                temp[new_row + j] = m_connections_[old_row + j];
        }
        m_natoms_ = max;
        m_connections_.swap(temp);
    }
}

typename ConnectivityTalbePIMPL::size_type ConnectivityTablePIMPL::nbonds()
  const {
    const size_type zero{0};
    return std::accumulate(m_connections_.begin(), m_connections_.end(), zero);
}

void ConnectivityTablePIMPL::add_bond(size_type i, size_type j) {
    auto max = std::max(i, j);
    auto min = std::min(i, j);
    if(max >= m_natoms_) {}
    m_connections_[min * m_natoms_ + min] = true;
}

} // namespace ghostfragment::detail_