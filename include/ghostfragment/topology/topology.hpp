#pragma once
#include "ghostfragment/topology/distance.hpp"
#include <array>
#include <memory>

namespace ghostfragment::topology {
namespace detail_ {
class TopologyPIMPL;
}

class Topology {
public:
    using pimpl_type    = detail_::TopologyPIMPL;
    using pimpl_ptr     = std::unique_ptr<pimpl_type>;
    using size_type     = std::size_t;
    using pair_type     = std::array<size_type, 2>;
    using distance_type = Distance;

    void set_distance(pair_type ij, distance_type value);
    void set_distance(pair_type ij, typename distance_type::value_type value);

private:
    pimpl_ptr m_pimpl_;
};

inline Topology::set_distance(pair_type ij,
                              typename distance_type::value_type value) {
    set_distance(std::move(ij), distance_type(value));
}

} // namespace ghostfragment::topology