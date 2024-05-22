#include "capping.hpp"
#include <ghostfragment/property_types/fragmenting/capped_fragments.hpp>

using my_pt        = ghostfragment::pt::CappedFragments;
using traits_type  = ghostfragment::pt::CappedFragmentsTraits;
using frags_type   = typename traits_type::frags_type;
using nucleus_type = typename frags_type::value_type::value_type;

namespace ghostfragment::capping {

namespace {
constexpr auto module_desc = R"""(
##################
Single Atom Capper
##################

This module closes off the valencies of the input fragments using single
nuclei. More specifically for each bond A-B, such that atom A is in the
fragment, and atom B is not, a nucleus (default is a hydrogen nucleus) will be
added to the fragment. By default the added nucleus will be placed at the
location of B.

The inputs to this module are fragments and the . In general these inputs are
non-disjoint, for this reason we choose to establish connectivity at an
atomic level.

#. Generate atomic connectivity
#. Determine caps we need
#. Pair each fragment with its set of caps

)""";
} // end namespace

MODULE_CTOR(SingleAtom) {
    description(module_desc);
    satisfies_property_type<my_pt>();

    add_input<nucleus_type>("capping nucleus")
      .set_description("nucleus to use as the cap")
      .set_default(nucleus_type{"H", 1ul, 1837.289, 0.0, 0.0, 0.0});
}

MODULE_RUN(SingleAtom) {
    using cap_type = typename frags_type::cap_set_type::value_type;

    auto&& [frags, broken_bonds] = my_pt::unwrap_inputs(inputs);
    auto cap = inputs.at("capping nucleus").value<nucleus_type>();

    for(const auto& [atom_i, atom_j] : broken_bonds) {
        // Make the cap
        nucleus_type new_cap(cap);
        for(nucleus_type::size_type j = 0; j < 3; ++j)
            new_cap.coord(j) = frags.supersystem()[atom_j].coord(j);

        // Add the cap to the set of caps for this fragment
        frags.add_cap(cap_type(atom_i, atom_j, new_cap));
    }

    auto rv = results();
    return my_pt::wrap_results(rv, frags);
}
} // namespace ghostfragment::capping
