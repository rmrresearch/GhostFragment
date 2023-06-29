#include "../test_ghostfragment.hpp"
#include "hydrocarbon/hydrocarbon.h"
#include <ghostfragment/property_types/fragmented_nuclei.hpp>

using namespace ghostfragment;
using namespace testing;

using frags_pt       = pt::FragmentedNuclei;
using graph_pt       = pt::MolecularGraph;
using graph2frags_pt = pt::MolecularGraphToFragments;

using frags_type = chemist::FragmentedNuclei;
using graph_type = MolecularGraph;
using conns_type = graph_type::connectivity_type;
using mol_type   = chemist::Molecule;

/* Testing strategy:
 *
 * Testing is done using the default modules (Heavy Atom for pseudoatom generation,
 * Bond-Based for fragmentation). 
 */

TEST_CASE("Fragment Driver") {
    auto mm   = initialize();
    auto& mod = mm.at("Fragment Driver");

    SECTION("Empty Molecule") {
        chemist::Molecule mol;
        frags_type corr(mol.nuclei());
        const auto& rv = mod.run_as<frags_pt>(mol.nuclei());
        REQUIRE(corr == rv);
    }

    SECTION("Single Atom") {
        chemist::Molecule mol;
        mol.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
        frags_type corr(mol.nuclei());
        corr.add_fragment({0});
        const auto& rv = mod.run_as<frags_pt>(mol.nuclei());
        REQUIRE(corr == rv);
    }

    SECTION("Methane") {
        auto methane = hydrocarbon(1);
        frags_type corr(methane.nuclei());
        corr.add_fragment({0, 1, 2, 3, 4});
        const auto& rv = mod.run_as<frags_pt>(methane.nuclei());
        REQUIRE(corr == rv);
    }

    SECTION("Ethane") {
        auto ethane = hydrocarbon(2);
        frags_type corr(ethane.nuclei());
        corr.add_fragment({0, 2, 3, 4});
        corr.add_fragment({1, 5, 6, 7});
        const auto& rv = mod.run_as<frags_pt>(ethane.nuclei());
        REQUIRE(corr == rv);
    }
}