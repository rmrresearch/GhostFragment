#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/charge_multiplicity_assigner.hpp>
#include <ghostfragment/drivers/drivers.hpp>
#include <catch2/catch.hpp>
#include <iostream>

using namespace ghostfragment;
using namespace testing;

using my_pt = pt::ChargeMultiplicityAssigner;
using frag_type = chemist::FragmentedNuclei;
using cap_type = std::vector<chemist::CapSet>;
using atom_type = chemist::Atom;
using mol_type = chemist::Molecule;

using charge_result_type = std::vector<mol_type::charge_type>;
using mult_result_type = std::vector<mol_type::size_type>;

TEST_CASE("Neutral Singlet") {
    auto mm = initialize();
    auto& mod = mm.at("Neutral Singlet");

    SECTION("Empty Molecule") {
        mol_type mol;
        frag_type frags(mol.nuclei());
        cap_type caps;

        charge_result_type charge_corr;
        mult_result_type mult_corr;

        const auto& [charge_test, mult_test] = mod.run_as<my_pt>(frags, caps, mol);

        REQUIRE(charge_test == charge_corr);
        REQUIRE(mult_test == mult_corr);
    }

    SECTION("Two fragments") {
        atom_type C1("C", 6ul, 12.0, 0.0, 0.0, 0.0);
        atom_type C2("C", 6ul, 12.0, 1.0, 0.0, 0.0);
        atom_type C3("C", 6ul, 12.0, 2.0, 0.0, 0.0);
        mol_type mol({C1, C2, C3});
        frag_type frags(mol.nuclei());
        frags.add_fragment({0, 1});
        frags.add_fragment({1, 2});

        SECTION("No caps") {
            cap_type caps(frags.size(), chemist::CapSet{});

            charge_result_type charge_corr(frags.size(), 0);
            mult_result_type mult_corr(frags.size(), 1);

            const auto& [charge_test, mult_test] = mod.run_as<my_pt>(frags, caps, mol);

            REQUIRE(charge_test == charge_corr);
            REQUIRE(mult_test == mult_corr);
        }

        SECTION("Two caps") {
            atom_type Cap1("C", 6ul, 12.0, 1.5, 0.0, 0.0);
            atom_type Cap2("C", 6ul, 12.0, 0.5, 0.0, 0.0);

            cap_type caps;

            chemist::CapSet cap_set1;
            cap_set1.add_cap(1, 2, Cap1);
            caps.push_back(cap_set1);

            chemist::CapSet cap_set2;
            cap_set2.add_cap(1, 0, Cap2);
            caps.push_back(cap_set2);

            charge_result_type charge_corr(frags.size(), 0);
            mult_result_type mult_corr(frags.size(), 1);

            const auto& [charge_test, mult_test] = mod.run_as<my_pt>(frags, caps, mol);

            REQUIRE(charge_test == charge_corr);
            REQUIRE(mult_test == mult_corr);
        }
    }

    SECTION("Odd number of elections") {
        atom_type H1("H", 1ul, 2.0, -1.0, 0.0, 0.0);
        atom_type C1("C", 6ul, 12.0, 0.0, 0.0, 0.0);
        atom_type C2("C", 6ul, 12.0, 1.0, 0.0, 0.0);
        atom_type C3("C", 6ul, 12.0, 2.0, 0.0, 0.0);
        atom_type H2("H", 1ul, 2.0, 3.0, 0.0, 0.0);
        mol_type mol({H1, C1, C2, C3, H2});
        frag_type frags(mol.nuclei());
        frags.add_fragment({0, 1, 2});
        frags.add_fragment({2, 3, 4});

        SECTION("No caps") {
            cap_type caps;
            for(auto i = 0; i < frags.size(); i++) {
                chemist::CapSet cap_set;
                chemist::Cap c;
                cap_set.push_back(c);
                caps.push_back(cap_set);
            }
            
            REQUIRE_THROWS_AS(mod.run_as<my_pt>(frags, caps, mol), std::runtime_error);
        }

        SECTION("Two caps") {
            atom_type Cap1("C", 6ul, 12.0, 1.5, 0.0, 0.0);
            atom_type Cap2("C", 6ul, 12.0, 0.5, 0.0, 0.0);

            cap_type caps;

            chemist::CapSet cap_set1;
            cap_set1.add_cap(2, 3, Cap1);
            caps.push_back(cap_set1);

            chemist::CapSet cap_set2;
            cap_set2.add_cap(2, 1, Cap2);
            caps.push_back(cap_set2);

            REQUIRE_THROWS_AS(mod.run_as<my_pt>(frags, caps, mol), std::runtime_error);
        }
    }
}
