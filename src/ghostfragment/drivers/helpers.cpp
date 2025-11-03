#include "helpers.hpp"
#include <combinations.hpp>
#include <powerset.hpp>

namespace ghostfragment::drivers {

std::vector<std::vector<std::size_t>> map_atomic_bases_to_atoms(
  const simde::type::chemical_system& system,
  const simde::type::ao_basis_set& basis_set) {
    using int_vector = std::vector<std::size_t>;
    auto n_atoms     = system.molecule().size();
    std::vector<int_vector> bf_map(n_atoms);

    for(std::size_t center_i = 0; center_i < basis_set.size(); ++center_i) {
        double distance          = 1e10;
        std::size_t closest_atom = 0;
        const auto& center       = basis_set.at(center_i);
        auto r                   = center.center();
        for(std::size_t atom_idx = 0; atom_idx < n_atoms; ++atom_idx) {
            auto atom_pos           = system.molecule().at(atom_idx).as_point();
            double current_distance = (r.as_point() - atom_pos).magnitude();
            if(current_distance < distance) {
                distance     = current_distance;
                closest_atom = atom_idx;
            }
        }
        bf_map[closest_atom].push_back(center_i);
    }
    return bf_map;
}

simde::type::ao_basis_set make_sub_basis_set(
  const simde::type::ao_basis_set& full_basis,
  const std::vector<std::size_t>& bf_indices) {
    simde::type::ao_basis_set sub_basis;

    for(const auto& idx : bf_indices) {
        sub_basis.add_center(full_basis.at(idx));
    }
    return sub_basis;
}

std::vector<ao_energy_input_t> build_vmfc_ao_energy_inputs(
  std::size_t n, const simde::type::ao_basis_set& full_basis,
  const type::fragmented_chemical_system& fragments,
  const std::vector<std::vector<std::size_t>>& bf_map) {
    const auto& frag_mol = fragments.fragmented_molecule();
    const auto& frag_nuc = frag_mol.fragmented_nuclei();

    // Get the nuclei in each fragment
    std::vector<std::vector<std::size_t>> nuclei_in_fragments(fragments.size());
    for(std::size_t i = 0; i < fragments.size(); ++i)
        nuclei_in_fragments[i] = frag_nuc.nuclear_indices(i);

    // Build a vector holding the numbers [0, n_fragments)
    std::vector<std::size_t> fragment_indices(fragments.size());
    std::iota(fragment_indices.begin(), fragment_indices.end(), 0);

    std::vector<ao_energy_input_t> inputs;

    // TODO: Should use recursion so that m-mer inputs are used to build
    // (m+1)-mer inputs by adding one fragment at a time
    for(std::size_t m = 1; m <= n; ++m) {
        for(auto&& mmer : iter::combinations(fragment_indices, m)) {
            // Get bs functions for mmer
            std::vector<std::size_t> mmer_bf_indices;
            for(auto frag_i : mmer) {
                for(auto nucleus_idx : nuclei_in_fragments.at(frag_i)) {
                    const auto& bf_indices = bf_map.at(nucleus_idx);
                    mmer_bf_indices.insert(mmer_bf_indices.end(),
                                           bf_indices.begin(),
                                           bf_indices.end());
                }
            }
            auto mmber_bs = make_sub_basis_set(full_basis, mmer_bf_indices);
            for(auto&& kmer : iter::powerset(mmer)) {
                if(kmer.empty()) continue;
                std::vector<std::size_t> kmer_nuclei(kmer.begin(), kmer.end());
                auto kmer_system = fragments.concatenate(kmer_nuclei);
                double c         = (kmer.size() % 2 == m % 2) ? 1.0 : -1.0;
                inputs.emplace_back(std::make_tuple(c, mmber_bs, kmer_system));
            }
        }
    }
    return inputs;
}

} // namespace ghostfragment::drivers