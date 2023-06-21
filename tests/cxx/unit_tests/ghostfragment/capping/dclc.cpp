#include "../test_ghostfragment.hpp"
#include "dclc.hpp"
#include <ghostfragment/property_types/connectivity_table.hpp>
#include <hydrocarbon/hydrocarbon_fragment.hpp>

TEST_CASE("DCLC Capping") {

    using namespace ghostfragment;
    using namespace testing;

    using the_pt       = pt::Capped;
    using input_type   = chemist::FragmentedNuclei;
    using result_type  = std::vector<chemist::CapSet>;
    using conn_pt      = ghostfragment::ConnectivityTable;

    auto mm        = initialize();
    auto& mod      = mm.at("DCLC Capping");

    SECTION("Ethane (2 carbon 2 frags)") {
        result_type corr(ethane_dclc_caps());
        input_type hc{hydrocarbon_fragmented_nuclei(2,1)};
        // mod.change_submod("Connectivity", "Covalent Radius");
        result_type caps = mod.run_as<the_pt>(hc);
        REQUIRE(AreCapsEqual(corr, caps));
    }

    SECTION("Propane (3 carbon 2 frags)") {
        result_type corr(propane_dclc_2_caps());
        input_type hc{hydrocarbon_fragmented_nuclei(3,2)};
        result_type caps = mod.run_as<the_pt>(hc);
        REQUIRE(AreCapsEqual(corr, caps));
    }

    SECTION("Propane (3 carbon 4 frags)") {
        result_type corr(propane_dclc_3_caps());
        input_type hc{hydrocarbon_fragmented_nuclei(3,1)};
        result_type caps = mod.run_as<the_pt>(hc);
        REQUIRE(AreCapsEqual(corr, caps));
    }

    SECTION("Average Bond Length Calculation"){
        // Tests the HC bond in propane
        chemist::Nuclei propane = hydrocarbon(3).nuclei();
        chemist::topology::ConnectivityTable con;
        con.set_n_atoms(11);
        con.add_bond(0,1);
        con.add_bond(1,2);
        con.add_bond(0,3);
        con.add_bond(0,4);
        con.add_bond(0,5);
        con.add_bond(1,6);
        con.add_bond(1,7);
        con.add_bond(2,8);
        con.add_bond(2,9);
        con.add_bond(2,10);
        double corr = 2.06;
        double test = ghostfragment::capping::average_bond_length(
            propane, con, 1, 6);
        REQUIRE(corr == Approx(test).margin(0.0001));
    }
}
