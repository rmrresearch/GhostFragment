#pragma once
#include "hydrocarbon/hydrocarbon.h"
#include <ghostfragment/capping/capping.hpp>
#include <ghostfragment/connectivity/connectivity.hpp>
#include <ghostfragment/property_types/capped.hpp>
#include <ghostfragment/property_types/connectivity_table.hpp>
#include <ghostfragment/property_types/broken_bonds.hpp>
#include <catch2/catch.hpp>

namespace testing::single{
using traits_t   = ghostfragment::pt::CappedTraits;
using result_type = traits_t::result_type;
using set_type = result_type::value_type;
using atom_type  = set_type::atom_type;

inline auto caps_methane_one() {
    result_type caps;

    set_type cap_set1;

    caps.emplace_back(std::move(cap_set1));

    return caps;
}

inline auto caps_ethane_one() {
    result_type caps;

    set_type cap_set1;
    cap_set1.add_cap(0, 1, atom_type("H", 1ul, 1837.289, 2.360094094, 1.667949599, 0.0));
    caps.emplace_back(std::move(cap_set1));

    set_type cap_set2;
    cap_set2.add_cap(1, 0, atom_type("H", 1ul, 1837.289, 0.0, 0.0, 0.0));
    caps.emplace_back(std::move(cap_set2));

    return caps;    
}

inline auto caps_propane_one() {
    result_type caps;

    set_type cap_set1;
    cap_set1.add_cap(0, 1, atom_type("H", 1ul, 1837.289, 2.360094094, 1.667949599, 0.0));
    caps.emplace_back(std::move(cap_set1));

    set_type cap_set2;
    cap_set2.add_cap(1, 0, atom_type("H", 1ul, 1837.289, 0.0, 0.0, 0.0));
    cap_set2.add_cap(1, 2, atom_type("H", 1ul, 1837.289, 4.720188189, 0.0, 0.0));
    caps.emplace_back(std::move(cap_set2));

    set_type cap_set3;
    cap_set3.add_cap(2, 1, atom_type("H", 1ul, 1837.289, 2.360094094, 1.667949599, 0.0));
    caps.emplace_back(std::move(cap_set3));

    return caps;
}

inline auto caps_propane_two() {
    result_type caps;

    set_type cap_set1;
    cap_set1.add_cap(1, 2, atom_type("H", 1ul, 1837.289, 4.720188189, 0.0, 0.0));
    caps.emplace_back(std::move(cap_set1));

    set_type cap_set2;
    cap_set2.add_cap(1, 0, atom_type("H", 1ul, 1837.289, 0.0, 0.0, 0.0));
    caps.emplace_back(std::move(cap_set2));

    return caps;
}
}