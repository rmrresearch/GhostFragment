#include "../test_ghostfragment.hpp"

using namespace ghostfragment;
using namespace testing;

using my_pt               = pt::NMers;
using capped_fragments_pt = pt::CappedFragments;
using screener_t          = pt::NMerScreener;
using capped_type = ghostfragment::pt::CappedFragmentsTraits::result_type;

/* Testing strategy.
 *
 * This is a driver. We assume the modules the driver calls work. So what we
 * really need to test here is the data flow, namely that the driver calls the
 * submods with the right inputs and that the driver properly forwards the
 * submodule results.
 */

TEST_CASE("NMer Driver") {
    auto mm   = initialize();
    auto& mod = mm.at("NMer Driver");

    for(std::size_t n_waters = 0; n_waters < 4; ++n_waters) {
        SECTION("N == " + std::to_string(n_waters)) {
            auto water_n = fragmented_water(n_waters);

            // The capped water fragments
            capped_type capped;
            auto empty_set = fragmented_water(0).new_subset();
            for(const auto& frag_i : water_n) capped.emplace(frag_i, empty_set);

            // The module doing the capping, just matters it returns capped
            auto cap_mod =
              pluginplay::make_lambda<capped_fragments_pt>([=](auto&& frags) {
                  REQUIRE(water_n == frags);
                  return capped;
              });

            for(unsigned n = 0; n <= n_waters; ++n) {
                // The nmers
                auto nmers = water_nmers(n_waters, n);

                // The module doing the screening, just matters it returns nmers
                auto screen_mod = pluginplay::make_lambda<screener_t>(
                  [=](auto&& capped_in, auto&& n_in) {
                      REQUIRE(capped == capped_in);
                      REQUIRE(n_in == n);
                      return nmers;
                  });

                // Tests for good n values
                SECTION("n == " + std::to_string(n)) {
                    mod.change_submod("Capper", cap_mod);
                    mod.change_submod("Screener", screen_mod);
                    mod.change_input("N-Mer Truncation Order", n);

                    const auto& [nmers_out] = mod.run_as<my_pt>(water_n);
                    REQUIRE(nmers == nmers_out);
                }

                // On last iteration check a bad n value
                if(n == n_waters) {
                    SECTION("Throws if n > N") {
                        mod.change_submod("Capper", cap_mod);
                        mod.change_submod("Screener", screen_mod);
                        mod.change_input("N-Mer Truncation Order", ++n);

                        using error_t = std::runtime_error;
                        REQUIRE_THROWS_AS(mod.run_as<my_pt>(water_n), error_t);
                    }
                }
            }
        }
    }
}
