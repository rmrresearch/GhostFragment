#include "connectivity_table_pimpl.hpp"
#include "ghostfragment/connectivity_table.hpp"

namespace ghostfragment {

using pimpl_type     = typename ConnectivityTable::pimpl_type;
using bond_list_type = typename ConnectivityTable::bond_list_type;

//---------------------------------- CTors -------------------------------------

ConnectivityTable::ConnectivityTable() noexcept = default;

ConnectivityTable::ConnectivityTable(size_type natoms) :
  m_pimpl_(std::make_unique<pimpl_type>(natoms)) {}

ConnectivityTable::~ConnectivityTable() noexcept = default;

void ConnectivityTable::set_n_atoms(size_type natoms) {
    pimpl_().set_natoms(natoms);
}

bond_list_type ConnectivityTable::bonds() const { return pimpl_().bonds(); }

pimpl_type& ConnectivityTable::pimpl_() {
    if(m_pimpl_) return *m_pimpl_;
    m_pimpl_ = std::make_unique<pimpl_type>(natoms);
    return *m_pimpl_;
}

const pimpl_type& ConnectivityTable::pimpl_() const {
    if(m_pimpl_) return *m_pimpl_;
    throw std::runtime_error("There is no PIMPL!!!");
}

} // namespace ghostfragment