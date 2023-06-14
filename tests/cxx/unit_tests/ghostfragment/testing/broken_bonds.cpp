#include "../test_ghostfragment.hpp"
#include "broken_bonds.hpp"
#include "hydrocarbon/hydrocarbon_fragment.hpp"

using namespace testing;

TEST_CASE("Broken Bonds") {
    using pt         = ghostfragment::pt::BrokenBonds;
    using input_type = chemist::FragmentedNuclei;

    using size_type   = typename input_type::size_type;
    using bond_type   = std::pair<size_type, size_type>;
    using bond_set    = std::set<bond_type>;
    using result_type = std::vector<bond_set>;

    auto mm   = testing::initialize();
    auto& mod = mm.at("Broken Bonds");

    SECTION("Ethane fragment (size 1)") {
        auto corr = bonds_ethane_one();
        input_type hc{hydrocarbon_fragmented_nuclei(2, 1)};
        result_type test = mod.run_as<pt>(hc);
        REQUIRE(corr == test);
    }

    SECTION("Propane fragment (size 1)") {
        auto corr = bonds_propane_one();
        input_type hc{hydrocarbon_fragmented_nuclei(3, 1)};
        result_type test = mod.run_as<pt>(hc);
        REQUIRE(corr == test);
    }

    SECTION("Propane fragment (size 2)") {
        auto corr = bonds_propane_two();
        input_type hc{hydrocarbon_fragmented_nuclei(3, 2)};
        result_type test = mod.run_as<pt>(hc);
        REQUIRE(corr == test);
    }
}