#pragma once
#include <ghostfragment/types.hpp>
#include <simde/simde.hpp>
#include <vector>

namespace ghostfragment::drivers {

/** @brief Assigns each atomic basis to the atom closest to the center.
 *
 *  @param[in] system The chemical system to map the AOs to.
 *  @param[in] basis_set The AO basis set to map.
 *
 *  @return A vector such that the i-th element is a vector containing the
 *          indices of the atomic bases assigned to the i-th atom.
 */
std::vector<std::vector<std::size_t>> map_atomic_bases_to_atoms(
  const simde::type::chemical_system& system,
  const simde::type::ao_basis_set& basis_set);

/** @brief Creates a new basis set with the specified centers.
 *
 *  @param[in] full_basis The full basis set to extract from.
 *  @param[in] bf_indices The indices of the centers to include in the new basis
 *                        set.
 */
simde::type::ao_basis_set make_sub_basis_set(
  const simde::type::ao_basis_set& full_basis,
  const std::vector<std::size_t>& bf_indices);

using ao_energy_input_t =
  std::tuple<double, simde::type::ao_basis_set,
             chemist::ChemicalSystemView<const simde::type::chemical_system>>;

std::vector<ao_energy_input_t> build_vmfc_ao_energy_inputs(
  std::size_t n, const simde::type::ao_basis_set& full_basis,
  const type::fragmented_chemical_system& fragments,
  const std::vector<std::vector<std::size_t>>& bf_map);

} // namespace ghostfragment::drivers