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

template<typename T, typename U, typename V>
void check_monomer_bs(T&& fragments, U&& basis_set, V&& inputs) {
    // Check first fragment input
    auto [str0, c0, basis0, sys0] = inputs[0];
    REQUIRE(str0 == "0-0");
    REQUIRE(c0 == 1.0);
    REQUIRE(sys0 == fragments.at(0));
    REQUIRE(basis0.size() == 3);
    REQUIRE(basis0.at(0) == basis_set.at(0));
    REQUIRE(basis0.at(1) == basis_set.at(1));
    REQUIRE(basis0.at(2) == basis_set.at(2));

    // Check second fragment input
    auto [str1, c1, basis1, sys1] = inputs[1];
    REQUIRE(str1 == "1-1");
    REQUIRE(c1 == 1.0);
    REQUIRE(sys1 == fragments.at(1));
    REQUIRE(basis1.size() == 3);
    REQUIRE(basis1.at(0) == basis_set.at(3));
    REQUIRE(basis1.at(1) == basis_set.at(4));
    REQUIRE(basis1.at(2) == basis_set.at(5));

    // Check third fragment input
    auto [str2, c2, basis2, sys2] = inputs[2];
    REQUIRE(str2 == "2-2");
    REQUIRE(c2 == 1.0);
    REQUIRE(sys2 == fragments.at(2));
    REQUIRE(basis2.size() == 3);
    REQUIRE(basis2.at(0) == basis_set.at(6));
    REQUIRE(basis2.at(1) == basis_set.at(7));
    REQUIRE(basis2.at(2) == basis_set.at(8));
}

