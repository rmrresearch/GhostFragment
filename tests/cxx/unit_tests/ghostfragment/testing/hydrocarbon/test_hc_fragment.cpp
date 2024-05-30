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

#include "hydrocarbon.hpp"
#include <catch2/catch.hpp>
#include <chemist/fragmenting/fragmented_nuclei.hpp>

using frags_type = chemist::fragmenting::FragmentedNuclei<chemist::Nuclei>;
using namespace testing;

namespace {
// Methane Molecule with fragment size 1
inline auto frag_methane_one() {
    auto hc = hydrocarbon(1);
    frags_type frags(hc.nuclei());
    frags.insert({0, 1, 2, 3, 4});
    return frags;
}
// Ethane Molecule with fragments size 1
inline auto frag_ethane_one() {
    auto hc = hydrocarbon(2);
    frags_type frags(hc.nuclei());
    frags.insert({0, 2, 3, 4});
    frags.insert({1, 5, 6, 7});
    return frags;
}

inline auto frag_propane_one() {
    auto hc = hydrocarbon(3);
    frags_type frags(hc.nuclei());
    frags.insert({0, 3, 4, 5});
    frags.insert({1, 6, 7});
    frags.insert({2, 8, 9, 10});
    return frags;
}

inline auto frag_propane_two() {
    auto hc = hydrocarbon(3);
    frags_type frags(hc.nuclei());
    frags.insert({0, 3, 4, 5, 1, 6, 7});
    frags.insert({1, 6, 7, 2, 8, 9, 10});
    return frags;
}

} // namespace

TEST_CASE("Hydrocarbon Fragment") {
    SECTION("Methane fragment (size 1)") {
        auto corr = frag_methane_one();
        REQUIRE(corr == hydrocarbon_fragmented_nuclei(1, 1));
    }
    SECTION("Ethane fragment (size 1)") {
        auto corr = frag_ethane_one();
        REQUIRE(corr == hydrocarbon_fragmented_nuclei(2, 1));
    }

    SECTION("Propane fragment (size 1)") {
        auto corr = frag_propane_one();
        REQUIRE(corr == hydrocarbon_fragmented_nuclei(3, 1));
    }

    SECTION("Propane fragment (size 2)") {
        auto corr = frag_propane_two();
        REQUIRE(corr == hydrocarbon_fragmented_nuclei(3, 2));
    }
}

TEST_CASE("Hydrocarbon Connectivity") {
    using conns_type = chemist::topology::ConnectivityTable;
    SECTION("Methane") {
        conns_type conns(5);
        conns.add_bond(0, 1);
        conns.add_bond(0, 2);
        conns.add_bond(0, 3);
        conns.add_bond(0, 4);
        REQUIRE(conns == hydrocarbon_connectivity(1));
    }

    SECTION("Ethane") {
        conns_type conns(8);
        conns.add_bond(0, 1);
        conns.add_bond(0, 2);
        conns.add_bond(0, 3);
        conns.add_bond(0, 4);
        conns.add_bond(1, 5);
        conns.add_bond(1, 6);
        conns.add_bond(1, 7);
        REQUIRE(conns == hydrocarbon_connectivity(2));
    }

    SECTION("Propane") {
        conns_type conns(11);
        conns.add_bond(0, 1);
        conns.add_bond(0, 3);
        conns.add_bond(0, 4);
        conns.add_bond(0, 5);
        conns.add_bond(1, 2);
        conns.add_bond(1, 6);
        conns.add_bond(1, 7);
        conns.add_bond(2, 8);
        conns.add_bond(2, 9);
        conns.add_bond(2, 10);
        REQUIRE(conns == hydrocarbon_connectivity(3));
    }
}
