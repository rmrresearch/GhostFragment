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

#include "../topology/covalent_radius.hpp"
#include "capping.hpp"
#include <ghostfragment/property_types/fragmenting/capped_fragments.hpp>

using my_pt        = ghostfragment::pt::CappedFragments;
using traits_t     = ghostfragment::pt::CappedFragmentsTraits;
using result_type  = traits_t::result_type;
using nucleus_type = typename result_type::value_type::value_type;

namespace ghostfragment::capping {

namespace {
constexpr auto module_desc = R"""(
##################
Weighted Distance Capper
##################

This module closes off the valencies of the input fragments using a hydrogen
atom at a specific distance. More specifically for each bond A-B, such that
atom A is in the
fragment, and atom B is not, a hydrogen atom will be
added to the fragment such that the location along the original bond is the
ratio
of a normal A-H bond to a normal A-B bond.



)""";
} // end namespace

MODULE_CTOR(WeightedDistance) {
    description(module_desc);
    satisfies_property_type<my_pt>();
    add_input<nucleus_type>("capping nucleus")
      .set_description("nucleus to use as the cap")
      .set_default(nucleus_type{"H", 1ul, 1837.289, 0.0, 0.0, 0.0});
}

MODULE_RUN(WeightedDistance) {
    using cap_type = typename result_type::cap_set_type::value_type;

    auto&& [frags, broken_bonds] = my_pt::unwrap_inputs(inputs);
    auto cap = inputs.at("capping nucleus").value<nucleus_type>();

    const auto& mol = frags.supersystem();

    for(const auto& bonds : broken_bonds) {
        // Gets the both atoms from the bond
        const auto& atom_i = mol[bonds.first];
        const auto& atom_j = mol[bonds.second];

        // Finds the bond lengths of i-H and i-j
        auto i_j_bond = topology::covalent_radius(atom_i.Z()) +
                        topology::covalent_radius(atom_j.Z());
        auto i_h_bond = topology::covalent_radius(atom_i.Z()) +
                        topology::covalent_radius(cap.Z());

        auto ratio = i_h_bond / i_j_bond;

        nucleus_type new_cap(cap);

        for(auto i = 0; i < 3; i++) {
            new_cap.coord(i) =
              (atom_i.coord(i) + ratio * (atom_j.coord(i) - atom_i.coord(i)));
        }
        frags.add_cap(cap_type(bonds.first, bonds.second, new_cap));
    }

    auto rv = results();
    return my_pt::wrap_results(rv, frags);
}
} // namespace ghostfragment::capping
