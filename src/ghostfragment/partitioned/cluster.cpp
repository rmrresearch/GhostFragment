#include "ghostfragment/types.hpp"
#include "partitioned.hpp"
#include <simde/simde.hpp>

namespace ghostfragment::partitioned {
namespace detail_ {

using bond_list_t = typename simde::type::connectivity_table::bond_list_type;
using atom_t      = typename bond_list_t::size_type;

/* The top call to this function provides us with a set `{x}`. Where `x` is one
 * integer. In that top call we loop over the bonds, `{y,z}` and we add
 * `{y,z}` to the set if either `y` or `z` is in the set already. Realizing that
 * the bonds are lexicographically ordered this means that the first loop will
 * add all connections `a,x` where `a<x` and `x,b` where `b>x`. This
 * successfully adds all bonds involving `x`. Once we find `a` and `b` they
 * will also be considered for comparison to `{y,z}`, which means we also will
 * end up adding all bonds: `a,c` where `c>x`, `d,b` where `d>x`, and `b,e`
 * where `e>b` (we also can end up finding bonds involving `c`, `d`, and `e`, as
 * well as the atoms connected to those bonds, but enumerating thses additional
 * bonds gets complicated fast). The point is that one cycle through bonds is
 * not sufficient as we could have missed bonds. Minimally we could have missed
 * bonds `f,a` and `g,b` where `f<a` and `g<x`, but there's also a ton of bonds
 * we could have missed involving `c`, `d`, `e` and the atoms bonded to them. By
 * looping again we grab the bonds we missed in the first loop, but may end up
 * missing bonds involving atoms found in the current loop. We thus keep looping
 * until the set of atoms that comes in is the same as the set of atoms we find.
 */
auto assign_bonds(const bond_list_t& bonds, const std::set<atom_t>& atoms) {
    std::set<atom_t> new_atoms(atoms);
    for(const auto& [i, j] : bonds) {
        if(new_atoms.count(i) || new_atoms.count(j)) {
            new_atoms.insert(i);
            new_atoms.insert(j);
        }
    }
    // Done iterating if we didn't find new atoms
    if(new_atoms == atoms) return new_atoms;
    // if we found new atoms need to iterate again
    return assign_bonds(bonds, new_atoms);
}

} // namespace detail_

const auto mod_desc = R"(
Cluster Partitioner
-------------------

This module partitions the input molecular system by walking the connectivity 
table and assigning all atoms that are bonded together into a single partition.
The end result is that if the input is a cluster of molecules, each molecule is
assigned to its own partition. If the input is a single molecule the result is a
single partition. And if there are zero atoms in the input molecular system you
get back zero partitions.

Atoms are assigned to partitions in input order. Meaning within a partition atom
``i`` will come before atom ``j` if atom ``i`` was declared in the supersystem
before atom ``j``.
)";

using pt = simde::FragmentedMolecule;

MODULE_CTOR(Cluster) {
    description(mod_desc);
    satisfies_property_type<pt>();

    add_submodule<simde::Connectivity>("Connectivity")
      .set_description("Determines the input system's connectivity.");
}

MODULE_RUN(Cluster) {
    using subset_type = typename type::fragmented_molecule::value_type;
    const auto& [mol] = pt::unwrap_inputs(inputs);
    const auto natoms = mol.size();

    type::fragmented_molecule frags(mol); // Will be the fragments

    // Handle zero atom edge-case
    if(natoms == 0) {
        auto rv = results();
        return pt::wrap_results(rv, frags);
    }

    auto& ctable_mod     = submods.at("Connectivity");
    const auto& [ctable] = ctable_mod.run_as<simde::Connectivity>(mol);

    using size_type = typename std::decay_t<decltype(ctable)>::size_type;
    std::map<type::tag, std::set<size_type>> atom2frag;

    // We know we have at least one atom so seed atom 0 to fragment 0
    type::tag curr_tag = "0";
    std::vector<bool> seen(natoms, false); // Ensures all atoms get assigned
    const auto& bonds = ctable.bonds();
    for(size_type i = 0; i < natoms; ++i) {
        if(seen[i]) continue;
        std::set<size_type> seed{i};
        atom2frag[curr_tag] = detail_::assign_bonds(bonds, seed);
        for(auto x : atom2frag[curr_tag]) seen[x] = true;
        curr_tag = std::to_string(atom2frag.size());
    }

    for(const auto& [tag, atoms] : atom2frag) {
        subset_type new_mol(frags.data());
        for(auto i : atoms) new_mol.insert(i);
        frags.insert(new_mol);
    }

    auto rv = results();
    return pt::wrap_results(rv, frags);
}

} // namespace ghostfragment::partitioned