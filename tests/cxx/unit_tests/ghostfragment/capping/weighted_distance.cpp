#include "../test_ghostfragment.hpp"
#include "../testing/are_caps_equal.hpp"
#include <catch2/catch.hpp>
#include <ghostfragment/property_types/fragmenting/capped_fragments.hpp>

using my_pt        = ghostfragment::pt::CappedFragments;
using traits_t     = ghostfragment::pt::CappedFragmentsTraits;
using frags_t      = typename traits_t::frags_type;
using bonds_t      = typename traits_t::broken_bonds_type;
using cap_set_type = typename frags_t::cap_set_type;
using cap_type     = typename cap_set_type::value_type;
using nuclei_type  = typename frags_t::supersystem_type::value_type;

namespace testing {

inline auto caps_methane_one() { return cap_set_type{}; }

inline auto caps_ethane_one() {
    cap_set_type caps;
    nuclei_type c0("H", 1ul, 1837.289, 1.66138, 1.17415, 0.0);
    caps.emplace_back(0, 1, c0);

    nuclei_type c1("H", 1ul, 1837.289, 0.698712, 0.493801, 0.0);
    caps.emplace_back(1, 0, c1);

    return caps;
}

inline auto caps_propane_one() {
    cap_set_type caps;
    nuclei_type c0("H", 1ul, 1837.289, 1.66138, 1.17415, 0.0);
    caps.emplace_back(0, 1, c0);

    nuclei_type c1("H", 1ul, 1837.289, 0.698712, 0.493801, 0.0);
    nuclei_type c2("H", 1ul, 1837.289, 4.02148, 0.493801, 0.0);
    caps.emplace_back(1, 0, c1);
    caps.emplace_back(1, 2, c2);

    nuclei_type c3("H", 1ul, 1837.289, 3.05881, 1.17415, 0.0);
    caps.emplace_back(2, 1, c3);

    return caps;
}

inline auto caps_propane_two() {
    cap_set_type caps;

    nuclei_type c1("H", 1ul, 1837.289, 0.698712, 0.493801, 0.0);
    caps.emplace_back(1, 0, c1);

    nuclei_type c0("H", 1ul, 1837.289, 4.02148, 0.493801, 0.0);
    caps.emplace_back(1, 2, c0);

    return caps;
}
} // namespace testing

using namespace testing;

TEST_CASE("Weighted Distance Capping") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("Weighted Distance");

    SECTION("Methane fragment (size 1)") {
        auto corr = caps_methane_one();
        auto hc   = hydrocarbon_fragmented_nuclei(1, 1);
        bonds_t bonds;

        auto test = mod.run_as<my_pt>(hc, bonds);
        REQUIRE(are_caps_equal(corr, test.cap_set()));
    }

    SECTION("Ethane fragment (size 1)") {
        auto corr = caps_ethane_one();
        auto hc   = hydrocarbon_fragmented_nuclei(2, 1);
        bonds_t bonds{{0, 1}, {1, 0}};
        auto test = mod.run_as<my_pt>(hc, bonds);
        REQUIRE(are_caps_equal(corr, test.cap_set()));
    }

    SECTION("Propane fragment (size 1)") {
        auto corr = caps_propane_one();
        auto hc   = hydrocarbon_fragmented_nuclei(3, 1);
        bonds_t bonds{{0, 1}, {1, 0}, {1, 2}, {2, 1}};

        auto test = mod.run_as<my_pt>(hc, bonds);
        REQUIRE(are_caps_equal(corr, test.cap_set()));
    }

    SECTION("Propane fragment (size 2)") {
        auto corr = caps_propane_two();
        auto hc   = hydrocarbon_fragmented_nuclei(3, 2);
        bonds_t bonds{{1, 0}, {1, 2}};
        auto test = mod.run_as<my_pt>(hc, bonds);
        REQUIRE(are_caps_equal(corr, test.cap_set()));
    }
}
