// #include "../connectivity/distance.hpp"
// #include "ghostfragment/property_types/property_types.hpp"
// #include "screening.hpp"
// #include <limits>

// namespace ghostfragment::screening {
// namespace {

// // Finds the minimum distance between an atom in f0 and an atom in f1
// template<typename Set0Type, typename Set1Type>
// auto min_distance(const Set0Type f0, const Set1Type& f1) {
//     double min = std::numeric_limits<double>::max();
//     for(const auto& a0 : f0) { // indices, not atoms, in f0
//         const auto& mol0 = f0.object();
//         for(const auto& a1 : f1) { // indices, not atoms, in f1
//             const auto& mol1 = f1.object();
//             auto r           = detail_::atomic_distance(mol0[a0], mol1[a1]);
//             min              = std::min(min, r);
//         }
//     }
//     return min;
// }

// // Finds minimum distance between an atom in f0 and an atom in f1 and c1
// template<typename SetType, typename FragType, typename CapType>
// auto min_distance(const SetType& f0, const FragType& f1, const CapType& c1) {
//     return std::min(min_distance(f0, f1), min_distance(f0, c1));
// }

// template<typename FragType, typename CapType>
// auto min_distance(const FragType& f0, const CapType& c0, const FragType& f1,
//                   const CapType& c1) {
//     return std::min(min_distance(f0, f1, c1), min_distance(c0, f1, c1));
// }

// } // namespace

// using my_pt = pt::NMerScreener;

// constexpr auto desc = R"""(
// Distance Based Screening
// ------------------------

// Many of the initial NMer screening routines relied on distance based cutoffs
// to select which NMers survived.

// The steps in this module:

// #. Computes the minimum distance between each pair of capped fragments
// #. As part of previous step, we screen pairs, and maintain a list of pairs
// that
//    survive
// #. Create m-mers by taking unions of surviving (m-1)-mers with surviving
// pairs
//    such that one (and only one) of the fragments in the pair is also in the
//    (m-1)-mer.

// N.B. This algorithm avoids returning n-mers which are subsets of other
// n-mers.
//      For disjoint fragments it should always be the case that no subsets are
//      returned; however, for non-disjoint fragments some subsets may survive.

// Algorithm Notes:
// ----------------

// This module assumes it's run as part of NMer driver and that NMer driver has
// taken care of ensuring the number of fragments is greater than or equal to
// the requested truncation order and that the NMer driver takes care of the
// truncation orders of 0 and 1. Hence we only worry about "real" nmers.

// Let N be the number of fragments, n be the nmer truncation level, and t be
// the distance cut-off then:

// - Determining the distances between fragments has us consider all fragments
// and
//   dimers
// - For a trimer to survive there must be a path through the trimer such that
//   each edge of the path is within the threshold distance. This means it must
//   be the case that:
//   - path a-b-c is such that a-b < t and b-c < t, and/or
//   - path b-a-c is such that a-b < t and a-c < t, and/or
//   - path a-c-b is such that a-c < t and b-c < t
// - For tetramer a-b-c-d to survive there must be a path through the tetramer
// such
//   that each edge of the path is within the threshold distance. This means
//   that it must be the case:
//   - path a-b-c-d is such that a-b-c < t  and c-d < t
//   - path a-(b-d)-c is such that a-b-c < t and b-d < t
//   - path d-a-b-c is such that a-b-c < t and a-d < t
//   - path a-b-d-c is such that a-b-d < t and c-d < t
//   - path a-(b-c)-d is such that a-b-d < t and b-c < t
//   - path c-a-b-d is such that a-b-d < t and a-c < t
//   - path a-c-d-b is such that a-c-d < t and b-d < t
//   - path a-(c-b)-d is such that a-c-d < t and b-c < t
//   - path b-a-c-d is such that a-c-d < t and a-b < t
//   - path b-c-d-a is such that b-c-d < t and a-d < t
//   - path b-(c-a)-d is such that b-c-d < t and a-c < t
//   - path a-b-c-d is such that b-c-d < t and a-b < t
// - The generalization is that the m-mers that survive can be formed by taking
// the
//   unions of (m-1)-mers that survive with pairs a-b such that at least one of
//   the monomers (either a or b) is in the (m-1)-mer. If the pair a-b is a
//   subset of the (m-1)-mer you just get back the (m-1)-mer
// )""";

