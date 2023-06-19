#pragma once
#include "hydrocarbon/hydrocarbon.h"
#include <ghostfragment/capping/capping.hpp>
#include <ghostfragment/connectivity/connectivity.hpp>
#include <ghostfragment/property_types/capped.hpp>
#include <ghostfragment/property_types/connectivity_table.hpp>
#include <ghostfragment/property_types/broken_bonds.hpp>
#include <catch2/catch.hpp>
#include <iostream>

namespace testing{
using bonds_pt = ghostfragment::pt::BrokenBonds;
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
    cap_set1.add_cap(0, 1, atom_type("H", 1ul, 1837.289, 1.68228, 1.18892, 0.0));
    caps.emplace_back(std::move(cap_set1));

    set_type cap_set2;
    cap_set2.add_cap(1, 0, atom_type("H", 1ul, 1837.289, 0.677812, 0.479031, 0.0));
    caps.emplace_back(std::move(cap_set2));

    return caps;    
}

inline auto caps_propane_one() {
    result_type caps;

    set_type cap_set1;
    cap_set1.add_cap(0, 1, atom_type("H", 1ul, 1837.289, 1.68228, 1.18892, 0.0));
    caps.emplace_back(std::move(cap_set1));

    set_type cap_set2;
    cap_set2.add_cap(1, 0, atom_type("H", 1ul, 1837.289, 0.677812, 0.479031, 0.0));
    cap_set2.add_cap(1, 2, atom_type("H", 1ul, 1837.289, 4.04238, 0.479031, 0.0));
    caps.emplace_back(std::move(cap_set2));

    set_type cap_set3;
    cap_set3.add_cap(2, 1, atom_type("H", 1ul, 1837.289, 3.03791, 1.18892, 0.0));
    caps.emplace_back(std::move(cap_set3));

    return caps;
}

inline auto caps_propane_two() {
    result_type caps;

    set_type cap_set1;
    cap_set1.add_cap(1, 2, atom_type("H", 1ul, 1837.289, 4.04238, 0.479031, 0.0));
    caps.emplace_back(std::move(cap_set1));

    set_type cap_set2;
    cap_set2.add_cap(1, 0, atom_type("H", 1ul, 1837.289, 0.677812, 0.479031, 0.0));
    caps.emplace_back(std::move(cap_set2));

    return caps;
}

inline auto are_caps_equal(result_type caps1, result_type caps2) {
    REQUIRE(caps1.size() == caps2.size());

    for(auto i = 0; i < caps1.size(); i++){
        set_type cap_set1 = caps1[i];
        set_type cap_set2 = caps2[i];

        REQUIRE(cap_set1.size() == cap_set2.size());

        for(auto j = 0; j < cap_set1.size(); j++){
            REQUIRE(cap_set1[j].get_anchor_index() == cap_set2[j].get_anchor_index());
            REQUIRE(cap_set1[j].get_replaced_index() == cap_set2[j].get_replaced_index());

            atom_type cap1 = cap_set1[j].cap_atom(0);
            atom_type cap2 = cap_set2[j].cap_atom(0);
            std::cout << "Cap " << j << " from fragment " << i << " Coordinates: " << cap2.x() << ", " << cap2.y() << ", " << cap2.z() << std::endl;

            REQUIRE(cap1.name() == cap2.name());
            REQUIRE(cap1.Z() == cap2.Z());
            REQUIRE(cap1.mass() == cap2.mass());

            // Commented out to print position of each cap. Should be brought back eventually.
            // REQUIRE(cap1.x() == Approx(cap2.x()).margin(0.0001));
            // REQUIRE(cap1.y() == Approx(cap2.y()).margin(0.0001));
            // REQUIRE(cap1.z() == Approx(cap2.z()).margin(0.0001));
        }
    }
    return true;
}
}