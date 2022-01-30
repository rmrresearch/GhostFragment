#include "../test_ghostfragment.hpp"

using my_pt = ghostfragment::pt::NMerScreener;

TEST_CASE("Distance Screening") {
    auto mm  = testing::initialize();
    auto mod = mm.at("Screen by distance");
}