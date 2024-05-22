#include "topology.hpp"
#include <ghostfragment/property_types/topology/broken_bonds.hpp>
#include <ghostfragment/property_types/topology/connectivity_table.hpp>
#include <ghostfragment/property_types/topology/nuclear_graph.hpp>
#include <simde/simde.hpp>

namespace ghostfragment::topology {

using my_pt       = pt::BrokenBonds;
using traits_type = pt::BrokenBondsTraits;

const auto module_desc = R"(
Broken Bonds from Fragmented Nuclei
----------------------------------------

This module takes as input a set of disjoint fragments and the connectivity of
the supersystem. Using the connectivity of the supersystem it then determines
the bonds that were broken in forming the fragments.
)";

MODULE_CTOR(BrokenBonds) {
    description(module_desc);
    satisfies_property_type<my_pt>();
}

MODULE_RUN(BrokenBonds) {
    using result_type = traits_type::result_type;
    using bond_type   = typename traits_type::bond_type;

    const auto& [frags, atom_conns] = my_pt::unwrap_inputs(inputs);

    result_type bonds;

    // Looks at each fragment
    for(std::size_t i = 0; i < frags.size(); i++) {
        // The set of bonds for a specific fragment
        const auto nukes = frags.nuclear_indices(i);

        // Looks at each nucleus index within the fragment
        for(const auto atom_i : nukes) {
            // Checks to see if the index appears within any of the edges in the
            // molecule graph
            for(const auto existing_bonds : atom_conns.bonds()) {
                // If the index is in the first, that means its pair is bigger
                if(atom_i == existing_bonds[0]) {
                    auto in_current_frag = false;

                    // Checks to see if the pair is already in the fragment
                    for(const auto atom_j : nukes) {
                        if(atom_j == existing_bonds[1]) {
                            in_current_frag = true;
                            break;
                        }
                    }

                    // If the pair is not already in the fragment,
                    // then it is a broken bond and must be added to the set
                    if(!in_current_frag) {
                        bond_type broken(atom_i, existing_bonds[1]);
                        bonds.insert(broken);
                    }
                }

                // If the index is in the second, that means its pair is smaller
                if(atom_i == existing_bonds[1]) {
                    auto in_current_frag = false;

                    // Checks to see if the pair is already in the fragment
                    for(const auto atom_j : nukes) {
                        if(atom_j == existing_bonds[0]) {
                            in_current_frag = true;
                            break;
                        }
                    }

                    // If the pair is not already in the fragment,
                    // then it is a broken bond and must be added to the set
                    if(!in_current_frag) {
                        bond_type broken(atom_i, existing_bonds[0]);
                        bonds.insert(broken);
                    }
                }
            }
        }
    }

    // Returning the results
    auto rv = results();
    return my_pt::wrap_results(rv, bonds);
}

} // namespace ghostfragment::topology
