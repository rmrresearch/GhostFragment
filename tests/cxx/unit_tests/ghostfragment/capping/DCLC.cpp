#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/connectivity_table.hpp>

using namespace ghostfragment;
using namespace testing;

using the_pt      = pt::Capped;
using connect_pt  = ConnectivityTable;
using ct_t        = ConnectivityTableTraits::result_type;
using return_type = pt::CappedTraits::result_type;
using size_type   = std::size_t;

TEST_CASE("DCLC Capping") {
    auto mm   = initialize();
    auto& mod = mm.at("DCLC Capping");

    SECTION("Hydrocarbon monomers") {
        for(size_type n_carbons = 1; n_carbons < 4; ++n_carbons) {
            SECTION("N = " + std::to_string(n_carbons)) {
                auto carbon_n = water_fragmented_nuclei(n_waters);

                auto conn_mod =
                  pluginplay::make_lambda<connect_pt>([=](const auto& mol_in) {
                      REQUIRE(mol_in == water_n.supersystem());
                      return water_connectivity(n_waters);
                  });

                return_type corr(n_waters);

                mod.change_submod("Connectivity", conn_mod);
                const auto& caps = mod.run_as<the_pt>(water_n);
                REQUIRE(caps == corr);
            }
        }
    }
}
