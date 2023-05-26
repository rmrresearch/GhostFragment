// #include "capping.hpp"
// #include <ghostfragment/property_types/capped.hpp>

// using my_pt      = ghostfragment::pt::CappedFragments;
// using connect_pt = simde::Connectivity;
// using traits_t   = ghostfragment::pt::CappedFragmentsTraits;

// namespace ghostfragment::capping {
// namespace {
// constexpr auto module_desc = R"""(
// ##################
// Single Atom Capper
// ##################

// This module closes off the valencies of the input fragments using single
// atoms. More specifically for each bond A-B, such that atom A is in the
// fragment, and atom B is not, an atom (default is a hydrogen atom) will be
// added to the fragment. By default the added atom will be placed at the
// location of B.

// The inputs to this module are fragments. In general these inputs are
// non-disjoint, for this reason we choose to establish connectivity at an
// atomic level.

// #. Generate atomic connectivity
// #. Determine caps we need
// #. Pair each fragment with its set of caps

// )""";
// }

// MODULE_CTOR(SingleAtom) {
//     satisfies_property_type<my_pt>();

//     add_submodule<connect_pt>("Connectivity");

//     add_input<std::size_t>("Z")
//       .set_description("Atomic number to use for cap")
//       .set_default(1ul);
// }

// MODULE_RUN(SingleAtom) {
//     // using return_t      = typename traits_t::result_type;
//     // const auto& [frags] = my_pt::unwrap_inputs(inputs);
//     // auto Z              = inputs.at("Z").value<std::size_t>();

//     // // Step 1. Generate atomic connectivity
//     // const auto& mol   = frags.object();
//     // const auto& conns =
//     submods.at("Connectivity").run_as<connect_pt>(mol);

//     // // Step 2. Make the caps
//     // Caps all_the_caps;
//     // using cap_type       = typename Caps::value_type;
//     // using cap_index_type = typename Caps::size_type;
//     // std::map<std::size_t, cap_index_type>
//     //   cap2idx;                                    // map from a cap to its
//     index
//     // std::vector<std::set<std::size_t>> frag2caps; // Cap indices for each
//     frag

//     // for(const auto& frag_i : frags) {
//     //     std::set<std::size_t> caps_i; // Will be the set of caps for this
//     frag
//     //     for(const auto& atom_i : frag_i) {
//     //         // Loop over atoms bonded to atom_i
//     //         for(const auto& atom_j : conns.bonded_atoms(atom_i)) {
//     //             // Check if atom_j is in the fragment, if so no cap is
//     needed
//     //             if(frag_i.count(mol[atom_j])) continue;

//     //             // Have we added this cap to all_the_caps? If not add it
//     //             if(!cap2idx.count(atom_j)) {
//     //                 auto new_cap   = mol[atom_j];
//     //                 new_cap.Z()    = Z;
//     //                 new_cap.name() = "H";
//     //                 all_the_caps.add_cap(new_cap, atom_j);
//     //                 cap2idx.emplace(atom_j, all_the_caps.size() - 1);
//     //             }

//     //             // Add the cap to the set of caps for this fragment
//     //             caps_i.insert(cap2idx.at(atom_j));
//     //         }
//     //     }
//     //     frag2caps.push_back(caps_i);
//     // }

//     // // Step 3. Pair frags with their cap sets
//     // type::fragmented_caps caps(all_the_caps);
//     // return_t capped_frags;
//     // for(std::size_t i = 0; i < frags.size(); ++i) {
//     //     // Make a subset of all_the_caps containing fragment i's caps
//     //     auto caps4i = caps.new_subset();
//     //     for(auto cap_i : frag2caps[i]) { caps4i.insert(cap_i); }

//     //     // Pair fragment i with its caps
//     //     capped_frags.emplace(frags[i], caps4i);
//     // }

//     // auto rv = results();
//     // return my_pt::wrap_results(rv, capped_frags);
// }
// } // namespace ghostfragment::capping
