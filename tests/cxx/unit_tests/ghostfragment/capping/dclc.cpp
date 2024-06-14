/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../test_ghostfragment.hpp"
#include "../testing/are_caps_equal.hpp"
#include <ghostfragment/property_types/fragmenting/capped_fragments.hpp>
#include <ghostfragment/property_types/topology/connectivity_table.hpp>

using the_pt         = ghostfragment::pt::CappedFragments;
using connect_pt     = ghostfragment::pt::ConnectivityTable;
using traits_t       = ghostfragment::pt::CappedFragmentsTraits;
using broken_bonds_t = typename traits_t::broken_bonds_type;
using frags_t        = typename traits_t::result_type;
using nuclei_t       = typename frags_t::value_type;
using nucleus_t      = typename nuclei_t::value_type;
using cap_set_type   = typename frags_t::cap_set_type;

namespace {
// Correct answers for three hydrocarbons -- ethane with two
// fragments, propane with two fragments, and propane with four
// fragments. Answers generated in Mathematica.

// Methane CapSet (1 carbon, 1 frag)

auto methane_dclc_caps() {
    cap_set_type methane;
    return methane;
}

// Ethane CapSets (2 carbon, 2 frags)
auto ethane_dclc_caps() {
    cap_set_type caps;

    nucleus_t c0("H", 1, 1837.289, 1.682281604, 1.188919091, 0);
    caps.emplace_back(0, 1, c0);

    nucleus_t c1("H", 1, 1837.289, 0.677812, 0.479031, 0);
    caps.emplace_back(1, 0, c1);

    return caps;
}

// Propane CapSet (3 carbon, 2 frags)
auto propane_dclc_2_caps() {
    cap_set_type caps;

    nucleus_t c1("H", 1, 1837.289, 0.677812, 0.479031, 0);
    caps.emplace_back(1, 0, c1);

    nucleus_t c0("H", 1, 1837.289, 4.04238, 0.479031, 0);
    caps.emplace_back(1, 2, c0);

    return caps;
}

// Propane CapSet (3 carbon, 4 frags)
auto propane_dclc_3_caps() {
    cap_set_type caps;

    nucleus_t c0("H", 1, 1837.289, 1.68228, 1.18892, 0);
    caps.emplace_back(0, 1, c0);

    nucleus_t c1("H", 1, 1837.289, 0.677812, 0.479031, 0);
    nucleus_t c2("H", 1, 1837.289, 4.04238, 0.479031, 0);
    caps.emplace_back(1, 0, c1);
    caps.emplace_back(1, 2, c2);

    nucleus_t c3("H", 1, 1837.289, 3.03791, 1.18892, 0);
    caps.emplace_back(2, 1, c3);

    return caps;
}

auto make_submod(std::size_t n) {
    return pluginplay::make_lambda<connect_pt>([=](auto&& mol_in) {
        REQUIRE(testing::hydrocarbon(n) == mol_in);
        return testing::hydrocarbon_connectivity(n);
    });
}

} // namespace

TEST_CASE("DCLC Capping") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("DCLC Capping");

    SECTION("Methane (1 carbon 1 frag") {
        auto corr = methane_dclc_caps();
        auto hc   = testing::hydrocarbon_fragmented_nuclei(1, 1);
        broken_bonds_t bonds;
        mod.change_submod("Connectivity", make_submod(1));
        auto caps = mod.run_as<the_pt>(hc, bonds);
        REQUIRE(are_caps_equal(corr, caps.cap_set()));
    }

    SECTION("Ethane (2 carbon 2 frags)") {
        auto corr = ethane_dclc_caps();
        auto hc   = testing::hydrocarbon_fragmented_nuclei(2, 1);
        broken_bonds_t bonds;
        bonds.insert({0, 1});
        bonds.insert({1, 0});
        mod.change_submod("Connectivity", make_submod(2));
        auto caps = mod.run_as<the_pt>(hc, bonds);
        REQUIRE(are_caps_equal(corr, caps.cap_set()));
    }

    SECTION("Propane (3 carbon 2 frags)") {
        auto corr = propane_dclc_2_caps();
        auto hc   = testing::hydrocarbon_fragmented_nuclei(3, 2);
        broken_bonds_t bonds;
        bonds.insert({1, 0});
        bonds.insert({1, 2});
        auto caps = mod.run_as<the_pt>(hc, bonds);
        REQUIRE(are_caps_equal(corr, caps.cap_set()));
    }

    SECTION("Propane (3 carbon 4 frags)") {
        auto corr = propane_dclc_3_caps();
        auto hc   = testing::hydrocarbon_fragmented_nuclei(3, 1);
        broken_bonds_t bonds;
        bonds.insert({0, 1});
        bonds.insert({1, 0});
        bonds.insert({1, 2});
        bonds.insert({2, 1});
        auto caps = mod.run_as<the_pt>(hc, bonds);
        REQUIRE(are_caps_equal(corr, caps.cap_set()));
    }
}
