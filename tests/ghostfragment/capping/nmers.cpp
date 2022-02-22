#include "../test_ghostfragment.hpp"

using namespace ghostfragment;
using namespace testing;

using frag_pt = ghostfragment::pt::CappedFragments;
using nmer_pt = ghostfragment::pt::CappedNMers;

using capped_frags_traits = pt::CappedFragmentsTraits;
using frags_type   = std::decay_t<typename capped_frags_traits::input_type>;
using capped_frags = typename capped_frags_traits::result_type;

using capped_nmers_traits = pt::CappedNMersTraits;
using return_type         = typename capped_nmers_traits::result_type;

namespace {

template<typename NMersType>
auto flatten(NMersType&& nmers) {
    const auto& frags = nmers.object();
    frags_type flattened_nmers(frags.object());

    for(const auto& nmer : nmers) {
        auto frag = flattened_nmers.new_subset();
        for(const auto& i : nmer) frag += frags[i];
        flattened_nmers.insert(frag);
    }
    return flattened_nmers;
}

} // namespace

TEST_CASE("NMer Capping") {
    auto mm   = initialize();
    auto& mod = mm.at("NMer Capper");

    SECTION("Water monomers") {
        for(std::size_t n_waters = 1; n_waters < 4; ++n_waters) {
            SECTION("N = " + std::to_string(n_waters)) {
                for(std::size_t n = 1; n <= n_waters; ++n) {
                    SECTION("n = " + std::to_string(n)) {
                        auto nmers = water_nmers(n_waters, n);

                        // No caps needed, so just empty sets
                        auto empty_set = fragmented_water(0).new_subset();

                        auto submod = pluginplay::make_lambda<frag_pt>(
                          [=](auto&& frags_in) {
                              REQUIRE(frags_in == flatten(nmers));
                              capped_frags rv;
                              for(const auto& frag : frags_in)
                                  rv.emplace(frag, empty_set);
                              return rv;
                          });

                        return_type corr;
                        for(const auto& nmer_i : nmers)
                            corr.emplace(nmer_i, empty_set);

                        mod.change_submod("Fragment Capper", submod);
                        const auto& [capped_nmers] = mod.run_as<nmer_pt>(nmers);
                        REQUIRE(capped_nmers == corr);
                    }
                }
            }
        }
    }
}
