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

#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/topology/connectivity_table.hpp>
#include <iostream>

namespace ghostfragment::fragmenting {

using frags_pt = pt::FragmentedNuclei;
using conn_pt  = pt::ConnectivityTable;

const auto mod_desc = R"(
Fragmentation by Heavy Atom
---------------------------

For each of the :math:`N` heavy atoms (where a heavy atom is defined as any
atom, but hydrogen), this fragmentation method creates :math:`N` fragments such
that the :math:`i`-th fragment contains the :math:`i`-th heavy atom and all
hydrogens bonded to the :math:`i`-th heavy atom. In the event that there are
hydrogen molecules, (*i.e.*, hydrogen atoms bonded to each other), or lone
hydrogen atoms, those are put into their own fragment.

While theoretically usable as a fragmentation method proper, this module is
largely envisioned as being used as a pseudoatom submodule, or as the first step
in a more involved pseudoatom submodule.

This module will raise an error if there is a hydrogen atom bonded to more than
one other atom.
)";

MODULE_CTOR(HeavyAtom) {
    description(mod_desc);

    satisfies_property_type<frags_pt>();

    add_submodule<conn_pt>("Connectivity");
}

MODULE_RUN(HeavyAtom) {
    using fragmented_nuclei = typename pt::FragmentedNucleiTraits::result_type;
    using size_type         = typename fragmented_nuclei::size_type;
    auto& logger            = get_runtime().logger();

    const auto& [system] = frags_pt::unwrap_inputs(inputs);
    const auto& mol      = system.molecule();

    auto& con_mod     = submods.at("Connectivity");
    const auto& conns = con_mod.run_as<conn_pt>(mol);
    logger.debug("Found " + std::to_string(conns.nbonds()) + " bonds.");

    fragmented_nuclei frags(mol.nuclei().as_nuclei());

    for(size_type atom_i = 0; atom_i < mol.size(); ++atom_i) {
        std::vector<size_type> fragment;
        const auto Zi     = mol[atom_i].Z();
        const auto conn_i = conns.bonded_atoms(atom_i);
        logger.trace("Atom " + std::to_string(atom_i) +
                     " has Z == " + std::to_string(Zi));
        if(Zi > 1) {
            fragment.push_back(atom_i);

            // Add hydrogens bonded to atom_i to the subset
            for(const auto atom_j : conn_i) {
                const auto Zj = mol[atom_j].Z();
                if(Zj == 1) fragment.push_back(atom_j);
            }
            frags.insert(fragment.begin(), fragment.end());
        } else if(Zi == 1) {
            if(conn_i.size() > 1)
                throw std::runtime_error("Wasn't expecting hydrogen to make "
                                         "more than one bond...");
            if(conn_i.size() == 0) {
                fragment.push_back(atom_i);
                frags.insert(fragment.begin(), fragment.end());
            } else { // size == 1
                const auto atom_j = *conn_i.begin();

                // See if we've dealt with this atom already or it's a heavy
                // atom (in which case we'll deal with it when we get to it).
                if(atom_j < atom_i || (mol[atom_j].Z() > 1)) continue;

                // It's a H-H molecule and we haven't already seen one of the
                // hydrogen atoms in it
                fragment.push_back(atom_i);
                fragment.push_back(atom_j);
                frags.insert(fragment.begin(), fragment.end());
            }
        } else {
            // I guess it's element zero...
            throw std::runtime_error("What does Z == 0 mean?");
        }
    }

    auto rv = results();
    return frags_pt::wrap_results(rv, frags);
}

} // namespace ghostfragment::fragmenting
