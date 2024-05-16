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
        corr_type corr(water(0).nuclei());
        REQUIRE(water_fragmented_nuclei(0) == corr);
    }

    SECTION("One Water") {
        corr_type corr(water(1).nuclei());
        corr.insert({0, 1, 2});
        REQUIRE(water_fragmented_nuclei(1) == corr);
    }

    SECTION("Two Waters") {
        corr_type corr(water(2).nuclei());
        corr.insert({0, 1, 2});
        corr.insert({3, 4, 5});
        REQUIRE(water_fragmented_nuclei(2) == corr);
    }

    SECTION("Three Waters") {
        corr_type corr(water(3).nuclei());
        corr.insert({0, 1, 2});
        corr.insert({3, 4, 5});
        corr.insert({6, 7, 8});
        REQUIRE(water_fragmented_nuclei(3) == corr);
    }
}
