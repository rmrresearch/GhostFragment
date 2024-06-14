/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fragmenting.hpp"
#include <ghostfragment/property_types/fragmenting/nuclear_graph_to_fragments.hpp>
#include <simde/simde.hpp>

namespace ghostfragment::fragmenting {

using my_pt       = pt::NuclearGraphToFragments;
using traits_type = pt::NuclearGraphToFragmentsTraits;
using graph_type  = typename traits_type::graph_type;
using frags_type  = typename traits_type::fragment_type;
using edge_list   = typename graph_type::edge_list_type;
using index_type  = typename edge_list::size_type;

namespace detail_ {

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
auto assign_bonds(const edge_list& bonds, const std::set<index_type>& atoms) {
    std::set<index_type> new_atoms(atoms);
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
)";

MODULE_CTOR(Cluster) {
    description(mod_desc);
    satisfies_property_type<my_pt>();
}

MODULE_RUN(Cluster) {
    using nuclei_type = typename graph_type::nuclei_type;

    const auto& [graph] = my_pt::unwrap_inputs(inputs);
    // patoms is short for pseudoatoms
    const auto npatoms = graph.nodes_size();

    // Handle zero patom edge-case
    if(npatoms == 0) {
        auto rv = results();
        return my_pt::wrap_results(rv, frags_type{nuclei_type{}});
    }

    frags_type frags(graph.nuclei().as_nuclei()); // Will be the fragments
    const auto& bonds = graph.edge_list();

    using size_type = typename std::decay_t<decltype(bonds)>::size_type;
    std::vector<std::set<size_type>> patom2frag;

    // We know we have at least one patom so seed patom 0 to fragment 0
    std::vector<bool> seen(npatoms, false); // Ensures all patoms get assigned
    for(size_type i = 0; i < npatoms; ++i) {
        if(seen[i]) continue;
        std::set<size_type> seed{i};
        patom2frag.push_back(detail_::assign_bonds(bonds, seed));
        for(auto x : patom2frag.back()) seen[x] = true;
    }

    for(const auto& patoms : patom2frag) {
        std::vector<typename nuclei_type::const_reference> new_mol;
        for(auto patom_i : patoms)
            for(auto atom_i : graph.node(patom_i)) new_mol.push_back(atom_i);
        frags.insert(new_mol.begin(), new_mol.end());
    }

    auto rv = results();
    return my_pt::wrap_results(rv, frags);
}

} // namespace ghostfragment::fragmenting
