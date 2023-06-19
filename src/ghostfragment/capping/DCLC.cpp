#include "capping.hpp"
#include <ghostfragment/property_types/capped.hpp>
#include <ghostfragment/property_types/connectivity_table.hpp>
#include <src/ghostfragment/connectivity/connectivity.hpp>

namespace ghostfragment::capping {

using my_pt      = ghostfragment::pt::Capped;
using connect_pt = ghostfragment::ConnectivityTable;
using traits_t   = ghostfragment::pt::CappedTraits;
using atom_type  = traits_t::result_type::value_type::atom_type;


// Computes the average X-C bond length in the molecule, where X is in
// the fragment and C is the cap. Takes in Nuclei m, and the atomic
// numbers of X and C.
double average_bond_length(chemist::Nuclei m,
const chemist::topology::ConnectivityTable& connections,
std::size_t z_x, std::size_t z_c){
    int existing_bonds = 0;
    double bond_lengths = 0;
    double ave_length = 0;
    for(size_t atom_k = 0; atom_k < m.size(); ++atom_k){
        if(m[atom_k].Z() == z_x){
            for(size_t atom_l : connections.bonded_atoms(atom_k)){
                if(m[atom_l].Z() == z_c){
                    bond_lengths += (m[atom_l].as_nucleus()
                    - m[atom_k].as_nucleus()).magnitude();
                    existing_bonds ++;
                }
            }
        }
    }
    // If no bonds, defaults to standard distance
    if(existing_bonds == 0){
        ave_length =
            ghostfragment::connectivity::covalent_radius(z_x) 
            + ghostfragment::connectivity::covalent_radius(z_c);
    }
    // If bonds exist, return their average length
    if(existing_bonds > 0){
        ave_length = bond_lengths/existing_bonds;
    }
    return ave_length;
}

namespace {
constexpr auto module_desc = R"""(
##################
DCLC Capper
##################

This module closes off the valencies of the input fragments using single
atoms. More specifically for each bond A-B, such that atom A is in the
fragment, and atom B is not, an atom (default is a hydrogen atom) will be
added to the fragment. The new atom will be placed at a distance determined
by the average A-X bond in the molecule, where X is the capping atom. If no
such bonds exist, then the bond distance is given by the length of the typical
A-X bond (i.e. the sum of the atoms' respective covalent radii).

The inputs to this module are fragments. In general these inputs are
non-disjoint, for this reason we choose to establish connectivity at an
atomic level.

#. Generate atomic connectivity
#. Determine caps we need
#. Pair each fragment with its set of caps

)""";
} // end namespace

MODULE_CTOR(DCLC) {
    satisfies_property_type<my_pt>();

    add_submodule<connect_pt>("Connectivity");

    add_input<atom_type>("capping atom")
      .set_description("atom to use as the cap")
      .set_default(atom_type{"H", 1ul, 1837.289, 0.0, 0.0, 0.0});
}

MODULE_RUN(DCLC) {
    const auto& [frags]    = my_pt::unwrap_inputs(inputs);
    auto cap               = inputs.at("capping atom").value<atom_type>();
    float bond_length      = 0;
    float existing_bonds   = 0;
    float original_bond    = 0;

    // Step 1. Generate atomic connectivity
    const auto& mol   = frags.supersystem();
    const auto& conns = submods.at("Connectivity").run_as<connect_pt>(mol);

    // Step 2. Make the caps
    using result_type  = traits_t::result_type;
    using cap_set_type = typename result_type::value_type;

    result_type capped_frags; // Will be the result
    for(const auto& frag_i : frags) {
        cap_set_type caps_i; // Will be the set of caps for this fragment
        for(const auto& atom_i : frag_i) {
            // Loop over atoms bonded to atom_i
            for(const auto& atom_j : conns.bonded_atoms(atom_i)) {
                // Check if atom_j is in the fragment, if so no cap is needed
                if(frag_i.count(mol[atom_j])) continue;

                // Make the cap
                atom_type new_cap(cap);
                original_bond = (mol[atom_i].as_nucleus()
                - mol[atom_j].as_nucleus()).magnitude();
                for(atom_type::size_type i = 0; i < 3; ++i){
                    new_cap.coord(i) = mol[atom_i].coord(i)
                    + (mol[atom_j].coord(i) - mol[atom_i].coord(i))
                    * average_bond_length(mol, conns, mol[atom_i].Z(),
                    inputs.at("capping atom").value<atom_type>().Z())
                    / original_bond;
                }

                // Add the cap to the set of caps for this fragment
                caps_i.add_cap(atom_i, atom_j, new_cap);
            }
        }
        capped_frags.emplace_back(std::move(caps_i));
    }

    auto rv = results();
    return my_pt::wrap_results(rv, capped_frags);
}
} // namespace ghostfragment::capping