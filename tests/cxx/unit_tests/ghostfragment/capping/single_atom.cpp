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
#include <ghostfragment/property_types/fragmenting/capped_fragments.hpp>

using namespace ghostfragment;
using namespace testing;

using the_pt            = pt::CappedFragments;
using frags_type        = typename pt::CappedFragmentsTraits::frags_type;
using broken_bonds_type = typename pt::CappedFragmentsTraits::broken_bonds_type;
using size_type         = std::size_t;
using nucleus_type      = typename frags_type::value_type::value_type;
using cap_type          = typename frags_type::cap_set_type::value_type;

inline auto caps_methane_one() {
    frags_type rv = hydrocarbon_fragmented_nuclei(1, 1);
    return rv;
}

inline auto caps_ethane_one() {
    auto rv = hydrocarbon_fragmented_nuclei(2, 1);
    nucleus_type c0("H", 1ul, 1837.289, 2.360094094, 1.667949599, 0.0);
    nucleus_type c1("H", 1ul, 1837.289, 0.0, 0.0, 0.0);
    rv.add_cap(cap_type(0, 1, c0));
    rv.add_cap(cap_type(1, 0, c1));
    return rv;
}

inline auto caps_propane_one() {
    auto rv = hydrocarbon_fragmented_nuclei(3, 1);
    nucleus_type c0("H", 1ul, 1837.289, 2.360094094, 1.667949599, 0.0);
    nucleus_type c1("H", 1ul, 1837.289, 0.0, 0.0, 0.0);
    nucleus_type c2("H", 1ul, 1837.289, 4.720188189, 0.0, 0.0);
    nucleus_type c3("H", 1ul, 1837.289, 2.360094094, 1.667949599, 0.0);
    rv.add_cap(cap_type(0, 1, c0));
    rv.add_cap(cap_type(1, 0, c1));
    rv.add_cap(cap_type(1, 2, c2));
    rv.add_cap(cap_type(2, 1, c3));
    return rv;
}

inline auto caps_propane_two() {
    auto rv = hydrocarbon_fragmented_nuclei(3, 2);
    nucleus_type c0("H", 1ul, 1837.289, 4.720188189, 0.0, 0.0);
    nucleus_type c1("H", 1ul, 1837.289, 0.0, 0.0, 0.0);
    rv.add_cap(cap_type(1, 0, c1));
    rv.add_cap(cap_type(1, 2, c0));
    return rv;
}

TEST_CASE("SingleAtom") {
    auto mm   = initialize();
    auto& mod = mm.at("Atomic Capping");

    SECTION("Water monomers") {
        for(size_type n_waters = 1; n_waters < 4; ++n_waters) {
            SECTION("N = " + std::to_string(n_waters)) {
                auto water_n = water_fragmented_nuclei(n_waters);
                broken_bonds_type bonds;

                const auto& rv = mod.run_as<the_pt>(water_n, bonds);
                REQUIRE(rv == water_n);
            }
        }
    }

    SECTION("Hydrocarbon monomers") {
        SECTION("Methane fragment (size 1)") {
            auto corr = caps_methane_one();
            auto hc   = hydrocarbon_fragmented_nuclei(1, 1);
            broken_bonds_type bonds;
            auto test = mod.run_as<the_pt>(hc, bonds);
            REQUIRE(are_caps_equal(corr.cap_set(), test.cap_set()));
        }

        SECTION("Ethane fragment (size 1)") {
            auto corr = caps_ethane_one();
            auto hc   = hydrocarbon_fragmented_nuclei(2, 1);
            broken_bonds_type bonds;
            bonds.insert({0, 1});
            bonds.insert({1, 0});
            auto test = mod.run_as<the_pt>(hc, bonds);
            REQUIRE(are_caps_equal(corr.cap_set(), test.cap_set()));
        }

        SECTION("Propane fragment (size 1)") {
            auto corr = caps_propane_one();
            auto hc   = hydrocarbon_fragmented_nuclei(3, 1);
            broken_bonds_type bonds;
            bonds.insert({0, 1});
            bonds.insert({1, 0});
            bonds.insert({1, 2});
            bonds.insert({2, 1});
            auto test = mod.run_as<the_pt>(hc, bonds);
            REQUIRE(are_caps_equal(corr.cap_set(), test.cap_set()));
        }

        SECTION("Propane fragment (size 2)") {
            auto corr = caps_propane_two();
            auto hc   = hydrocarbon_fragmented_nuclei(3, 2);
            broken_bonds_type bonds;
            bonds.insert({1, 2});
            bonds.insert({1, 0});
            auto test = mod.run_as<the_pt>(hc, bonds);
            REQUIRE(are_caps_equal(corr.cap_set(), test.cap_set()));
        }
    }
}
