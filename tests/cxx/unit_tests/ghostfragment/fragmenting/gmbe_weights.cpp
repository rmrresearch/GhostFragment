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
#include <ghostfragment/property_types/fragmenting/fragment_weights.hpp>

using namespace ghostfragment;

using property_type       = pt::FragmentWeights;
using traits_type         = pt::FragmentWeightsTraits;
using fragmented_sys_type = typename traits_type::fragments_type;
using fragmented_mol_type =
  typename fragmented_sys_type::fragmented_molecule_type;
using fragmented_nuclei_type =
  typename fragmented_mol_type::fragmented_nuclei_type;
using nuclei_type      = typename fragmented_nuclei_type::supersystem_type;
using nucleus_type     = typename nuclei_type::value_type;
using weight_container = typename traits_type::weight_container;

namespace {

// Wraps going from fragmented nuclei to fragmented system
auto as_system(fragmented_nuclei_type frags) {
    fragmented_mol_type fragmented_mol(std::move(frags), 0, 1);
    return fragmented_sys_type(std::move(fragmented_mol));
}

} // namespace

/* Testing strategy:
 *
 * We create a system with four water molecules. Assuming each water is a
 * pseudoatom, we then iterate over the  powerset of how to form fragments (no
 * fragments, one giant fragment, two fragments, three
 * fragments, then four fragments). For each level of fragmenting we consider
 * the different ways of partitioning the system e.g., no overlap, one pair-wise
 * overlap. In practice what matters is not the identify of the overlap (e.g.,
 * it doesn't matter if two fragments overlap by 1 or 2 waters) but how many
 * fragments share the overlap.
 */

