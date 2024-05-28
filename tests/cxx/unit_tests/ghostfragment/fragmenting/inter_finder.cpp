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
#include <ghostfragment/fragmenting/inter_finder.hpp>
// #include <iostream>

using namespace ghostfragment::fragmenting;

using traits_type    = IntersectionTraits;
using fragments_type = typename traits_type::input_type;
using nuclei_type    = typename fragments_type::supersystem_type;
using nucleus_type   = typename nuclei_type::value_type;

TEST_CASE("Intersection Finder") {
    nuclei_type nuclei;

    for(auto i = 0; i < 8; ++i) {
        nuclei.push_back(nucleus_type("H", 1ul, 1.0, i, 0.0, 0.0));
    }

    fragments_type fragmented_nuclei(nuclei);

    SECTION("No Fragments") {
        fragments_type corr(nuclei);
        REQUIRE(intersections(fragmented_nuclei) == corr);
    }

    SECTION("One Fragment") {
        fragmented_nuclei.insert({0, 1, 2, 3, 4, 5, 6, 7});
        fragments_type corr(fragmented_nuclei);
        REQUIRE(intersections(fragmented_nuclei) == corr);
    }

    SECTION("Two Fragments") {
        SECTION("Disjoint") {
            fragmented_nuclei.insert({0, 1, 2, 3});
            fragmented_nuclei.insert({4, 5, 6, 7});

            fragments_type corr(fragmented_nuclei);

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }

        SECTION("Overlap") {
            fragmented_nuclei.insert({0, 1, 2, 3, 4});
            fragmented_nuclei.insert({4, 5, 6, 7});

            fragments_type corr(fragmented_nuclei);
            corr.insert({4});

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }
    }

    SECTION("Three Fragments") {
        SECTION("Disjoint") {
            fragmented_nuclei.insert({0, 1, 2});
            fragmented_nuclei.insert({3, 4, 5});
            fragmented_nuclei.insert({6, 7});

            fragments_type corr(fragmented_nuclei);

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }

        SECTION("One Overlap") {
            fragmented_nuclei.insert({0, 1, 2});
            fragmented_nuclei.insert({2, 3, 4});
            fragmented_nuclei.insert({5, 6, 7});

            fragments_type corr(fragmented_nuclei);
            corr.insert({2});

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }

        SECTION("Two Overlaps") {
            fragmented_nuclei.insert({0, 1, 2});
            fragmented_nuclei.insert({2, 3, 4});
            fragmented_nuclei.insert({4, 5, 6, 7});

            fragments_type corr(fragmented_nuclei);
            corr.insert({2});
            corr.insert({4});

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }

        SECTION("Three Overlaps") {
            fragmented_nuclei.insert({0, 1, 2, 3});
            fragmented_nuclei.insert({2, 3, 4, 5});
            fragmented_nuclei.insert({3, 4, 5, 6});

            fragments_type corr(fragmented_nuclei);
            corr.insert({2, 3});
            corr.insert({3});
            corr.insert({3, 4, 5});

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }
    }

    SECTION("Four Fragments") {
        SECTION("Disjoint") {
            fragmented_nuclei.insert({0, 1});
            fragmented_nuclei.insert({2, 3});
            fragmented_nuclei.insert({4, 5});
            fragmented_nuclei.insert({6, 7});

            fragments_type corr(fragmented_nuclei);

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }

        SECTION("One Overlap") {
            fragmented_nuclei.insert({0, 1, 2});
            fragmented_nuclei.insert({2, 3});
            fragmented_nuclei.insert({4, 5});
            fragmented_nuclei.insert({6, 7});

            fragments_type corr(fragmented_nuclei);
            corr.insert({2});

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }

        SECTION("Two Overlaps") {
            fragmented_nuclei.insert({0, 1, 2});
            fragmented_nuclei.insert({2, 3});
            fragmented_nuclei.insert({4, 5, 6});
            fragmented_nuclei.insert({6, 7});

            fragments_type corr(fragmented_nuclei);
            corr.insert({2});
            corr.insert({6});

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }

        SECTION("Three Overlaps") {
            fragmented_nuclei.insert({0, 1, 2});
            fragmented_nuclei.insert({2, 3, 4});
            fragmented_nuclei.insert({2, 4, 5, 6});
            fragmented_nuclei.insert({6, 7});

            fragments_type corr(fragmented_nuclei);
            corr.insert({2});
            corr.insert({2, 4});
            corr.insert({6});

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }

        SECTION("Four Overlaps") {
            fragmented_nuclei.insert({0, 1, 2, 3});
            fragmented_nuclei.insert({2, 3, 4});
            fragmented_nuclei.insert({2, 4, 5, 6});
            fragmented_nuclei.insert({2, 6, 7});

            fragments_type corr(fragmented_nuclei);
            corr.insert({2});
            corr.insert({2, 3});
            corr.insert({2, 4});
            corr.insert({2, 6});

            REQUIRE(intersections(fragmented_nuclei) == corr);
        }
    }
}
