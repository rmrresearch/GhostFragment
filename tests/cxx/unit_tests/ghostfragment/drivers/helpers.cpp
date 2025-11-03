#include "../test_ghostfragment.hpp"
#include <ghostfragment/drivers/helpers.hpp>

using namespace ghostfragment::drivers;
using namespace ghostfragment::type;
using int_vector = std::vector<std::size_t>;

TEST_CASE("map_atomic_bases_to_atoms") {
    SECTION("One Water") {
        // Create a simple chemical system and basis set
        auto mol       = testing::water(1);
        auto basis_set = testing::water_sto3g(mol);
        chemist::ChemicalSystem system(std::move(mol));

        // Map basis functions to atoms
        auto bf_map = map_atomic_bases_to_atoms(system, basis_set);

        REQUIRE(bf_map[0] == int_vector{0});
        REQUIRE(bf_map[1] == int_vector{1});
        REQUIRE(bf_map[2] == int_vector{2});
    }

    SECTION("Two Water") {
        // Create a simple chemical system and basis set
        auto mol       = testing::water(2);
        auto basis_set = testing::water_sto3g(mol);
        chemist::ChemicalSystem system(std::move(mol));

        // Map basis functions to atoms
        auto bf_map = map_atomic_bases_to_atoms(system, basis_set);

        REQUIRE(bf_map[0] == int_vector{0});
        REQUIRE(bf_map[1] == int_vector{1});
        REQUIRE(bf_map[2] == int_vector{2});
        REQUIRE(bf_map[3] == int_vector{3});
        REQUIRE(bf_map[4] == int_vector{4});
        REQUIRE(bf_map[5] == int_vector{5});
    }
}

TEST_CASE("make_sub_basis_set") {
    // Create a simple chemical system and basis set
    auto mol       = testing::water(2);
    auto basis_set = testing::water_sto3g(mol);
    chemist::ChemicalSystem system(std::move(mol));

    int_vector water0_indices{0, 1, 2};
    int_vector water1_indices{3, 4, 5};
    auto sub_basis0 = make_sub_basis_set(basis_set, water0_indices);
    auto sub_basis1 = make_sub_basis_set(basis_set, water1_indices);

    REQUIRE(sub_basis0.size() == 3);
    REQUIRE(sub_basis0.at(0) == basis_set.at(0));
    REQUIRE(sub_basis0.at(1) == basis_set.at(1));
    REQUIRE(sub_basis0.at(2) == basis_set.at(2));
    REQUIRE(sub_basis1.size() == 3);
    REQUIRE(sub_basis1.at(0) == basis_set.at(3));
    REQUIRE(sub_basis1.at(1) == basis_set.at(4));
    REQUIRE(sub_basis1.at(2) == basis_set.at(5));
}

TEST_CASE("build_vmfc_ao_energy_inputs") {
    // Create a simple chemical system and basis set
    auto mol       = testing::water(2);
    auto basis_set = testing::water_sto3g(mol);
    chemist::ChemicalSystem system(std::move(mol));

    // Fragment the system into two waters
    fragmented_molecule frag_mol(testing::water_fragmented_nuclei(2), 0, 1);
    fragmented_chemical_system fragments(frag_mol);

    // Map basis functions to atoms
    auto bf_map = map_atomic_bases_to_atoms(system, basis_set);

    SECTION("n == 1") {
        auto inputs =
          build_vmfc_ao_energy_inputs(1, basis_set, fragments, bf_map);

        REQUIRE(inputs.size() == 2); // Two fragments

        // Check first fragment input
        auto [c0, basis0, sys0] = inputs[0];
        REQUIRE(c0 == 1.0);
        REQUIRE(sys0 == fragments.at(0));
        REQUIRE(basis0.size() == 3);
        REQUIRE(basis0.at(0) == basis_set.at(0));
        REQUIRE(basis0.at(1) == basis_set.at(1));
        REQUIRE(basis0.at(2) == basis_set.at(2));

        // Check second fragment input
        auto [c1, basis1, sys1] = inputs[1];
        REQUIRE(c1 == 1.0);
        REQUIRE(sys1 == fragments.at(1));
        REQUIRE(basis1.size() == 3);
        REQUIRE(basis1.at(0) == basis_set.at(3));
        REQUIRE(basis1.at(1) == basis_set.at(4));
        REQUIRE(basis1.at(2) == basis_set.at(5));
    }

    SECTION("n == 2") {
        auto inputs =
          build_vmfc_ao_energy_inputs(2, basis_set, fragments, bf_map);

        REQUIRE(inputs.size() == 5); // three more calcs over n == 1

        // Monomer 0 in its own basis
        auto [c0, basis0, sys0] = inputs[0];
        REQUIRE(c0 == 1.0);
        REQUIRE(sys0 == fragments.at(0));
        REQUIRE(basis0.size() == 3);
        REQUIRE(basis0.at(0) == basis_set.at(0));
        REQUIRE(basis0.at(1) == basis_set.at(1));
        REQUIRE(basis0.at(2) == basis_set.at(2));

        // Monomer 1 in its own basis
        auto [c1, basis1, sys1] = inputs[1];
        REQUIRE(c1 == 1.0);
        REQUIRE(sys1 == fragments.at(1));
        REQUIRE(basis1.size() == 3);
        REQUIRE(basis1.at(0) == basis_set.at(3));
        REQUIRE(basis1.at(1) == basis_set.at(4));
        REQUIRE(basis1.at(2) == basis_set.at(5));

        // Monomer 0 in dimer basis
        auto [c2, basis2, sys2] = inputs[2];
        REQUIRE(c2 == -1.0);
        REQUIRE(sys2 == fragments.at(0));
        REQUIRE(basis2.size() == 6);
        REQUIRE(basis2.at(0) == basis_set.at(0));
        REQUIRE(basis2.at(1) == basis_set.at(1));
        REQUIRE(basis2.at(2) == basis_set.at(2));
        REQUIRE(basis2.at(3) == basis_set.at(3));
        REQUIRE(basis2.at(4) == basis_set.at(4));
        REQUIRE(basis2.at(5) == basis_set.at(5));

        // Monomer 1 in dimer basis
        auto [c3, basis3, sys3] = inputs[3];
        REQUIRE(c3 == -1.0);
        REQUIRE(sys3 == fragments.at(1));
        REQUIRE(basis3.size() == 6);
        REQUIRE(basis3.at(0) == basis_set.at(0));
        REQUIRE(basis3.at(1) == basis_set.at(1));
        REQUIRE(basis3.at(2) == basis_set.at(2));
        REQUIRE(basis3.at(3) == basis_set.at(3));
        REQUIRE(basis3.at(4) == basis_set.at(4));
        REQUIRE(basis3.at(5) == basis_set.at(5));

        // Dimer in dimer basis
        auto [c4, basis4, sys4] = inputs[4];
        REQUIRE(c4 == 1.0);
        REQUIRE(sys4 == fragments.concatenate({0, 1}));
        REQUIRE(basis4.size() == 6);
        REQUIRE(basis4.at(0) == basis_set.at(0));
        REQUIRE(basis4.at(1) == basis_set.at(1));
        REQUIRE(basis4.at(2) == basis_set.at(2));
        REQUIRE(basis4.at(3) == basis_set.at(3));
        REQUIRE(basis4.at(4) == basis_set.at(4));
        REQUIRE(basis4.at(5) == basis_set.at(5));
    }
}