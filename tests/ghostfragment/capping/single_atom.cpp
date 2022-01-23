#include "../test_ghostfragment.hpp"

using namespace ghostfragment;
using namespace testing;

using the_pt      = ghostfragment::pt::CappedFragments;
using connect_pt  = simde::Connectivity;
using ct_t        = simde::type::connectivity_table;
using return_type = ghostfragment::pt::CappedFragmentsTraits::result_type;

TEST_CASE("SingleAtom") {
    auto mm   = initialize();
    auto& mod = mm.at("Atomic Capping");

    SECTION("Water monomers") {
        for(std::size_t n_waters = 1; n_waters < 4; ++n_waters) {
            SECTION("N = " + std::to_string(n_waters)) {
                auto water_n = fragmented_water(n_waters);

                auto conn_mod =
                  pluginplay::make_lambda<connect_pt>([=](const auto& mol_in) {
                      REQUIRE(mol_in == water_n.object());
                      return water_connectivity(n_waters);
                  });

                // No caps needed, so just empty sets
                return_type corr;
                auto empty_set = fragmented_water(0).new_subset();
                for(const auto& frag_i : water_n)
                    corr.emplace(frag_i, empty_set);

                mod.change_submod("Connectivity", conn_mod);
                const auto& [frag2cap] = mod.run_as<the_pt>(water_n);
                REQUIRE(frag2cap == corr);
            }
        }
    }

    // TODO: Test for something that actually has caps....
}