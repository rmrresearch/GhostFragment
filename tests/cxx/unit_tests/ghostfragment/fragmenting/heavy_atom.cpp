#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/connectivity_table.hpp>
#include <iostream>

using molecule   = simde::type::molecule;
using my_pt      = ghostfragment::pt::FragmentedNuclei;
using connect_pt = ghostfragment::ConnectivityTable;
using connect_t  = simde::type::connectivity_table;
using return_t   = ghostfragment::type::fragmented_molecule;

using input_type = chemist::Nuclei;
using value_type = input_type::value_type;
using result_type = chemist::FragmentedNuclei;

namespace {

auto make_lambda(input_type mol, const connect_t& conns) {
    return pluginplay::make_lambda<connect_pt>([=](const auto& mol_in) {
        REQUIRE(mol_in == mol);
        return conns;
    });
}

} // namespace

TEST_CASE("HeavyAtom") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("Heavy Atom Partition");

    SECTION("Empty Molecule") {
        input_type mol;

        mod.change_submod("Connectivity", make_lambda(mol, connect_t{}));

        const auto& test = mod.run_as<my_pt>(mol);

        result_type corr(mol);
        REQUIRE(corr == test);
    }

    SECTION("Throws if H makes more than one bond") {
        value_type H1("H", 1ul, 1.0, 1.0, 2.0, 3.0);
        value_type H2("H", 1ul, 1.0, 4.0, 5.0, 6.0);
        value_type O1("O", 8ul, 16.0, 7.0, 8.0, 9.0);
        input_type mol({H1, H2, O1});

        connect_t c(3);
        c.add_bond(0, 1);
        c.add_bond(0, 2);

        mod.change_submod("Connectivity", make_lambda(mol, c));

        REQUIRE_THROWS_AS(mod.run_as<my_pt>(mol), std::runtime_error);
    }

    SECTION("Throws if Z == 0") {
        input_type mol({input_type::value_type("Ez", 0, 1ul)});

        mod.change_submod("Connectivity", make_lambda(mol, connect_t{1}));

        REQUIRE_THROWS_AS(mod.run_as<my_pt>(mol), std::runtime_error);
    }

SECTION("H2 and H2O") {
        value_type H1("H", 1ul, 1.0, 1.0, 2.0, 3.0);
        value_type H2("H", 1ul, 1.0, 4.0, 5.0, 6.0);
        value_type H3("H", 1ul, 1.0, 7.0, 8.0, 9.0);
        value_type O1("O", 8ul, 16.0, 10.0, 11.0, 12.0);
        value_type H4("H", 1ul, 1.0, 13.0, 14.0, 15.0);
        input_type mol({H1, H2, H3, O1, H4});

        connect_t c(5);
        c.add_bond(0, 1);
        c.add_bond(2, 3);
        c.add_bond(3, 4);

        mod.change_submod("Connectivity", make_lambda(mol, c));
        const auto& test = mod.run_as<my_pt>(mol);
        result_type corr(mol);
        corr.add_fragment({0, 1});
        corr.add_fragment({2, 3, 4});
        REQUIRE(corr == test);
    }

SECTION("Isolated H") {
        value_type H1("H", 1ul, 1.0, 4.0, 5.0, 6.0);
        value_type H2("H", 1ul, 1.0, 7.0, 8.0, 9.0);
        value_type O1("O", 8ul, 16.0, 10.0, 11.0, 12.0);
        value_type H3("H", 1ul, 1.0, 13.0, 14.0, 15.0);
        input_type mol({H1, H2, O1, H3});

        connect_t c(4);
        c.add_bond(1, 2);
        c.add_bond(2, 3);

        mod.change_submod("Connectivity", make_lambda(mol, c));
        const auto& test = mod.run_as<my_pt>(mol);
        result_type corr(mol);
        corr.add_fragment({0});
        corr.add_fragment({1, 2, 3});
        REQUIRE(corr == test);
    }

SECTION("Bunch of heavy atoms") {
        value_type O1("O", 8ul, 16.0, 0.0, 1.0, 2.0);
        value_type O2("O", 8ul, 16.0, 1.0, 1.0, 2.0);
        value_type O3("O", 8ul, 16.0, 0.0, 1.0, 1.0);
        value_type O4("O", 8ul, 16.0, 1.0, 1.0, 1.0);
        value_type O5("O", 8ul, 16.0, 2.0, 1.0, 2.0);
        value_type O6("O", 8ul, 16.0, 2.0, 1.0, 1.0);
        input_type mol({O1, O2, O3, O4, O5, O6});

        connect_t c(6);
        c.add_bond(0, 1);
        c.add_bond(1, 2);
        c.add_bond(4, 5);

        mod.change_submod("Connectivity", make_lambda(mol, c));
        const auto& test = mod.run_as<my_pt>(mol);

        result_type corr(mol);
        corr.add_fragment({0});
        corr.add_fragment({1});
        corr.add_fragment({2});
        corr.add_fragment({3});
        corr.add_fragment({4});
        corr.add_fragment({5});
        REQUIRE(corr == test);
    }
}
