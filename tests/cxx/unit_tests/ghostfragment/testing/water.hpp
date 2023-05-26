#pragma once
#include <ghostfragment/type/type.hpp>

namespace testing {

/// Creates a system with N waters (waters are in a line along the z-axis)
inline auto water(std::size_t N = 1) {
    using molecule_type = ghostfragment::type::nuclei_set;
    using atom_type     = typename molecule_type::value_type;
    using cart_type     = typename atom_type::coord_type;
    const double dz     = 3.0;
    molecule_type rv;
    for(std::size_t i = 0; i < N; ++i) {
        const double z = i * dz;
        cart_type rO{0.00000000000000, -0.07579039945857, z};
        cart_type rH0{0.86681456860648, 0.60144316994806, z};
        cart_type rH1{-0.86681456860648, 0.60144316994806, z};
        rv.push_back(atom_type{"O", 8ul, rO[0], rO[1], rO[2]});
        rv.push_back(atom_type{"H", 1ul, rH0[0], rH0[1], rH0[2]});
        rv.push_back(atom_type{"H", 1ul, rH1[0], rH1[1], rH1[2]});
    }
    return rv;
}

} // namespace testing
