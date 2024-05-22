#include "../topology/covalent_radius.hpp"
#include "capping.hpp"
#include <ghostfragment/property_types/fragmenting/capped_fragments.hpp>
#include <ghostfragment/property_types/topology/connectivity_table.hpp>

namespace ghostfragment::capping {

using my_pt                  = ghostfragment::pt::CappedFragments;
using connect_pt             = ghostfragment::pt::ConnectivityTable;
using traits_t               = ghostfragment::pt::CappedFragmentsTraits;
using connect_t              = ghostfragment::pt::ConnectivityTableTraits;
using conns_type             = typename connect_t::result_type;
using nuclei_type            = typename traits_t::result_type::value_type;
using const_nuclei_reference = typename traits_t::result_type::const_reference;
using nucleus_type           = typename nuclei_type::value_type;
using molecule_type          = typename connect_t::input_type;
using charge_type            = typename molecule_type::charge_type;
using multiplicity_type      = typename molecule_type::multiplicity_type;
using distance_type          = double;

// Computes the average X-C bond length in the molecule, where X is in
// the fragment and C is the cap. Takes in Nuclei m, and the atomic
// numbers of X and C.
distance_type average_bond_length(const_nuclei_reference m,
                                  const conns_type& connections,
                                  std::size_t z_x, std::size_t z_c) {
    int existing_bonds         = 0;
    distance_type bond_lengths = 0;
    distance_type ave_length   = 0;
    for(size_t atom_k = 0; atom_k < m.size(); ++atom_k) {
        if(m[atom_k].Z() == z_x) {
            for(size_t atom_l : connections.bonded_atoms(atom_k)) {
                if(m[atom_l].Z() == z_c) {
                    bond_lengths +=
                      (m[atom_l].as_nucleus() - m[atom_k].as_nucleus())
                        .magnitude();
                    existing_bonds++;
                }
            }
        }
    }
    // If no bonds, defaults to standard distance
    if(existing_bonds == 0) {
        ave_length =
          topology::covalent_radius(z_x) + topology::covalent_radius(z_c);
    }
    // If bonds exist, return their average length
    if(existing_bonds > 0) { ave_length = bond_lengths / existing_bonds; }
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

const auto cap_key    = "capping atom";
const auto charge_key = "charge for supersystem";
const auto mult_key   = "multiplicity for supersystem";
} // end namespace

MODULE_CTOR(DCLC) {
    description(module_desc);
    satisfies_property_type<my_pt>();

    add_submodule<connect_pt>("Connectivity");

    add_input<nucleus_type>(cap_key)
      .set_description("atom to use as the cap")
      .set_default(nucleus_type{"H", 1ul, 1837.289, 0.0, 0.0, 0.0});

    add_input<charge_type>(charge_key).set_default(charge_type{0});
    add_input<multiplicity_type>(mult_key).set_default(multiplicity_type{1});
}

MODULE_RUN(DCLC) {
    using size_type = typename nucleus_type::atomic_number_type;
    using bond_type = std::pair<size_type, size_type>;
    using frag_type = typename traits_t::result_type;
    using cap_type  = typename frag_type::cap_set_type::value_type;

    auto&& [frags, broken_bonds] = my_pt::unwrap_inputs(inputs);
    auto cap                     = inputs.at(cap_key).value<nucleus_type>();
    auto charge                  = inputs.at(charge_key).value<charge_type>();
    auto mult = inputs.at(mult_key).value<multiplicity_type>();

    std::map<bond_type, distance_type> found_bonds;

    // Step 1. Generate atomic connectivity
    auto mol = frags.supersystem();

    // We assume charge and multiplicity don't matter too much, but do allow the
    // user to set them if they want...
    chemist::Molecule temp(charge, mult, mol.as_nuclei());
    const auto& conns = submods.at("Connectivity").run_as<connect_pt>(temp);

    // Step 2. Make the caps
    const auto cap_Z = cap.Z();
    for(const auto& [atom_i, atom_j] : broken_bonds) {
        auto Zi             = mol[atom_i].Z();
        auto Zs             = std::make_pair(Zi, cap_Z);
        const auto has_pair = found_bonds.count(Zs);

        if(!has_pair)
            found_bonds[Zs] = average_bond_length(mol, conns, Zi, cap_Z);

        const auto ni      = mol[atom_i].as_nucleus();
        const auto nj      = mol[atom_j].as_nucleus();
        auto original_bond = (ni - nj).magnitude();
        const auto r0      = found_bonds[Zs];

        nucleus_type new_cap(cap);
        for(size_type i = 0; i < 3; ++i) {
            const auto qi    = ni.coord(i);
            const auto dq    = nj.coord(i) - qi;
            new_cap.coord(i) = qi + dq * (r0 / original_bond);
        }

        // Add the cap to the set of caps for this fragment
        frags.add_cap(cap_type(atom_i, atom_j, new_cap));
    }

    auto rv = results();
    return my_pt::wrap_results(rv, frags);
}
} // namespace ghostfragment::capping
