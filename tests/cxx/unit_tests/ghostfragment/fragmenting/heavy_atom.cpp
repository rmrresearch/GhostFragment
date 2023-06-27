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

    // Since we are hard-coding the connectivity tables the coordinates don't
    // matter
    auto [H, He, O] = testing::some_nuclei();

    SECTION("Empty Molecule") {
        input_type mol;

        mod.change_submod("Connectivity", make_lambda(mol, connect_t{}));

        const auto& test = mod.run_as<my_pt>(mol);

        result_type corr(mol);
        REQUIRE(corr == test);
    }

    SECTION("Throws if H makes more than one bond") {
        input_type mol({H, H, O});

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
        input_type mol({H, H, H, O, H});

        std::cout << "H2 and H20" << std::endl;

        connect_t c(5);
        c.add_bond(0, 1);
        c.add_bond(2, 3);
        c.add_bond(3, 4);

        mod.change_submod("Connectivity", make_lambda(mol, c));
        const auto& test = mod.run_as<my_pt>(mol);
        std::cout << "Recieved fragmented nuclei has size " << test.size() << std::endl;

        for(auto a : test){
            std::cout << "Fragment " << a << " has atoms";
            for(auto b : a){
                std::cout << " " << b;
            }
            std::cout << std::endl;
        }

        result_type corr(mol);
        corr.add_fragment({0, 1});
        corr.add_fragment({2, 3, 4});
        REQUIRE(corr == test);
    }

    SECTION("Isolated H") {
        input_type mol({H, H, O, H});

        std::cout << "Isolated H" << std::endl;

        connect_t c(4);
        c.add_bond(1, 2);
        c.add_bond(2, 3);

        mod.change_submod("Connectivity", make_lambda(mol, c));
        const auto& test = mod.run_as<my_pt>(mol);
        std::cout << "Recieved fragmented nuclei has size " << test.size() << std::endl;

        for(auto a : test){
            std::cout << "Fragment " << a << " has atoms";
            for(auto b : a){
                std::cout << " " << b;
            }
            std::cout << std::endl;
        }
        result_type corr(mol);
        corr.add_fragment({0});
        corr.add_fragment({1, 2, 3});
        REQUIRE(corr == test);
    }

    SECTION("Bunch of heavy atoms") {
        input_type mol({O, O, O, O, O, O});

        std::cout << "Bunch of heavy atoms" << std::endl;

        connect_t c(6);
        c.add_bond(0, 1);
        c.add_bond(1, 2);
        c.add_bond(4, 5);

        mod.change_submod("Connectivity", make_lambda(mol, c));
        const auto& test = mod.run_as<my_pt>(mol);
        std::cout << "Recieved fragmented nuclei has size " << test.size() << std::endl;

        for(auto a : test){
            std::cout << "Fragment " << a << " has atoms";
            for(auto b : a){
                std::cout << " " << b;
            }
            std::cout << std::endl;
        }
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