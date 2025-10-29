#pragma once
#include <simde/simde.hpp>
#include <vector>

namespace ghostfragment::drivers {

std::vector<std::vector<std::size_t>> map_basis_functions_to_atoms(
    const simde::type::chemical_system& system,
    const simde::type::ao_basis_set& basis_set);

}