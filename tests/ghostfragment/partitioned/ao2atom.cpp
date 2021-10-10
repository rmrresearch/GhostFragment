#include "../test_ghostfragment.hpp"
#include "ghostfragment/ghostfragment.hpp"
#include <catch2/catch.hpp>

TEST_CASE("AO2Atom") {
    auto mm  = testing::initialize();
    auto mod = mm.at("AO Center to Atom Mapper");

    auto water       = testing::water();
    auto aos         = testing::sto3g(water);
    const auto& [rv] = mod.run_as<simde::AtomToCenter>(water, aos.basis_set());

    using return_type = simde::atom_to_center_return_type;
    using set_type    = typename return_type::value_type;
    return_type corr{set_type{0}, set_type{1}, set_type{2}};
    REQUIRE(corr == rv);
}