#pragma once
#include "water.hpp"
#include <ghostfragment/type/type.hpp>

namespace testing {

// Makes fragments where each water is in a single fragment
inline auto fragmented_water(std::size_t N) {
    auto molecule    = water(N);
    using frag_type  = ghostfragment::type::fragmented_molecule;
    using value_type = frag_type::value_type;
    using size_type  = value_type::size_type;

    frag_type frags(molecule);
    for(size_type i = 0; i < N; ++i) {
        auto water = frags.new_subset();
        for(size_type j = 0; j < 3; ++j) water.insert(i * 3 + j);
        frags.insert(water);
    }
    return frags;
}

} // namespace testing
