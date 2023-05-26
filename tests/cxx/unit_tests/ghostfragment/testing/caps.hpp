// #pragma once
// #include "fragment.hpp"
// #include <ghostfragment/property_types/capped.hpp>

// namespace testing {

// // This just makes the full set of caps for a water cluster (doesn't assign)
// inline auto caps_for_water(std::size_t n_waters) {
//     ghostfragment::Caps caps;
//     ghostfragment::type::fragmented_caps no_caps(caps);
//     if(n_waters == 0) return no_caps;
//     auto empty_set = no_caps.new_subset();
//     no_caps.insert(empty_set);
//     return no_caps;
// }

// // This pairs the caps to their water molecule
// inline auto capped_water(std::size_t n_waters) {
//     auto water_n = fragmented_water(n_waters);
//     auto no_caps = caps_for_water(n_waters);

//     ghostfragment::pt::CappedFragmentsTraits::result_type capped;
//     for(const auto& frag_i : water_n) capped.emplace(frag_i, no_caps[0]);
//     return capped;
// }

// // This just makes the set of caps when the water cluster needs capped
// inline auto caps_for_water_needing_caps(std::size_t n_waters) {
//     using atom_type = typename ghostfragment::type::nuclei_set::value_type;

//     ghostfragment::Caps all_the_caps;
//     const auto mol = water(n_waters);
//     for(size_t i = 0; i < n_waters; ++i) {
//         // Cap replacing the 2nd H
//         atom_type h("H", 1ul, mol[i * 3 + 2].coords());
//         // Cap replacing the O
//         atom_type o("H", 1ul, mol[i * 3].coords());
//         all_the_caps.add_cap(h, i * 3 + 2);
//         all_the_caps.add_cap(o, i * 3);
//     }
//     ghostfragment::type::fragmented_caps caps(all_the_caps);
//     for(std::size_t cap_i = 0; cap_i < all_the_caps.size(); ++cap_i) {
//         auto subset = caps.new_subset();
//         subset.insert(cap_i);
//         caps.insert(subset);
//     }
//     return caps;
// }

// // Caps waters when fragmented (OH) (H). Results: (OHH) (HH)
// inline auto capped_water_needing_caps(std::size_t n_waters) {
//     using capped_type =
//     ghostfragment::pt::CappedFragmentsTraits::result_type;

//     auto frags      = fragmented_water_needing_caps(n_waters);
//     const auto N    = frags.size();
//     const auto caps = caps_for_water_needing_caps(n_waters);

//     capped_type capped;
//     for(std::size_t i = 0; i < N; ++i) { capped.emplace(frags[i], caps[i]); }
//     return capped;
// }
// } // namespace testing