// MODULE_CTOR(MinimumDistance) {
//     description(desc);

//     satisfies_property_type<my_pt>();

//     // Default is not to screen
//     const auto max = std::numeric_limits<double>::max();
//     add_input<double>("threshold").set_default(max);
// }

// MODULE_RUN(MinimumDistance) {
//     const auto& [capped_frags, n] = my_pt::unwrap_inputs(inputs);
//     auto t                        = inputs.at("threshold").value<double>();

//     // N == number of frags, n == truncation order
//     const auto N = capped_frags.size();

//     // TODO: Revisit when Chemist#284 is tackled
//     type::fragmented_molecule frags(capped_frags.begin()->first.object());
//     for(const auto& [f0, c0] : capped_frags) frags.insert(f0);
//     type::nmers nmers(frags);

//     // This will be the surviving dimers
//     using nmer_type = typename type::nmers::value_type;
//     std::vector<nmer_type> dimers;

//     // Add the fragments
//     std::set<nmer_type> good_nmers;
//     for(const auto& f0c0 : capped_frags) {
//         auto frag = nmers.new_subset();
//         frag.insert(f0c0.first);
//         good_nmers.insert(frag);
//     }

//     // 1. Determine distances between capped fragments
//     using key_type = typename
//     std::decay_t<decltype(capped_frags)>::value_type; std::map<key_type,
//     std::map<key_type, double>> distance; for(const auto& f0c0 :
//     capped_frags) {
//         const auto& f0 = f0c0.first;
//         const auto& c0 = f0c0.second;
//         for(const auto& f1c1 : capped_frags) {
//             const auto& f1 = f1c1.first;
//             if(f0 == f1) break; // Only consider f0 > f1
//             const auto& c1       = f1c1.second;
//             const auto r         = min_distance(f0, c0, f1, c1);
//             distance[f0c0][f1c1] = r;
//             distance[f1c1][f0c0] = r;
//             if(r <= t) {
//                 auto dimer = nmers.new_subset();
//                 dimer.insert(f0);
//                 dimer.insert(f1);
//                 auto frag0 = nmers.new_subset();
//                 frag0.insert(f0);
//                 good_nmers.erase(frag0);
//                 auto frag1 = nmers.new_subset();
//                 frag1.insert(f1);
//                 good_nmers.erase(frag1);
//                 dimers.push_back(dimer);
//                 good_nmers.insert(dimer);
//             }
//         }
//     }

//     // Since the above also considers f0 == f1 nmers currently contains
//     monomers
//     // and dimers, we now need to get the (m + 1)-mers such that m >= 2.

//     // This variable will hold the m-mers that cleared screening
//     std::vector<nmer_type> mmers(dimers);

//     // The last (m+1)-mers we need to consider are the n-mers
//     for(std::size_t m = 2; m < n; ++m) {
//         // Here we make the (m+1)-mers
//         std::vector<nmer_type> mp1_mers;

//         for(const auto& mmer : mmers) {       // Loop over surviving m-mers
//             for(const auto& dimer : dimers) { // Loop over surviving pairs
//                 // Share a fragment when intersection is 1
//                 bool share_a_fragment = (dimer ^ mmer).size() == 1;
//                 if(!share_a_fragment) continue;
//                 auto mp1_mer = mmer + dimer;
//                 good_nmers.erase(mmer);
//                 good_nmers.erase(dimer);
//                 good_nmers.insert(mp1_mer);
//                 mp1_mers.push_back(mp1_mer);
//             }
//         }
//         mmers.swap(mp1_mers);
//     }

//     for(auto x : good_nmers) nmers.insert(x);

//     auto rv = results();
//     return my_pt::wrap_results(rv, nmers);
// }

// } // namespace ghostfragment::screening
