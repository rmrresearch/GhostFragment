#include "fragmenting.hpp"

#include <ghostfragment/property_types/connectivity_table.hpp>
#include <ghostfragment/type/type.hpp>

namespace ghostfragment::fragmenting {

using frags_pt = simde::FragmentedMolecule;
using conn_pt  = ghostfragment::ConnectivityTable;

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
    using fragmented_molecule = type::fragmented_molecule;
    using size_type           = typename simde::type::molecule::size_type;
    using subset_type         = type::fragmented_molecule::value_type;

    const auto& [mol] = frags_pt::unwrap_inputs(inputs);

    auto& con_mod     = submods.at("Connectivity");
    const auto& conns = con_mod.run_as<conn_pt>(mol.nuclei());

    fragmented_molecule frags(mol);

    std::map<size_type, subset_type> subsets;

    for(size_type atom_i = 0; atom_i < mol.size(); ++atom_i) {
        const auto Zi     = mol[atom_i].Z();
        const auto conn_i = conns.bonded_atoms(atom_i);
        if(Zi > 1) {
            auto ss = frags.new_subset();
            ss.insert(atom_i);

            // Add hydrogens bonded to atom_i to the subset
            for(const auto atom_j : conn_i) {
                const auto Zj = mol[atom_j].Z();
                if(Zj == 1) ss.insert(atom_j);
            }
            subsets.emplace(atom_i, ss);
        } else if(Zi == 1) {
            if(conn_i.size() > 1)
                throw std::runtime_error("Wasn't expecting hydrogen to make "
                                         "more than one bond...");
            if(conn_i.size() == 0) {
                auto ss = frags.new_subset();
                ss.insert(atom_i);
                subsets.emplace(atom_i, ss);
            } else { // size == 1
                const auto atom_j = *conn_i.begin();

                // See if we've dealt with this atom already or it's a heavy
                // atom (in which case we'll deal with it when we get to it).
                if(atom_j < atom_i || (mol[atom_j].Z() > 1)) continue;

                // It's a H-H molecule and we haven't already seen one of the
                // hydrogen atoms in it
                auto ss = frags.new_subset();
                ss.insert(atom_i);
                ss.insert(atom_j);
                subsets.emplace(atom_i, ss);
            }
        } else {
            // I guess it's element zero...
            throw std::runtime_error("What does Z == 0 mean?");
        }
    }
    for(const auto& [_, v] : subsets) frags.insert(v);

    auto rv = results();
    return frags_pt::wrap_results(rv, frags);
}

} // namespace ghostfragment::partitioned
