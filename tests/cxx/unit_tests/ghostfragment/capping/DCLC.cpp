#include "../test_ghostfragment.hpp"
#include "DCLC.hpp"
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
    mm.change_submod("DCLC Capping", "Connectivity", 
                     "Covalent Radius");
    auto& mod      = mm.at("DCLC Capping");

    SECTION("Ethane (2 carbon 2 frags)") {
        result_type corr(Ethane2());
        input_type hc{hydrocarbon_fragmented_nuclei(2,1)};
        // mod.change_submod("Connectivity", "Covalent Radius");
        result_type caps = mod.run_as<the_pt>(hc);
        REQUIRE(AreCapsEqual(corr, caps));
    }

    SECTION("Propane (3 carbon 2 frags)") {
        result_type corr(Propane2());
        input_type hc{hydrocarbon_fragmented_nuclei(3,2)};
        result_type caps = mod.run_as<the_pt>(hc);
        REQUIRE(AreCapsEqual(corr, caps));
    }

    SECTION("Propane (3 carbon 4 frags)") {
        result_type corr(Propane4());
        input_type hc{hydrocarbon_fragmented_nuclei(3,1)};
        result_type caps = mod.run_as<the_pt>(hc);
        REQUIRE(AreCapsEqual(corr, caps));
    }
}
