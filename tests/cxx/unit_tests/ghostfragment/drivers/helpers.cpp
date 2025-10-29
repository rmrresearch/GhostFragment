#include "../test_ghostfragment.hpp"
#include <ghostfragment/drivers/helpers.hpp>

using namespace ghostfragment::drivers;
using int_vector = std::vector<std::size_t>;

TEST_CASE("map_basis_functions_to_atoms") {

    SECTION("One Water"){
        // Create a simple chemical system and basis set
        auto mol = testing::water(1);
        auto basis_set = testing::water_sto3g(mol);
        chemist::ChemicalSystem system(std::move(mol));

        // Map basis functions to atoms
        auto bf_map = map_basis_functions_to_atoms(system, basis_set);

        REQUIRE(bf_map[0] == int_vector{0, 1, 2, 3, 4}); 
        REQUIRE(bf_map[1] == int_vector{5}); 
        REQUIRE(bf_map[2] == int_vector{6}); 
    }

    SECTION("Two Water"){
        // Create a simple chemical system and basis set
        auto mol = testing::water(2);
        auto basis_set = testing::water_sto3g(mol);
        chemist::ChemicalSystem system(std::move(mol));

        // Map basis functions to atoms
        auto bf_map = map_basis_functions_to_atoms(system, basis_set);

        REQUIRE(bf_map[0] == int_vector{0, 1, 2, 3, 4}); 
        REQUIRE(bf_map[1] == int_vector{5}); 
        REQUIRE(bf_map[2] == int_vector{6}); 
        REQUIRE(bf_map[3] == int_vector{7, 8, 9, 10, 11});
        REQUIRE(bf_map[4] == int_vector{12});
        REQUIRE(bf_map[5] == int_vector{13});
    }
}