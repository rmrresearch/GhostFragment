#include "../test_ghostfragment.hpp"
#include "DCLC.hpp"
#include <ghostfragment/property_types/connectivity_table.hpp>
#include <hydrocarbon/hydrocarbon_fragment.hpp>

TEST_CASE("DCLC Capping") {

    using namespace ghostfragment;
    using namespace testing;

    using the_pt      = pt::DCLC;
    using input_type  = chemist::FragmentedNuclei;
    using result_type = chemist::CapSet;

    auto mm   = initialize();
    auto& mod = mm.at("DCLC Capping");

    SECTION("Ethane (2 carbon 2 frags)") {
        chemist::Molecule corr(Ethane2());
        input_type hc{hydrocarbon_fragmented_nuclei(2,1)};
        result_type caps = mod.run_as<the_pt>(hc);
        chemist::Molecule test;
        for(const auto& cap_i :: caps){
            for(i = 0; i < cap_i.size(); ++i){
                test.push_back(atom_type cap_i.cap_atom(i));
            }
        }
        REQUIRE(AreMoleculesEqual(corr, test));
    }

    SECTION("Propane (3 carbon 2 frags)") {
        chemist::Molecule corr(Propane2());
        input_type hc{hydrocarbon_fragmented_nuclei(3,2)};
        result_type caps = mod.run_as<the_pt>(hc);
        chemist::Molecule test;
        for(const auto& cap_i :: caps){
            for(i = 0; i < cap_i.size(); ++i){
                test.push_back(atom_type cap_i.cap_atom(i));
            }
        }
        REQUIRE(AreMoleculesEqual(corr, test));
    }

    SECTION("Propane (3 carbon 4 frags)") {
        chemist::Molecule corr(Propane4());
        input_type hc{hydrocarbon_fragmented_nuclei(3,1)};
        result_type caps = mod.run_as<the_pt>(hc);
        chemist::Molecule test;
        for(const auto& cap_i :: caps){
            for(i = 0; i < cap_i.size(); ++i){
                test.push_back(atom_type cap_i.cap_atom(i));
            }
        }
        REQUIRE(AreMoleculesEqual(corr, test));
    }
}
