#pragma once
#include <catch2/catch.hpp>
#include <ghostfragment/property_types/fragmenting/capped_fragments.hpp>

using traits_t     = ghostfragment::pt::CappedFragmentsTraits;
using cap_set_type = traits_t::result_type::cap_set_type;

inline auto are_caps_equal(cap_set_type caps1, cap_set_type caps2) {
    REQUIRE(caps1.size() == caps2.size());

    for(decltype(caps1.size()) i = 0; i < caps1.size(); i++) {
        REQUIRE(caps1[i].get_anchor_index() == caps2[i].get_anchor_index());
        REQUIRE(caps1[i].get_replaced_index() == caps2[i].get_replaced_index());

        auto cap1 = caps1[i].at(0);
        auto cap2 = caps2[i].at(0);

        REQUIRE(cap1.name() == cap2.name());
        REQUIRE(cap1.Z() == cap2.Z());
        REQUIRE(cap1.mass() == cap2.mass());

        REQUIRE(cap1.x() == Approx(cap2.x()).margin(0.0001));
        REQUIRE(cap1.y() == Approx(cap2.y()).margin(0.0001));
        REQUIRE(cap1.z() == Approx(cap2.z()).margin(0.0001));
    }
    return true;
}
