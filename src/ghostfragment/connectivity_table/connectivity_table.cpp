#include "connectivity_table_pimpl.hpp"
#include "ghostfragment/connectivity_table.hpp"

namespace ghostfragment {

//---------------------------------- CTors -------------------------------------

ConnectivityTable::ConnectivityTable() noexcept = default;

ConnectivityTable::ConnectivityTable(size_type natoms) :
  m_pimpl_(std::make_unique<pimpl_type>(natoms)) {}

ConnectivityTable::~ConnectivityTable() noexcept = default;

void ConnectivityTable::set_n_atoms(size_type natoms) {
    m_pimpl_->set_natoms(natoms);
}

} // namespace ghostfragment