TEST_CASE("GMBE Weights") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("GMBE Weights");

    auto nuclei_mol = testing::water(4);
    fragmented_nuclei_type frags(nuclei_mol.nuclei().as_nuclei());

    SECTION("No Fragments") {
        weight_container corr;
        auto weights = mod.run_as<property_type>(as_system(frags));
        REQUIRE(weights == corr);
    }

    SECTION("One Fragment") {
        frags.insert({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
        weight_container corr(1, 1.0);
        auto weights = mod.run_as<property_type>(as_system(frags));
        REQUIRE(weights == corr);
    }

    SECTION("Two Fragments") {
        SECTION("Disjoint") {
            frags.insert({0, 1, 2, 3, 4, 5});
            frags.insert({6, 7, 8, 9, 10, 11});
            weight_container corr(2, 1.0);
            auto weights = mod.run_as<property_type>(as_system(frags));
            REQUIRE(weights == corr);
        }
        SECTION("Overlap") {
            frags.insert({0, 1, 2, 3, 4, 5});
            frags.insert({3, 4, 5, 6, 7, 8, 9, 10, 11});
            frags.insert({3, 4, 5});

            weight_container corr{1.0, 1.0, -1.0};
            auto weights = mod.run_as<property_type>(as_system(frags));
        }
    }

    SECTION("Three Fragments") {
        SECTION("Disjoint") {
            frags.insert({0, 1, 2});
            frags.insert({3, 4, 5});
            frags.insert({6, 7, 8, 9, 10, 11});

            weight_container corr{1.0, 1.0, 1.0};

            auto weights = mod.run_as<property_type>(as_system(frags));
            REQUIRE(weights == corr);
        }

        SECTION("One pair-wise overlap") {
            frags.insert({0, 1, 2, 3, 4, 5});
            frags.insert({3, 4, 5, 6, 7, 8});
            frags.insert({9, 10, 11});
            frags.insert({3, 4, 5});

            weight_container corr{1.0, 1.0, 1.0, -1.0};

            auto weights = mod.run_as<property_type>(as_system(frags));
            REQUIRE(weights == corr);
        }

        SECTION("Two pair-wise overlaps") {
            frags.insert({0, 1, 2, 3, 4, 5});
            frags.insert({3, 4, 5, 6, 7, 8});
            frags.insert({6, 7, 8, 9, 10, 11});
            frags.insert({3, 4, 5});
            frags.insert({6, 7, 8});

            weight_container corr{1.0, 1.0, 1.0, -1.0, -1.0};

            auto weights = mod.run_as<property_type>(as_system(frags));
            REQUIRE(weights == corr);
        }

        SECTION("Three pair-wise overlaps") {
            frags.insert({0, 1, 2, 3, 4, 5});
            frags.insert({3, 4, 5, 6, 7, 8});
            frags.insert({0, 1, 2, 6, 7, 8, 9, 10, 11});
            frags.insert({0, 1, 2});
            frags.insert({3, 4, 5});
            frags.insert({6, 7, 8});

            weight_container corr{1.0, 1.0, 1.0, -1.0, -1.0, -1.0};
            auto weights = mod.run_as<property_type>(as_system(frags));
            REQUIRE(weights == corr);
        }

        SECTION("Three pair-wise overlaps and 1 three-way overlap") {
            frags.insert({0, 1, 2, 3, 4, 5, 6, 7, 8});
            frags.insert({0, 1, 2, 3, 4, 5, 9, 10, 11});
            frags.insert({0, 1, 2, 6, 7, 8, 9, 10, 11});
            frags.insert({0, 1, 2, 3, 4, 5});
            frags.insert({0, 1, 2, 6, 7, 8});
            frags.insert({0, 1, 2, 9, 10, 11});
            frags.insert({0, 1, 2});

            weight_container corr{1.0, 1.0, 1.0, -1.0, -1.0, -1.0, 1.0};
            auto weights = mod.run_as<property_type>(as_system(frags));
            REQUIRE(weights == corr);
        }

        SECTION("Three pair-wise overlaps that are the 1 three-way overlap") {
            frags.insert({0, 1, 2, 3, 4, 5});
            frags.insert({0, 1, 2, 6, 7, 8});
            frags.insert({0, 1, 2, 9, 10, 11});
            frags.insert({0, 1, 2});

            weight_container corr{1.0, 1.0, 1.0, -2.0};
            auto weights = mod.run_as<property_type>(as_system(frags));
            REQUIRE(weights == corr);
        }
    }

    SECTION("Four Fragments") {
        SECTION("Disjoint") {
            frags.insert({0, 1, 2});
            frags.insert({3, 4, 5});
            frags.insert({6, 7, 8});
            frags.insert({9, 10, 11});

            weight_container corr{1.0, 1.0, 1.0, 1.0};
            auto weights = mod.run_as<property_type>(as_system(frags));
            REQUIRE(weights == corr);
        }

        SECTION("Non-disjoint") {
            frags.insert({0, 1, 2, 3, 4, 5, 6, 7, 8});
            frags.insert({0, 1, 2, 3, 4, 5, 9, 10, 11});
            frags.insert({0, 1, 2, 6, 7, 8, 9, 10, 11});
            frags.insert({3, 4, 5, 6, 7, 8, 9, 10, 11});
            frags.insert({0, 1, 2, 3, 4, 5});   // 1^2
            frags.insert({0, 1, 2, 6, 7, 8});   // 1^3
            frags.insert({0, 1, 2, 9, 10, 11}); // 2^3
            frags.insert({3, 4, 5, 6, 7, 8});   // 1^4
            frags.insert({3, 4, 5, 9, 10, 11}); // 2^4
            frags.insert({6, 7, 8, 9, 10, 11}); // 3^4
            frags.insert({0, 1, 2});            // 1^2^3
            frags.insert({3, 4, 5});            // 1^2^4
            frags.insert({6, 7, 8});            // 1^3^4
            frags.insert({9, 10, 11});          // 2^3^4

            weight_container corr{1.0,  1.0,  1.0,  1.0, -1.0, -1.0, -1.0,
                                  -1.0, -1.0, -1.0, 1.0, 1.0,  1.0,  1.0};

            auto weights = mod.run_as<property_type>(as_system(frags));
            REQUIRE(weights == corr);
        }
    }
}
