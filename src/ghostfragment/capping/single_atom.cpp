#include "capping.hpp"
#include <ghostfragment/property_types/capped.hpp>
#include <ghostfragment/property_types/connectivity_table.hpp>

using my_pt      = ghostfragment::pt::Capped;
using connect_pt = ghostfragment::ConnectivityTable;
using traits_t   = ghostfragment::pt::CappedTraits;
using atom_type  = traits_t::result_type::value_type::atom_type;

namespace ghostfragment::capping {

namespace {
constexpr auto module_desc = R"""(
##################
Single Atom Capper
##################

This module closes off the valencies of the input fragments using single
atoms. More specifically for each bond A-B, such that atom A is in the
fragment, and atom B is not, an atom (default is a hydrogen atom) will be
added to the fragment. By default the added atom will be placed at the
location of B.

The inputs to this module are fragments. In general these inputs are
non-disjoint, for this reason we choose to establish connectivity at an
atomic level.

#. Generate atomic connectivity
#. Determine caps we need
#. Pair each fragment with its set of caps

)""";
} // end namespace

MODULE_CTOR(SingleAtom) {
    satisfies_property_type<my_pt>();

    add_submodule<connect_pt>("Connectivity");

    add_input<atom_type>("capping atom")
      .set_description("atom to use as the cap")
      .set_default(atom_type{"H", 1ul, 1837.289, 0.0, 0.0, 0.0});
}

MODULE_RUN(SingleAtom) {
    const auto& [frags] = my_pt::unwrap_inputs(inputs);
    auto cap            = inputs.at("capping atom").value<atom_type>();

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
                for(atom_type::size_type i = 0; i < 3; ++i)
                    new_cap.coord(i) = mol[atom_j].coord(i);

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
