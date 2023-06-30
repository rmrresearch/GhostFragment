#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/charge_assigner.hpp>
#include <ghostfragment/drivers/drivers.hpp>
#include <catch2/catch.hpp>
#include <iostream>

using namespace ghostfragment;
using namespace testing;

using my_pt = pt::ChargeAssigner;
using frag_type = chemist::FragmentedNuclei;
using cap_type = std::vector<chemist::CapSet>;
using atom_type = chemist::Atom;
using mol_type = chemist::Molecule;

using result_type = std::vector<mol_type::charge_type>;

TEST_CASE("Neutral Charge") {
    auto mm = initialize();
    auto& mod = mm.at("Neutral Charge");

    SECTION("Empty Molecule") {
        mol_type mol;
        frag_type frags(mol.nuclei());
        cap_type caps;

        result_type corr;

        const auto& test = mod.run_as<my_pt>(frags, caps, mol);

        REQUIRE(test == corr);
    }

    SECTION("Two fragments") {
        atom_type C1("C", 6ul, 12.0, 0.0, 0.0, 0.0);
        atom_type C2("C", 6ul, 12.0, 1.0, 0.0, 0.0);
        atom_type C3("C", 6ul, 12.0, 1.0, 0.0, 0.0);
        mol_type mol({C1, C2, C3});
        frag_type frags(mol.nuclei());
        frags.add_fragment({0, 1});
        frags.add_fragment({1, 2});

        SECTION("No caps") {
            cap_type caps;
            for(auto i = 0; i < frags.size(); i++) {
                chemist::CapSet cap_set;
                chemist::Cap c;
                cap_set.push_back(c);
                caps.push_back(cap_set);
            }

            result_type corr;
            corr.push_back(0);
            corr.push_back(0);

            const auto& test = mod.run_as<my_pt>(frags, caps, mol);

            REQUIRE(test == corr);
        }

        SECTION("Two caps") {
            atom_type Cap1("C", 6ul, 12.0, 0.5, 0.0, 0.0);
            atom_type Cap2("C", 6ul, 12.0, 0.5, 0.0, 0.0);

            cap_type caps;

            chemist::CapSet cap_set1;
            cap_set1.add_cap(1, 2, Cap1);
            caps.push_back(cap_set1);

            chemist::CapSet cap_set2;
            cap_set2.add_cap(1, 0, Cap2);
            caps.push_back(cap_set2);

            result_type corr;
            corr.push_back(0);
            corr.push_back(0);

            const auto& test = mod.run_as<my_pt>(frags, caps, mol);

            REQUIRE(test == corr);
        }
        
    }
}
