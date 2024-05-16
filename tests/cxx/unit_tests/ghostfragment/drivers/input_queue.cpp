// #include "../test_ghostfragment.hpp"
// #include "hydrocarbon/hydrocarbon.h"
// #include <ghostfragment/property_types/property_types.hpp>
// #include <ghostfragment/property_types/fragmented_nuclei.hpp>
// #include <ghostfragment/property_types/fragmented_molecule.hpp>

// using namespace ghostfragment;
// using namespace testing;

// using my_pt    = pt::InputQueue;
// using frags_pt = pt::FragmentedNuclei;
// using mol_pt   = pt::FragmentedMolecule;

// using system_type  = chemist::ChemicalSystem;
// using frags_type   = chemist::FragmentedNuclei;
// using fragmol_type = chemist::FragmentedMolecule;
// using mol_type     = chemist::Molecule;
// using pair_type   = std::pair<chemist::ChemicalSystem, double>;
// using return_type = std::vector<pair_type>;

// namespace {

// auto make_frag_module(const system_type& mol, const frags_type& rv) {
//     return pluginplay::make_lambda<frags_pt>([=](auto&& mol_in) {
//         REQUIRE(mol_in == mol);
//         return rv;
//     });
// }

// auto make_mol_module(const frags_type& mol_1, const frags_type& mol_2,
// const fragmol_type& rv_1, const fragmol_type& rv_2) {
//     return pluginplay::make_lambda<mol_pt>([=](auto&& mol_in) {
//         // Conditional so that lambda function returns correct rv for both
//         calls
//         // in the InputQueue module
//         if(mol_in == mol_1) {
//             return rv_1;
//         }
//         else {
//             return rv_2;
//         }
//     });
// }

// } // namespace

// /* Testing strategy:
//  *
//  * InputQueue is mainly a driver. Aside from the finding of intersections,
//  * the rest of its behavior is determined by submodules. We thus employ
//  lambda
//  * functions as surrogates for these modules to test InputQueue itself.
//  */

// TEST_CASE("Input Queue") {
//     auto mm   = initialize();
//     auto& mod = mm.at("Input Queue");

//     SECTION("Empty System") {
//         system_type system;
//         return_type corr;

//         mod.change_submod("Fragmentation", make_frag_module(system,
//         frags_type())); mod.change_submod("FragtoMol",
//         make_mol_module(frags_type(), frags_type(), fragmol_type(),
//         fragmol_type())); REQUIRE_THROWS_AS(mod.run_as<my_pt>(system),
//         std::runtime_error);
//     }

//     SECTION("Single Atom") {
//         chemist::Molecule mol;
//         mol.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
//         system_type system(mol);

//         frags_type frags(mol.nuclei());
//         frags.add_fragment({0});

//         fragmol_type fragmol(frags);

//         return_type corr;
//         corr.push_back(pair_type(system, 1));

//         mod.change_submod("Fragmentation", make_frag_module(system, frags));
//         mod.change_submod("FragtoMol", make_mol_module(frags, frags, fragmol,
//         fragmol)); const auto& rv = mod.run_as<my_pt>(system); REQUIRE(corr
//         == rv);
//     }

//     SECTION("Methane Single Fragment") {
//         auto methane = hydrocarbon(1);
//         system_type system(methane);
//         frags_type frags(methane.nuclei());
//         frags.add_fragment({0, 1, 2, 3, 4});

//         fragmol_type fragmol(frags);

//         return_type corr;
//         corr.push_back(pair_type(system, 1));

//         mod.change_submod("Fragmentation", make_frag_module(system, frags));
//         mod.change_submod("FragtoMol", make_mol_module(frags, frags, fragmol,
//         fragmol)); const auto& rv = mod.run_as<my_pt>(system); REQUIRE(corr
//         == rv);
//     }

//     SECTION("Two Disjoint Fragments") {
//         chemist::Molecule mol;
//         mol.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
//         mol.push_back(chemist::Atom("H", 1, 1837.289, 1, 1, 1));
//         system_type system(mol);

//         frags_type frags(mol.nuclei());
//         frags.add_fragment({0});
//         frags.add_fragment({1});

//         fragmol_type fragmol(frags);

//         return_type corr;
//         chemist::Molecule mol_1;
//         chemist::Molecule mol_2;
//         mol_1.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
//         mol_2.push_back(chemist::Atom("H", 1, 1837.289, 1, 1, 1));
//         corr.push_back(pair_type(system_type(mol_1), 1));
//         corr.push_back(pair_type(system_type(mol_2), 1));

//         mod.change_submod("Fragmentation", make_frag_module(system, frags));
//         mod.change_submod("FragtoMol", make_mol_module(frags, frags, fragmol,
//         fragmol)); const auto& rv = mod.run_as<my_pt>(system); REQUIRE(corr
//         == rv);
//     }

//     SECTION("Two Nondisjoint Fragments") {
//         chemist::Molecule mol;
//         mol.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
//         mol.push_back(chemist::Atom("H", 1, 1837.289, 1, 1, 1));
//         mol.push_back(chemist::Atom("H", 1, 1837.289, 2, 2, 2));
//         system_type system(mol);

//         frags_type frags_1(mol.nuclei());
//         frags_1.add_fragment({0, 1});
//         frags_1.add_fragment({1, 2});

//         frags_type frags_2(mol.nuclei());
//         frags_2.add_fragment({0, 1});
//         frags_2.add_fragment({1, 2});
//         frags_2.add_fragment({1});

//         fragmol_type fragmol_1(frags_1);
//         fragmol_type fragmol_2(frags_2);

//         return_type corr;
//         chemist::Molecule mol_1;
//         chemist::Molecule mol_2;
//         chemist::Molecule mol_3;
//         mol_1.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
//         mol_1.push_back(chemist::Atom("H", 1, 1837.289, 1, 1, 1));
//         mol_2.push_back(chemist::Atom("H", 1, 1837.289, 1, 1, 1));
//         mol_2.push_back(chemist::Atom("H", 1, 1837.289, 2, 2, 2));
//         mol_3.push_back(chemist::Atom("H", 1, 1837.289, 1, 1, 1));
//         corr.push_back(pair_type(system_type(mol_1), 1));
//         corr.push_back(pair_type(system_type(mol_3), -1));
//         corr.push_back(pair_type(system_type(mol_2), 1));

//         mod.change_submod("Fragmentation", make_frag_module(system,
//         frags_1)); mod.change_submod("FragtoMol", make_mol_module(frags_1,
//         frags_2, fragmol_1, fragmol_2)); const auto& rv =
//         mod.run_as<my_pt>(system); REQUIRE(corr == rv);
//     }
// }