template<typename T, typename U, typename V>
void check_dimer_bs(T&& fragments, U&& basis_set, V&& inputs) {
    // Monomer 0 in dimer 0 basis
    auto [str3, c3, basis3, sys3] = inputs[3];
    REQUIRE(str3 == "0-0_1");
    REQUIRE(c3 == -1.0);
    REQUIRE(sys3 == fragments.at(0));
    REQUIRE(basis3.size() == 6);
    REQUIRE(basis3.at(0) == basis_set.at(0));
    REQUIRE(basis3.at(1) == basis_set.at(1));
    REQUIRE(basis3.at(2) == basis_set.at(2));
    REQUIRE(basis3.at(3) == basis_set.at(3));
    REQUIRE(basis3.at(4) == basis_set.at(4));
    REQUIRE(basis3.at(5) == basis_set.at(5));

    // Monomer 1 in dimer 0 basis
    auto [str4, c4, basis4, sys4] = inputs[4];
    REQUIRE(str4 == "1-0_1");
    REQUIRE(c4 == -1.0);
    REQUIRE(sys4 == fragments.at(1));
    REQUIRE(basis4.size() == 6);
    REQUIRE(basis4.at(0) == basis_set.at(0));
    REQUIRE(basis4.at(1) == basis_set.at(1));
    REQUIRE(basis4.at(2) == basis_set.at(2));
    REQUIRE(basis4.at(3) == basis_set.at(3));
    REQUIRE(basis4.at(4) == basis_set.at(4));
    REQUIRE(basis4.at(5) == basis_set.at(5));

    // Dimer 0 in dimer 0 basis
    auto [str5, c5, basis5, sys5] = inputs[5];
    REQUIRE(str5 == "0_1-0_1");
    REQUIRE(c5 == 1.0);
    REQUIRE(sys5 == fragments.concatenate({0, 1}));
    REQUIRE(basis5.size() == 6);
    REQUIRE(basis5.at(0) == basis_set.at(0));
    REQUIRE(basis5.at(1) == basis_set.at(1));
    REQUIRE(basis5.at(2) == basis_set.at(2));
    REQUIRE(basis5.at(3) == basis_set.at(3));
    REQUIRE(basis5.at(4) == basis_set.at(4));
    REQUIRE(basis5.at(5) == basis_set.at(5));

    // Monomer 0 in dimer 1 basis
    auto [str6, c6, basis6, sys6] = inputs[6];
    REQUIRE(str6 == "0-0_2");
    REQUIRE(c6 == -1.0);
    REQUIRE(sys6 == fragments.at(0));
    REQUIRE(basis6.size() == 6);
    REQUIRE(basis6.at(0) == basis_set.at(0));
    REQUIRE(basis6.at(1) == basis_set.at(1));
    REQUIRE(basis6.at(2) == basis_set.at(2));
    REQUIRE(basis6.at(3) == basis_set.at(6));
    REQUIRE(basis6.at(4) == basis_set.at(7));
    REQUIRE(basis6.at(5) == basis_set.at(8));

    // Monomer 2 in dimer 1 basis
    auto [str7, c7, basis7, sys7] = inputs[7];
    REQUIRE(str7 == "2-0_2");
    REQUIRE(c7 == -1.0);
    REQUIRE(sys7 == fragments.at(2));
    REQUIRE(basis7.size() == 6);
    REQUIRE(basis7.at(0) == basis_set.at(0));
    REQUIRE(basis7.at(1) == basis_set.at(1));
    REQUIRE(basis7.at(2) == basis_set.at(2));
    REQUIRE(basis7.at(3) == basis_set.at(6));
    REQUIRE(basis7.at(4) == basis_set.at(7));
    REQUIRE(basis7.at(5) == basis_set.at(8));

    // Dimer 1 in dimer 1 basis
    auto [str8, c8, basis8, sys8] = inputs[8];
    REQUIRE(str8 == "0_2-0_2");
    REQUIRE(c8 == 1.0);
    REQUIRE(sys8 == fragments.concatenate({0, 2}));
    REQUIRE(basis8.size() == 6);
    REQUIRE(basis8.at(0) == basis_set.at(0));
    REQUIRE(basis8.at(1) == basis_set.at(1));
    REQUIRE(basis8.at(2) == basis_set.at(2));
    REQUIRE(basis8.at(3) == basis_set.at(6));
    REQUIRE(basis8.at(4) == basis_set.at(7));
    REQUIRE(basis8.at(5) == basis_set.at(8));

    // Monomer 1 in dimer 2 basis
    auto [str9, c9, basis9, sys9] = inputs[9];
    REQUIRE(str9 == "1-1_2");
    REQUIRE(c9 == -1.0);
    REQUIRE(sys9 == fragments.at(1));
    REQUIRE(basis9.size() == 6);
    REQUIRE(basis9.at(0) == basis_set.at(3));
    REQUIRE(basis9.at(1) == basis_set.at(4));
    REQUIRE(basis9.at(2) == basis_set.at(5));
    REQUIRE(basis9.at(3) == basis_set.at(6));
    REQUIRE(basis9.at(4) == basis_set.at(7));
    REQUIRE(basis9.at(5) == basis_set.at(8));

    // Monomer 2 in dimer 2 basis
    auto [str10, c10, basis10, sys10] = inputs[10];
    REQUIRE(str10 == "2-1_2");
    REQUIRE(c10 == -1.0);
    REQUIRE(sys10 == fragments.at(2));
    REQUIRE(basis10.size() == 6);
    REQUIRE(basis10.at(0) == basis_set.at(3));
    REQUIRE(basis10.at(1) == basis_set.at(4));
    REQUIRE(basis10.at(2) == basis_set.at(5));
    REQUIRE(basis10.at(3) == basis_set.at(6));
    REQUIRE(basis10.at(4) == basis_set.at(7));
    REQUIRE(basis10.at(5) == basis_set.at(8));

    // Dimer 2 in dimer 2 basis
    auto [str11, c11, basis11, sys11] = inputs[11];
    REQUIRE(str11 == "1_2-1_2");
    REQUIRE(c11 == 1.0);
    REQUIRE(sys11 == fragments.concatenate({1, 2}));
    REQUIRE(basis11.size() == 6);
    REQUIRE(basis11.at(0) == basis_set.at(3));
    REQUIRE(basis11.at(1) == basis_set.at(4));
    REQUIRE(basis11.at(2) == basis_set.at(5));
    REQUIRE(basis11.at(3) == basis_set.at(6));
    REQUIRE(basis11.at(4) == basis_set.at(7));
    REQUIRE(basis11.at(5) == basis_set.at(8));
}

