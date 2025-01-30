/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/topology/connectivity_table.hpp>
#include <iostream>

using namespace ghostfragment;

using my_pt      = pt::FragmentedNuclei;
using connect_pt = pt::ConnectivityTable;

using chemical_system_type = typename pt::FragmentedNucleiTraits::system_type;
using molecule_type =
  typename chemical_system_type::molecule_traits::value_type;
using atom_type   = typename molecule_type::atom_type;
using result_type = pt::FragmentedNucleiTraits::result_type;
using connect_t   = typename pt::ConnectivityTableTraits::result_type;

namespace {

// Used to test that HeavyAtom correctly calls the connectivity submodule
auto make_lambda(molecule_type mol, const connect_t& conns) {
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
        chemical_system_type sys;

        auto lambda = make_lambda(sys.molecule(), connect_t{});
        mod.change_submod("Connectivity", lambda);

        const auto& test = mod.run_as<my_pt>(sys);

        result_type corr(sys.molecule().nuclei().as_nuclei());
        REQUIRE(corr == test);
    }

    SECTION("Throws if H makes more than one bond") {
        atom_type H1("H", 1ul, 1.0, 1.0, 2.0, 3.0);
        atom_type H2("H", 1ul, 1.0, 4.0, 5.0, 6.0);
        atom_type O1("O", 8ul, 16.0, 7.0, 8.0, 9.0);
        molecule_type mol;
        mol.push_back(H1);
        mol.push_back(H2);
        mol.push_back(O1);
        chemical_system_type system(mol);

        connect_t c(3);
        c.add_bond(0, 1);
        c.add_bond(0, 2);

        mod.change_submod("Connectivity", make_lambda(mol, c));

        REQUIRE_THROWS_AS(mod.run_as<my_pt>(system), std::runtime_error);
    }

    SECTION("Throws if Z == 0") {
        molecule_type mol;
        mol.push_back(atom_type("Ez", 0, 1ul, 0, 0, 0));
        chemical_system_type system(mol);

        auto lambda = make_lambda(mol, connect_t{1});

        mod.change_submod("Connectivity", lambda);

        REQUIRE_THROWS_AS(mod.run_as<my_pt>(system), std::runtime_error);
    }

    SECTION("H2 and H2O") {
        atom_type H1("H", 1ul, 1.0, 1.0, 2.0, 3.0);
        atom_type H2("H", 1ul, 1.0, 4.0, 5.0, 6.0);
        atom_type H3("H", 1ul, 1.0, 7.0, 8.0, 9.0);
        atom_type O1("O", 8ul, 16.0, 10.0, 11.0, 12.0);
        atom_type H4("H", 1ul, 1.0, 13.0, 14.0, 15.0);
        molecule_type mol;
        mol.push_back(H1);
        mol.push_back(H2);
        mol.push_back(H3);
        mol.push_back(O1);
        mol.push_back(H4);
        chemical_system_type system(mol);

        connect_t c(5);
        c.add_bond(0, 1);
        c.add_bond(2, 3);
        c.add_bond(3, 4);

        mod.change_submod("Connectivity", make_lambda(mol, c));
        const auto& test = mod.run_as<my_pt>(system);
        result_type corr(mol.nuclei().as_nuclei());
        corr.insert({0, 1});
        corr.insert({3, 2, 4}); // Finds the Oxygen first
        REQUIRE(corr == test);
    }

    SECTION("Isolated H") {
        atom_type H1("H", 1ul, 1.0, 4.0, 5.0, 6.0);
        atom_type H2("H", 1ul, 1.0, 7.0, 8.0, 9.0);
        atom_type O1("O", 8ul, 16.0, 10.0, 11.0, 12.0);
        atom_type H3("H", 1ul, 1.0, 13.0, 14.0, 15.0);
        molecule_type mol;
        mol.push_back(H1);
        mol.push_back(H2);
        mol.push_back(O1);
        mol.push_back(H3);
        chemical_system_type system(mol);

        connect_t c(4);
        c.add_bond(1, 2);
        c.add_bond(2, 3);

        mod.change_submod("Connectivity", make_lambda(mol, c));
        const auto& test = mod.run_as<my_pt>(system);
        result_type corr(mol.nuclei().as_nuclei());
        corr.insert({0});
        corr.insert({2, 1, 3}); // Finds the Oxygen first
        REQUIRE(corr == test);
    }

    SECTION("Bunch of heavy atoms") {
        atom_type O1("O", 8ul, 16.0, 0.0, 1.0, 2.0);
        atom_type O2("O", 8ul, 16.0, 1.0, 1.0, 2.0);
        atom_type O3("O", 8ul, 16.0, 0.0, 1.0, 1.0);
        atom_type O4("O", 8ul, 16.0, 1.0, 1.0, 1.0);
        atom_type O5("O", 8ul, 16.0, 2.0, 1.0, 2.0);
        atom_type O6("O", 8ul, 16.0, 2.0, 1.0, 1.0);
        molecule_type mol;
        mol.push_back(O1);
        mol.push_back(O2);
        mol.push_back(O3);
        mol.push_back(O4);
        mol.push_back(O5);
        mol.push_back(O6);
        chemical_system_type system(mol);

        connect_t c(6);
        c.add_bond(0, 1);
        c.add_bond(1, 2);
        c.add_bond(4, 5);

        mod.change_submod("Connectivity", make_lambda(mol, c));
        const auto& test = mod.run_as<my_pt>(system);

        result_type corr(mol.nuclei().as_nuclei());
        corr.insert({0});
        corr.insert({1});
        corr.insert({2});
        corr.insert({3});
        corr.insert({4});
        corr.insert({5});
        REQUIRE(corr == test);
    }
}
