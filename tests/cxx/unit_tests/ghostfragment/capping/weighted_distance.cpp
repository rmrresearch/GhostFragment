#include "../test_ghostfragment.hpp"
#include <hydrocarbon/hydrocarbon_fragment.hpp>
#include "weighted_distance.hpp"
#include <testing/are_caps_equal.hpp>

using namespace testing::weighted;
using namespace testing;

TEST_CASE("Weighted Distance Capping") {
    using input_type  = const chemist::FragmentedNuclei&;
    using pt      = ghostfragment::pt::Capped;
    using bonds_pt = ghostfragment::pt::BrokenBonds;
    using traits_t   = ghostfragment::pt::CappedTraits;
    using result_type = traits_t::result_type;
    using set_type = result_type::value_type;
    using atom_type  = set_type::atom_type;

    auto mm = testing::initialize();
    auto& mod = mm.at("Weighted Distance");

    SECTION("Methane fragment (size 1)") {
        auto corr = caps_methane_one();
        input_type hc{hydrocarbon_fragmented_nuclei(1, 1)};
        result_type test = mod.run_as<pt>(hc);
        REQUIRE(are_caps_equal(corr, test));
    }

    SECTION("Ethane fragment (size 1)") {
        auto corr = caps_ethane_one();
        input_type hc{hydrocarbon_fragmented_nuclei(2, 1)};
        result_type test = mod.run_as<pt>(hc);
        REQUIRE(are_caps_equal(corr, test));
    }

    SECTION("Propane fragment (size 1)") {
        auto corr = caps_propane_one();
        input_type hc{hydrocarbon_fragmented_nuclei(3, 1)};
        result_type test = mod.run_as<pt>(hc);
        REQUIRE(are_caps_equal(corr, test));
    }

    SECTION("Propane fragment (size 2)") {
        auto corr = caps_propane_two();
        input_type hc{hydrocarbon_fragmented_nuclei(3, 2)};
        result_type test = mod.run_as<pt>(hc);
        REQUIRE(are_caps_equal(corr, test));
    }
}