template<typename T, typename U, typename V>
void check_trimer_bs(T&& fragments, U&& basis_set, V&& inputs) {
    // Monomer 0 in trimer 0 basis
    auto [str0, c0, basis0, sys0] = inputs[12];
    REQUIRE(str0 == "0-0_1_2");
    REQUIRE(c0 == 1.0);
    REQUIRE(sys0 == fragments.at(0));
    REQUIRE(basis0 == basis_set);

    // Monomer 1 in trimer 0 basis
    auto [str1, c1, basis1, sys1] = inputs[13];
    REQUIRE(str1 == "1-0_1_2");
    REQUIRE(c1 == 1.0);
    REQUIRE(sys1 == fragments.at(1));
    REQUIRE(basis1 == basis_set);

    // Monomer 2 in trimer 0 basis
    auto [str2, c2, basis2, sys2] = inputs[14];
    REQUIRE(str2 == "2-0_1_2");
    REQUIRE(c2 == 1.0);
    REQUIRE(sys2 == fragments.at(2));
    REQUIRE(basis2 == basis_set);

    // Dimer 0 in trimer 0 basis
    auto [str3, c3, basis3, sys3] = inputs[15];
    REQUIRE(str3 == "0_1-0_1_2");
    REQUIRE(c3 == -1.0);
    REQUIRE(sys3 == fragments.concatenate({0, 1}));
    REQUIRE(basis3 == basis_set);

    // Dimer 1 in trimer 0 basis
    auto [str4, c4, basis4, sys4] = inputs[16];
    REQUIRE(str4 == "0_2-0_1_2");
    REQUIRE(c4 == -1.0);
    REQUIRE(sys4 == fragments.concatenate({0, 2}));
    REQUIRE(basis4 == basis_set);

    // Dimer 2 in trimer 0 basis
    auto [str5, c5, basis5, sys5] = inputs[17];
    REQUIRE(str5 == "1_2-0_1_2");
    REQUIRE(c5 == -1.0);
    REQUIRE(sys5 == fragments.concatenate({1, 2}));
    REQUIRE(basis5 == basis_set);

    // Trimer 0 in trimer 0 basis
    auto [str6, c6, basis6, sys6] = inputs[18];
    REQUIRE(str6 == "0_1_2-0_1_2");
    REQUIRE(c6 == 1.0);
    REQUIRE(sys6 == fragments.concatenate({0, 1, 2}));
    REQUIRE(basis6 == basis_set);
}

TEST_CASE("build_vmfc_ao_energy_inputs") {
    // Create a simple chemical system and basis set
    auto mol       = testing::water(3);
    auto basis_set = testing::water_sto3g(mol);
    chemist::ChemicalSystem system(std::move(mol));

    // Fragment the system into two waters
    fragmented_molecule frag_mol(testing::water_fragmented_nuclei(3), 0, 1);
    fragmented_chemical_system fragments(frag_mol);

    // Map basis functions to atoms
    auto bf_map = map_atomic_bases_to_atoms(system, basis_set);

    SECTION("n == 1") {
        auto inputs =
          build_vmfc_ao_energy_inputs(1, basis_set, fragments, bf_map);

        REQUIRE(inputs.size() == 3);
        check_monomer_bs(fragments, basis_set, inputs);
    }

    SECTION("n == 2") {
        auto inputs =
          build_vmfc_ao_energy_inputs(2, basis_set, fragments, bf_map);

        REQUIRE(inputs.size() == 12);
        check_monomer_bs(fragments, basis_set, inputs);
        check_dimer_bs(fragments, basis_set, inputs);
    }

    SECTION("n == 3") {
        auto inputs =
          build_vmfc_ao_energy_inputs(3, basis_set, fragments, bf_map);

        REQUIRE(inputs.size() == 19);
        check_monomer_bs(fragments, basis_set, inputs);
        check_dimer_bs(fragments, basis_set, inputs);
        check_trimer_bs(fragments, basis_set, inputs);
    }
}