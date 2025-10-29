#include "helpers.hpp"

namespace ghostfragment::drivers {

std::vector<std::vector<std::size_t>> map_basis_functions_to_atoms(
    const simde::type::chemical_system& system,
    const simde::type::ao_basis_set& basis_set) {
        using int_vector = std::vector<std::size_t>;
    auto n_atoms = system.molecule().size();
    std::vector<int_vector> bf_map(n_atoms);
    std::size_t counter = 0;

    for(std::size_t center_i = 0; center_i < basis_set.size(); ++center_i) {
        double distance = 1e10;
        std::size_t closest_atom = 0;
        const auto& center = basis_set.at(center_i);
        auto r = center.center();
        for(std::size_t atom_idx = 0; atom_idx < n_atoms; ++atom_idx) {
            auto atom_pos = system.molecule().at(atom_idx).as_point();
            double current_distance = (r.as_point() - atom_pos).magnitude();
            if(current_distance < distance) {
                distance = current_distance;
                closest_atom = atom_idx;
            }
        }
        for(std::size_t i = 0; i < center.n_aos(); ++i) {
            bf_map[closest_atom].push_back(counter++);
        }
    }
    return bf_map;
}

}