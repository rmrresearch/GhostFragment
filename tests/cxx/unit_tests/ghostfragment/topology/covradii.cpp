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
#include <ghostfragment/property_types/topology/connectivity_table.hpp>
#include <ghostfragment/topology/covalent_radius.hpp>
#include <ghostfragment/topology/topology.hpp>

using namespace ghostfragment;

TEST_CASE("CovRadii Module") {
    using property_type = pt::ConnectivityTable;
    using molecule_type = pt::ConnectivityTableTraits::input_type;
    using atom_type     = typename molecule_type::atom_type;
    using ct_type       = pt::ConnectivityTableTraits::result_type;

    auto mm   = testing::initialize();
    auto& mod = mm.at("Covalent Radius");

    const auto sigma_h = topology::covalent_radius(1);
    const atom_type h0("H", 1ul, 1837.289, 0.0, 0.0, 0.0);

    SECTION("Default tau") {
        SECTION("Two H atoms") {
            SECTION("Less than tau * sigma") {
                atom_type h1(h0);
                h1.z() = 0.9 * (sigma_h + sigma_h);
                molecule_type h2{h0, h1};

                auto ct = mod.run_as<property_type>(h2);
                ct_type corr(2);
                corr.add_bond(0, 1);
                REQUIRE(ct == corr);
            }

            SECTION("At tau * sigma") {
                atom_type h1(h0);
                h1.z() = 1.1 * (sigma_h + sigma_h);
                molecule_type h2{h0, h1};

                auto ct = mod.run_as<property_type>(h2);
                ct_type corr(2);
                corr.add_bond(0, 1);
                REQUIRE(ct == corr);
            }

            SECTION("Longer than tau * sigma") {
                atom_type h1(h0);
                h1.z() = 2.0 * (sigma_h + sigma_h);
                molecule_type h2{h0, h1};

                auto ct = mod.run_as<property_type>(h2);
                ct_type corr(2);
                REQUIRE(ct == corr);
            }
        }
    }

    SECTION("Non-default tau") {
        mod.change_input("tau", 1.0);
        SECTION("Two H atoms") {
            SECTION("Less than tau * sigma") {
                atom_type h1(h0);
                h1.z() = 0.9 * (sigma_h + sigma_h);
                molecule_type h2{h0, h1};

                auto ct = mod.run_as<property_type>(h2);
                ct_type corr(2);
                corr.add_bond(0, 1);
                REQUIRE(ct == corr);
            }

            SECTION("At tau * sigma") {
                atom_type h1(h0);
                h1.z() = 2.0 * (sigma_h + sigma_h);
                molecule_type h2{h0, h1};

                auto ct = mod.run_as<property_type>(h2);
                ct_type corr(2);
                corr.add_bond(0, 1);
                REQUIRE(ct == corr);
            }

            SECTION("Longer than tau * sigma") {
                atom_type h1(h0);
                h1.z() = 3.0 * (sigma_h + sigma_h);
                molecule_type h2{h0, h1};

                auto ct = mod.run_as<property_type>(h2);
                ct_type corr(2);
                REQUIRE(ct == corr);
            }
        }
    }

    SECTION("Water monomer") {
        auto h2o = testing::water(1);
        auto ct  = mod.run_as<property_type>(h2o);

        ct_type corr(3);
        corr.add_bond(0, 1);
        corr.add_bond(0, 2);
        REQUIRE(ct == corr);
    }

    SECTION("Water dimer") {
        auto h2o2 = testing::water(2);
        auto ct   = mod.run_as<property_type>(h2o2);

        ct_type corr(6);
        corr.add_bond(0, 1);
        corr.add_bond(0, 2);
        corr.add_bond(3, 4);
        corr.add_bond(3, 5);

        REQUIRE(ct == corr);
    }
}
