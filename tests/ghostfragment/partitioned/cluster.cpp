#include "../test_ghostfragment.hpp"

using molecule   = ghostfragment::type::molecule;
using atom       = typename molecule::value_type;
using my_pt      = ghostfragment::pt::fragmented_mol;
using connect_pt = ghostfragment::pt::connectivity;
using connect_t  = ghostfragment::type::connectivity_table;
using tag_t      = ghostfragment::type::tag;
using return_t   = std::map<tag_t, molecule>;

TEST_CASE("Cluster Partitioner") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("Cluster Partition");

    // Since we are hard-coding the connectivity tables the coordinates don't
    // matter
    atom H{"H", 1ul};
    atom He{"He", 2ul};
    atom O{"O", 8ul};

    SECTION("Empty Molecule") {
        const auto& [rv] = mod.run_as<my_pt>(molecule{});
        return_t corr;
        REQUIRE(corr == rv);
    }

    SECTION("One Atom") {
        molecule mol(He);

        auto l = [=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            return connect_t{};
        };
        mod.change_submod("Connectivity", sde::make_lambda<connect_pt>(l));
        const auto& [rv] = mod.run_as<my_pt>(mol);
        return_t corr{{"0", mol}};
        REQUIRE(corr == rv);
    }

    SECTION("Two Atoms - Not bonded") {
        molecule mol(He, H);

        auto l = [=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            return connect_t{};
        };
        mod.change_submod("Connectivity", sde::make_lambda<connect_pt>(l));
        const auto& [rv] = mod.run_as<my_pt>(mol);
        return_t corr{{"0", molecule(He)}, {"1", molecule(H)}};
        REQUIRE(corr == rv);
    }

    SECTION("Two Atoms - Bonded") {
        molecule mol(He, H);

        auto l = [=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            connect_t t(2);
            t.add_bond(0, 1);
            return t;
        };
        mod.change_submod("Connectivity", sde::make_lambda<connect_pt>(l));
        const auto& [rv] = mod.run_as<my_pt>(mol);
        return_t corr{{"0", mol}};
        REQUIRE(corr == rv);
    }

    SECTION("Two molecules - nicely partitioned") {
        molecule mol(H, H, O, H, H);

        auto l = [=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            connect_t t(5);
            t.add_bond(0, 2);
            t.add_bond(1, 2);
            t.add_bond(3, 4);
            return t;
        };
        mod.change_submod("Connectivity", sde::make_lambda<connect_pt>(l));
        const auto& [rv] = mod.run_as<my_pt>(mol);
        return_t corr{{"0", molecule(H, H, O)}, {"1", molecule(H, H)}};
        REQUIRE(corr == rv);
    }

    SECTION("Two molecules - mixed up") {
        molecule mol(H, H, O, H, H);

        auto l = [=](const auto& mol_in) {
            REQUIRE(mol_in == mol);
            connect_t t(5);
            t.add_bond(1, 3);
            t.add_bond(0, 2);
            t.add_bond(2, 4);
            return t;
        };
        mod.change_submod("Connectivity", sde::make_lambda<connect_pt>(l));
        const auto& [rv] = mod.run_as<my_pt>(mol);

        return_t corr{{"0", molecule(H, O, H)}, {"1", molecule(H, H)}};
        REQUIRE(corr == rv);
    }
}