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
#include <catch2/catch.hpp>
#include <ghostfragment/property_types/topology/broken_bonds.hpp>

using traits_type = ghostfragment::pt::BrokenBondsTraits;
using input_type  = typename traits_type::fragments_type;
using size_type   = typename traits_type::size_type;
using bond_type   = typename traits_type::bond_type;
using result_type = typename traits_type::result_type;

namespace testing {

// Broken bonds of an ethane molecule with fragment size 1
inline auto bonds_methane_one() { return result_type{}; }

// Broken bonds of an ethane molecule with fragments of size 1
inline auto bonds_ethane_one() {
    result_type bonds;
    bonds.insert(bond_type(0, 1));
    bonds.insert(bond_type(1, 0));
    return bonds;
}

inline auto bonds_propane_one() {
    result_type bonds;
    bonds.insert(bond_type(0, 1));
    bonds.insert(bond_type(1, 0));
    bonds.insert(bond_type(1, 2));
    bonds.insert(bond_type(2, 1));
    return bonds;
}

inline auto bonds_propane_two() {
    result_type bonds;
    bonds.insert(bond_type(1, 2));
    bonds.insert(bond_type(1, 0));
    return bonds;
}

} // namespace testing

using namespace testing;

TEST_CASE("Broken Bonds") {
    using pt = ghostfragment::pt::BrokenBonds;

    auto mm   = testing::initialize();
    auto& mod = mm.at("Broken Bonds");

    SECTION("Methane fragment (size 1)") {
        auto corr        = bonds_methane_one();
        auto hc          = hydrocarbon_fragmented_nuclei(1, 1);
        auto conns       = hydrocarbon_connectivity(1);
        result_type test = mod.run_as<pt>(hc, conns);
        REQUIRE(corr == test);
    }

    SECTION("Ethane fragment (size 1)") {
        auto corr        = bonds_ethane_one();
        auto hc          = hydrocarbon_fragmented_nuclei(2, 1);
        auto conns       = hydrocarbon_connectivity(2);
        result_type test = mod.run_as<pt>(hc, conns);
        REQUIRE(corr == test);
    }

    SECTION("Propane fragment (size 1)") {
        auto corr        = bonds_propane_one();
        auto hc          = hydrocarbon_fragmented_nuclei(3, 1);
        auto conns       = hydrocarbon_connectivity(3);
        result_type test = mod.run_as<pt>(hc, conns);
        REQUIRE(corr == test);
    }

    SECTION("Propane fragment (size 2)") {
        auto corr        = bonds_propane_two();
        auto hc          = hydrocarbon_fragmented_nuclei(3, 2);
        auto conns       = hydrocarbon_connectivity(3);
        result_type test = mod.run_as<pt>(hc, conns);
        REQUIRE(corr == test);
    }
}
