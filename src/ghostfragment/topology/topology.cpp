#include "ghostfragment/topology/topology.hpp"
#include "topology_pimpl.hpp"

namespace ghostfragment::topology {

Topology::Topology() noexcept = default;

Topology::~Topology() noexcept = default;

typename Topology::pimpl_type& Topology::pimpl_() {
    if(!m_pimpl_) m_pimpl_ = std::make_unique<pimpl_type>();
    return *m_pimpl_;
}

} // namespace ghostfragment::topology