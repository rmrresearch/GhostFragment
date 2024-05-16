// #include "capping.hpp"
// #include <src/ghostfragment/connectivity/connectivity.hpp>
// #include <ghostfragment/property_types/capped.hpp>
// #include <ghostfragment/property_types/connectivity_table.hpp>
// #include <ghostfragment/property_types/broken_bonds.hpp>

// using my_pt      = ghostfragment::pt::Capped;
// using bonds_pt = ghostfragment::pt::BrokenBonds;
// using traits_t   = ghostfragment::pt::CappedTraits;
// using result_type = traits_t::result_type;
// using set_type = result_type::value_type;
// using atom_type  = set_type::atom_type;

// namespace ghostfragment::capping {

// namespace {
// constexpr auto module_desc = R"""(
// ##################
// Weighted Distance Capper
// ##################

// This module closes off the valencies of the input fragments using a hydrogen
// atom at a specific distance. More specifically for each bond A-B, such that atom A is in the
// fragment, and atom B is not, a hydrogen atom will be
// added to the fragment such that the location along the original bond is the ratio
// of a normal A-H bond to a normal A-B bond.

// The inputs to this module are fragments. In general these inputs are
// non-disjoint, for this reason we choose to establish connectivity at an
// atomic level.

// #. Generate atomic connectivity
// #. Determine caps we need
// #. Pair each fragment with its set of caps

// )""";
// } // end namespace

// MODULE_CTOR(WeightedDistance){
//     satisfies_property_type<my_pt>();

//     add_submodule<bonds_pt>("Broken Bonds");
// }

// MODULE_RUN(WeightedDistance){
//     const auto& [frags] = my_pt::unwrap_inputs(inputs);

//     const auto& mol = frags.supersystem();
//     const auto& broken_bonds = submods.at("Broken Bonds").run_as<bonds_pt>(frags);

//     result_type capped_frags;

//     for(auto bond_set : broken_bonds){
//         set_type caps_i;
//         for(auto bonds : bond_set){
//             //Gets the both atoms from the bond
//             const auto& atom_i = mol[bonds.first];
//             const auto& atom_j = mol[bonds.second];

//             //Finds the bond lengths of i-H and i-j
//             auto i_j_bond = ghostfragment::connectivity::covalent_radius(atom_i.Z()) + ghostfragment::connectivity::covalent_radius(atom_j.Z());
//             auto i_h_bond = ghostfragment::connectivity::covalent_radius(atom_i.Z()) + ghostfragment::connectivity::covalent_radius(1);

//             auto ratio = i_h_bond / i_j_bond;

//             atom_type new_cap("H", 1ul, 1837.289, 0.0, 0.0, 0.0);

//             for(auto i = 0; i < 3; i++){
//                 new_cap.coord(i) = (atom_i.coord(i) + ratio * (atom_j.coord(i) - atom_i.coord(i)));
//             }
//             caps_i.add_cap(bonds.first, bonds.second, new_cap);
//         }

//         capped_frags.emplace_back(std::move(caps_i));
//     }

//     auto rv = results();
//     return my_pt::wrap_results(rv, capped_frags);
// }
// }  // namespace ghostfragment::capping
