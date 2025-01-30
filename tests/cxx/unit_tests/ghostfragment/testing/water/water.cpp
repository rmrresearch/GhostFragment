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

#include "water.hpp"
#include <catch2/catch.hpp>

using namespace testing;

/* Unit tests our function for creating water "clusters". We simply test it
 * against the correct hard-coded answers for up to a tetramer. It's assumed
 * that if it works that much, it'll keep working...
 */

TEST_CASE("water") {
    using molecule_type = chemist::Molecule;
    using atom_type     = typename molecule_type::atom_type;
    const unsigned long OZ{8}, HZ{1};
    const double Om{16.0}, Hm{1.0};
    const double Ox{0.00000000000000}, Oy{-0.07579039945857};
    const double Hx{0.86681456860648}, Hy{0.60144316994806};

    SECTION("Zero waters") {
        molecule_type corr;
        REQUIRE(corr == water(0));
    }

    SECTION("One water") {
        molecule_type corr;
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 0.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 0.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 0.0});
        REQUIRE(corr == water(1));
    }

    SECTION("Two waters") {
        molecule_type corr;
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 0.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 0.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 0.0});
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 3.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 3.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 3.0});
        REQUIRE(corr == water(2));
    }

    SECTION("Three waters") {
        molecule_type corr;
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 0.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 0.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 0.0});
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 3.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 3.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 3.0});
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 6.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 6.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 6.0});
        REQUIRE(corr == water(3));
    }

    SECTION("Four waters") {
        molecule_type corr;
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 0.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 0.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 0.0});
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 3.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 3.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 3.0});
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 6.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 6.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 6.0});
        corr.push_back(atom_type{"O", OZ, Om, Ox, Oy, 9.0});
        corr.push_back(atom_type{"H", HZ, Hm, Hx, Hy, 9.0});
        corr.push_back(atom_type{"H", HZ, Hm, -Hx, Hy, 9.0});
        REQUIRE(corr == water(4));
    }
}

TEST_CASE("water_fragmented_nuclei") {
    using corr_type = decltype(water_fragmented_nuclei(0));

    SECTION("Zero Waters") {
        corr_type corr(water(0).nuclei().as_nuclei());
        REQUIRE(water_fragmented_nuclei(0) == corr);
    }

    SECTION("One Water") {
        corr_type corr(water(1).nuclei().as_nuclei());
        corr.insert({0, 1, 2});
        REQUIRE(water_fragmented_nuclei(1) == corr);
    }

    SECTION("Two Waters") {
        corr_type corr(water(2).nuclei().as_nuclei());
        corr.insert({0, 1, 2});
        corr.insert({3, 4, 5});
        REQUIRE(water_fragmented_nuclei(2) == corr);
    }

    SECTION("Three Waters") {
        corr_type corr(water(3).nuclei().as_nuclei());
        corr.insert({0, 1, 2});
        corr.insert({3, 4, 5});
        corr.insert({6, 7, 8});
        REQUIRE(water_fragmented_nuclei(3) == corr);
    }
}

// /* For unit testing we test against the hard-coded answers for 0, 1, 2, and 3
//  * water molecules. It's assumed that it if it works for those scenarios
//  it'll
//  * work for any other scenario as well.
//  */

TEST_CASE("water_connectivity") {
    using ctable_type = chemist::topology::ConnectivityTable;

    SECTION("Zero waters") {
        ctable_type corr(0);
        REQUIRE(corr == water_connectivity(0));
    }

    SECTION("One water") {
        ctable_type corr(3);
        corr.add_bond(0, 1);
        corr.add_bond(0, 2);
        REQUIRE(corr == water_connectivity(1));
    }

    SECTION("Two waters") {
        ctable_type corr(6);
        corr.add_bond(0, 1);
        corr.add_bond(0, 2);
        corr.add_bond(3, 4);
        corr.add_bond(3, 5);
        REQUIRE(corr == water_connectivity(2));
    }

    SECTION("Three waters") {
        ctable_type corr(9);
        corr.add_bond(0, 1);
        corr.add_bond(0, 2);
        corr.add_bond(3, 4);
        corr.add_bond(3, 5);
        corr.add_bond(6, 7);
        corr.add_bond(6, 8);
        REQUIRE(corr == water_connectivity(3));
    }
}
