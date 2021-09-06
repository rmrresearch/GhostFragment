#include "../test_ghostfragment.hpp"

using molecule   = simde::type::molecule;
using my_pt      = simde::FragmentedMolecule;
using connect_pt = simde::Connectivity;
using connect_t  = simde::type::connectivity_table;
using tag_t      = ghostfragment::type::tag;
using return_t   = ghostfragment::type::fragmented_molecule;
using subset_t   = typename return_t::value_type;

TEST_CASE("Cluster Partitioner") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("Cluster Partition");

    // Since we are hard-coding the connectivity tables the coordinates don't
    // matter
    auto [H, He, O] = testing::some_atoms();

    SECTION("Empty Molecule") {
        const auto& [rv] = mod.run_as<my_pt>(molecule{});
        return_t corr(molecule{});
        REQUIRE(corr == rv);
    }

    SECTION("One Atom") {
        molecule mol{He};

        auto l = pluginplay::make_lambda<connect_pt>([=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            return connect_t{};
        });
        mod.change_submod("Connectivity", l);
        const auto& [rv] = mod.run_as<my_pt>(mol);
        return_t corr(mol, {{0}});
        REQUIRE(corr == rv);
    }

    SECTION("Two Atoms - Not bonded") {
        molecule mol{He, H};

        auto l = pluginplay::make_lambda<connect_pt>([=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            return connect_t{};
        });
        mod.change_submod("Connectivity", l);
        const auto& [rv] = mod.run_as<my_pt>(mol);
        return_t corr(mol, {{0}, {1}});
        REQUIRE(corr == rv);
    }

    SECTION("Two Atoms - Bonded") {
        molecule mol{He, H};

        auto l = pluginplay::make_lambda<connect_pt>([=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            connect_t t(2);
            t.add_bond(0, 1);
            return t;
        });
        mod.change_submod("Connectivity", l);
        const auto& [rv] = mod.run_as<my_pt>(mol);
        return_t corr(mol, {{0, 1}});
        REQUIRE(corr == rv);
    }

    SECTION("Two molecules - nicely partitioned") {
        molecule mol{H, H, O, H, H};

        auto l = pluginplay::make_lambda<connect_pt>([=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            connect_t t(5);
            t.add_bond(0, 2);
            t.add_bond(1, 2);
            t.add_bond(3, 4);
            return t;
        });
        mod.change_submod("Connectivity", l);
        const auto& [rv] = mod.run_as<my_pt>(mol);
        return_t corr(mol, {{0, 1, 2}, {3, 4}});
        REQUIRE(corr == rv);
    }

    SECTION("Two molecules - mixed up") {
        molecule mol{H, H, O, H, H};

        auto l = pluginplay::make_lambda<connect_pt>([=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            connect_t t(5);
            t.add_bond(1, 3);
            t.add_bond(0, 2);
            t.add_bond(2, 4);
            return t;
        });
        mod.change_submod("Connectivity", l);
        const auto& [rv] = mod.run_as<my_pt>(mol);

        return_t corr(mol, {{0, 2, 4}, {1, 3}});
        REQUIRE(corr == rv);
    }
}