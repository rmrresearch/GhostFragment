#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/multiplicity_assigner.hpp>
#include <ghostfragment/drivers/drivers.hpp>
#include <catch2/catch.hpp>

using namespace ghostfragment;
using namespace testing;

using my_pt = pt::MultiplicityAssigner;
using frag_type = chemist::FragmentedNuclei;
using cap_type = std::vector<chemist::CapSet>;
using atom_type = chemist::Atom;
using mol_type = chemist::Molecule;

using result_type = std::vector<mol_type::size_type>;

TEST_CASE("Single Multiplicity") {
    auto mm = initialize();
    auto& mod = mm.at("Single Multiplicity");

    SECTION("Empty Molecule") {
        mol_type mol;
        frag_type frags(mol.nuclei());
        cap_type caps;

        result_type corr;

        const auto& test = mod.run_as<my_pt>(frags, caps, mol);

        REQUIRE(test == corr);
    }

    SECTION("Two fragments") {
        
    }
}