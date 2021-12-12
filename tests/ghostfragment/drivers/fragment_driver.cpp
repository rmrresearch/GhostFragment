#include "../test_ghostfragment.hpp"

using namespace ghostfragment;
using namespace testing;

using frags_pt       = simde::FragmentedMolecule;
using graph_pt       = pt::MolecularGraph;
using graph2frags_pt = pt::MolecularGraphToFragments;

using frags_type = type::fragmented_molecule;

TEST_CASE("Fragment Driver") {
    auto mm   = initialize();
    auto& mod = mm.at("Fragment Driver");

    SECTION("One molecule") {
        auto mol = water(1);

        // TODO: Need to unwrap the pseduatoms in the graph2frags mod
        const auto& [frags] = mod.run_as<frags_pt>(mol);
        frags_type corr(mol, {{0, 1, 2}});
        REQUIRE(corr == frags);
    }
}