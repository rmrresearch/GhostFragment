#include "connectivity.hpp"
#include <ghostfragment/property_types/broken_bonds.hpp>
#include <ghostfragment/property_types/connectivity_table.hpp>
#include <ghostfragment/property_types/molecular_graph.hpp>
#include <simde/simde.hpp>

namespace ghostfragment::connectivity {

using my_pt   = ghostfragment::pt::BrokenBonds;
using conn_pt = ghostfragment::ConnectivityTable;
// using conn_pt  = ghostfragment::ConnectivityTable;

const auto module_desc = R"(
Broken Bonds from Fragmented Nuclei
----------------------------------------

This module takes as input a set of disjoint fragments. Then using the molecular graph 
of the parent molecular system it determines the bonds that were broken between the
fragments.
)";

MODULE_CTOR(BrokenBonds) {
    satisfies_property_type<my_pt>();
    add_submodule<conn_pt>("Atomic connectivity");
}

MODULE_RUN(BrokenBonds) {
    using traits_type = pt::BrokenBondsTraits;
    using bond_type   = traits_type::bond_type;
    using set_type    = traits_type::bond_set;
    using result_type = traits_type::result_type;

    const auto& [frags] = my_pt::unwrap_inputs(inputs);

    result_type bonds;

    auto& conn_mod         = submods.at("Atomic connectivity");
    const auto& atom_conns = conn_mod.run_as<conn_pt>(frags.supersystem());

    // Looks at each fragment
    for(std::size_t i = 0; i < frags.size(); i++) {
        // The set of bonds for a specific fragment
        set_type frag_set;
        const auto nukes = frags[i];

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
                        frag_set.insert(broken);
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
                        frag_set.insert(broken);
                    }
                }
            }
        }

        // Adding the fragment's set of broken bonds to the system-wide vector
        bonds.push_back(frag_set);
    }

    // Returning the results
    auto rv = results();
    return my_pt::wrap_results(rv, bonds);
}

} // namespace ghostfragment::connectivity
