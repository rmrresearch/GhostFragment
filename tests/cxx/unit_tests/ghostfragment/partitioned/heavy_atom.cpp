// #include "../test_ghostfragment.hpp"

// using molecule   = simde::type::molecule;
// using my_pt      = simde::FragmentedMolecule;
// using connect_pt = simde::Connectivity;
// using connect_t  = simde::type::connectivity_table;
// using return_t   = ghostfragment::type::fragmented_molecule;

// namespace {

// auto make_lambda(const molecule& mol, const connect_t& conns) {
//     return pluginplay::make_lambda<connect_pt>([=](const auto& mol_in) {
//         REQUIRE(mol_in == mol);
//         return conns;
//     });
// }

// } // namespace

// TEST_CASE("HeavyAtom") {
//     auto mm   = testing::initialize();
//     auto& mod = mm.at("Heavy Atom Partition");

//     // Since we are hard-coding the connectivity tables the coordinates don't
//     // matter
//     auto [H, He, O] = testing::some_atoms();

//     SECTION("Empty Molecule") {
//         molecule mol{};
//         mod.change_submod("Connectivity", make_lambda(mol, connect_t{}));

//         const auto& [rv] = mod.run_as<my_pt>(mol);

//         return_t corr(mol);
//         REQUIRE(corr == rv);
//     }

//     SECTION("Throws if H makes more than one bond") {
//         molecule mol{H, H, O};

//         connect_t c(3);
//         c.add_bond(0, 1);
//         c.add_bond(0, 2);

//         mod.change_submod("Connectivity", make_lambda(mol, c));

//         REQUIRE_THROWS_AS(mod.run_as<my_pt>(mol), std::runtime_error);
//     }

//     SECTION("Throws if Z == 0") {
//         molecule mol{molecule::value_type{"Ez", 0ul}};
//         mod.change_submod("Connectivity", make_lambda(mol, connect_t{1}));

//         REQUIRE_THROWS_AS(mod.run_as<my_pt>(mol), std::runtime_error);
//     }

//     SECTION("H2 and H2O") {
//         molecule mol{H, H, H, O, H};

//         connect_t c(5);
//         c.add_bond(0, 1);
//         c.add_bond(2, 3);
//         c.add_bond(3, 4);

//         mod.change_submod("Connectivity", make_lambda(mol, c));
//         const auto& [rv] = mod.run_as<my_pt>(mol);
//         return_t corr(mol, {{0, 1}, {2, 3, 4}});
//         REQUIRE(corr == rv);
//     }

//     SECTION("Isolated H") {
//         molecule mol{H, H, O, H};

//         connect_t c(4);
//         c.add_bond(0, 2);
//         c.add_bond(2, 3);

//         mod.change_submod("Connectivity", make_lambda(mol, c));
//         const auto& [rv] = mod.run_as<my_pt>(mol);
//         return_t corr(mol, {{1}, {0, 2, 3}});
//         REQUIRE(corr == rv);
//     }

//     SECTION("Bunch of heavy atoms") {
//         molecule mol{O, O, O, O, O, O};

//         connect_t c(6);
//         c.add_bond(0, 1);
//         c.add_bond(1, 2);
//         c.add_bond(4, 5);

//         mod.change_submod("Connectivity", make_lambda(mol, c));
//         const auto& [rv] = mod.run_as<my_pt>(mol);
//         return_t corr(mol, {{0}, {1}, {2}, {3}, {4}, {5}});
//         REQUIRE(corr == rv);
//     }
// }
