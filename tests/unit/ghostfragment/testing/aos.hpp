#pragma once
#include "sto3g.hpp"
#include <ghostfragment/detail_/fragmented_system_pimpl.hpp>

namespace testing {

// Assigns AOs to nuclei assuming nuclei order is same as AO center order
inline auto atom_to_ao(const simde::type::molecule& mol) {
    using pimpl_type  = ghostfragment::detail_::FragmentedSystemPIMPL;
    using return_type = pimpl_type::idx2ao_map_type;
    return_type atom2aos;
    auto aos = sto3g(mol);
    ghostfragment::type::fragmented_aos ao_sets(aos);
    for(std::size_t atom_i = 0; atom_i < mol.size(); ++atom_i) {
        auto ao_set = ao_sets.new_subset();
        ao_set.insert(atom_i);
        atom2aos.emplace_back(ao_set);
    }
    return atom2aos;
}

} // namespace testing
