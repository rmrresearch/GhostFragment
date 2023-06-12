#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/connectivity_table.hpp>

using namespace ghostfragment;
using namespace testing;

using the_pt      = pt::Capped;
using connect_pt  = ConnectivityTable;
using ct_t        = ConnectivityTableTraits::result_type;
using return_type = pt::CappedTraits::result_type;
using size_type   = std::size_t;

TEST_CASE("SingleAtom") {
    auto mm   = initialize();
    auto& mod = mm.at("Atomic Capping");

    SECTION("Water monomers") {
        for(size_type n_waters = 1; n_waters < 4; ++n_waters) {
            SECTION("N = " + std::to_string(n_waters)) {
                auto water_n = water_fragmented_nuclei(n_waters);

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

    SECTION("Hydrocarbon monomers") {
        // TODO: Write me!!!
    }
}
