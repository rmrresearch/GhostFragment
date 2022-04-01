// #include "ghostfragment/nmer_system.hpp"
// #include "test_ghostfragment.hpp"

// using namespace ghostfragment;
// using namespace testing;

// TEST_CASE("NMerSystem") {
//     using fragmented_system_type = NMerSystem::fragmented_system_type;
//     using capped_nmers           = NMerSystem::capped_nmers;
//     using vector_type            =
//     fragmented_system_type::atom2nelectron_type; auto water3 =
//     fragmented_water(3); auto water4                  = fragmented_water(4);
//     auto dimers                  = make_nmers(water3, 2);
//     auto trimers                 = make_nmers(water4, 3);

//     simde::type::molecule all_caps;
//     type::fragmented_molecule caps(all_caps);
//     auto empty_set = caps.new_subset();
//     capped_nmers nmers;
//     for(const auto& dimer_i : dimers) nmers.emplace(dimer_i, empty_set);

//     vector_type es{8, 1, 1, 8, 1, 1, 8, 1, 1};
//     auto aos = water_ao_pairs(3);
//     fragmented_system_type frags(water3, aos, es);

//     NMerSystem defaulted;
//     NMerSystem has_value(frags, nmers);

//     SECTION("CTors") {
//         SECTION("Default") { REQUIRE(defaulted.size() == 0); }
//         SECTION("Value") {
//             REQUIRE(has_value.size() == 3);
//             REQUIRE(has_value.fragments() == frags);
//         }
//         SECTION("Copy") {
//             NMerSystem default_copy(defaulted);
//             REQUIRE(default_copy == defaulted);

//             NMerSystem copy(has_value);
//             REQUIRE(copy == has_value);
//         }
//         SECTION("Move") {
//             NMerSystem default_moved(std::move(defaulted));
//             REQUIRE(default_moved == NMerSystem{});

//             NMerSystem corr(has_value);
//             NMerSystem value_moved(std::move(has_value));
//             REQUIRE(corr == value_moved);
//         }
//         SECTION("Copy Assignment") {
//             NMerSystem copy;
//             auto pcopy = &(copy = has_value);
//             REQUIRE(pcopy == &copy);
//             REQUIRE(copy == has_value);
//         }
//         SECTION("Move Assignment") {
//             NMerSystem default_moved;
//             auto pdefault = &(default_moved = std::move(defaulted));
//             REQUIRE(pdefault == &default_moved);
//             REQUIRE(default_moved == NMerSystem{});

//             NMerSystem corr(has_value);
//             NMerSystem value_moved;
//             auto pvalue = &(value_moved = std::move(has_value));
//             REQUIRE(pvalue == &value_moved);
//             REQUIRE(corr == value_moved);
//         }
//     }

//     SECTION("size") {
//         REQUIRE(defaulted.size() == 0);
//         REQUIRE(has_value.size() == 3);
//     }

//     SECTION("nmer") {
//         REQUIRE_THROWS_AS(defaulted.nmer(0), std::out_of_range);
//         REQUIRE(has_value.nmer(0) == dimers[0]);
//         REQUIRE(has_value.nmer(1) == dimers[1]);
//         REQUIRE(has_value.nmer(2) == dimers[2]);
//         REQUIRE_THROWS_AS(has_value.nmer(3), std::out_of_range);
//     }

//     SECTION("fragments") {
//         REQUIRE_THROWS_AS(defaulted.fragments(), std::runtime_error);
//         REQUIRE(has_value.fragments() == frags);
//     }

//     // Get the AOs for each atom
//     std::vector atom_aos{9, water3.new_subset()};
//     for(std::size_t i = 0; i < 9; ++i) atom_aos[i].insert(i);

//     // Make AOs for each water
//     auto water0_aos =
//       aos.at(atom_aos[0]) + aos.at(atom_aos[1]) + aos.at(atom_aos[2]);
//     auto water1_aos =
//       aos.at(atom_aos[3]) + aos.at(atom_aos[4]) + aos.at(atom_aos[5]);
//     auto water2_aos =
//       aos.at(atom_aos[6]) + aos.at(atom_aos[7]) + aos.at(atom_aos[8]);

//     SECTION("ao_basis_set(nmer)") {
//         using rerror = std::runtime_error;
//         REQUIRE_THROWS_AS(defaulted.ao_basis_set(dimers[0]), rerror);

//         auto d0_aos = water0_aos + water1_aos;
//         REQUIRE(has_value.ao_basis_set(dimers[0]) == d0_aos);

//         auto d1_aos = water0_aos + water2_aos;
//         REQUIRE(has_value.ao_basis_set(dimers[1]) == d1_aos);

//         auto d2_aos = water1_aos + water2_aos;
//         REQUIRE(has_value.ao_basis_set(dimers[2]) == d2_aos);

//         auto d01_aos = d0_aos + d1_aos;
//         REQUIRE(has_value.ao_basis_set(dimers[0] + dimers[1]) == d01_aos);

//         using oerror = std::out_of_range;
//         REQUIRE_THROWS_AS(has_value.ao_basis_set(trimers[0]), oerror);
//     }

//     SECTION("ao_basis_set(frag)") {
//         using rerror = std::runtime_error;
//         REQUIRE_THROWS_AS(defaulted.ao_basis_set(water3[0]), rerror);

//         REQUIRE(has_value.ao_basis_set(water3[0]) == water0_aos);
//         REQUIRE(has_value.ao_basis_set(water3[1]) == water1_aos);
//         REQUIRE(has_value.ao_basis_set(water3[2]) == water2_aos);

//         auto d0_aos = water0_aos + water1_aos;
//         REQUIRE(has_value.ao_basis_set(water3[0] + water3[1]) == d0_aos);

//         using oerror = std::out_of_range;
//         REQUIRE_THROWS_AS(has_value.ao_basis_set(water4[0]), oerror);
//     }

//     SECTION("n_electrons(nmer)") {
//         REQUIRE_THROWS_AS(defaulted.n_electrons(dimers[0]),
//         std::runtime_error); REQUIRE(has_value.n_electrons(dimers[0]) == 20);
//         REQUIRE(has_value.n_electrons(dimers[1]) == 20);
//         REQUIRE(has_value.n_electrons(dimers[2]) == 20);
//         REQUIRE(has_value.n_electrons(dimers[0] + dimers[1]) == 30);
//         REQUIRE_THROWS_AS(has_value.n_electrons(trimers[0]),
//         std::out_of_range);
//     }

//     SECTION("n_electrons(frag)") {
//         REQUIRE_THROWS_AS(defaulted.n_electrons(water3[0]),
//         std::runtime_error); REQUIRE(has_value.n_electrons(water3[0]) == 10);
//         REQUIRE(has_value.n_electrons(water3[1]) == 10);
//         REQUIRE(has_value.n_electrons(water3[2]) == 10);
//         REQUIRE(has_value.n_electrons(water3[0] + water3[1]) == 20);
//         REQUIRE_THROWS_AS(has_value.n_electrons(water4[0]),
//         std::out_of_range);
//     }

//     SECTION("Comparisons") {
//         // default is the same as default
//         REQUIRE(defaulted == NMerSystem{});
//         REQUIRE_FALSE(defaulted != NMerSystem{});

//         // Default != stateful
//         REQUIRE_FALSE(has_value == defaulted);
//         REQUIRE(has_value != defaulted);

//         // Same n-mers and fragments
//         REQUIRE(has_value == NMerSystem(frags, nmers));
//         REQUIRE_FALSE(has_value != NMerSystem(frags, nmers));

//         // Different fragments
//         REQUIRE_FALSE(has_value == NMerSystem(fragmented_system_type{},
//         nmers)); REQUIRE(has_value != NMerSystem(fragmented_system_type{},
//         nmers));

//         // Different n-mers
//         REQUIRE_FALSE(has_value == NMerSystem(frags, capped_nmers{}));
//         REQUIRE(has_value != NMerSystem(frags, capped_nmers{}));
//     }

//     SECTION("hash") {
//         using pluginplay::hash_objects;

//         // Default == default
//         auto default_hash = hash_objects(defaulted);
//         REQUIRE(default_hash == hash_objects(NMerSystem{}));

//         // Default != stateful
//         auto value_hash = hash_objects(has_value);
//         REQUIRE(value_hash != default_hash);

//         // Same n-mers
//         REQUIRE(value_hash == hash_objects(NMerSystem(frags, nmers)));

//         // Different fragments
//         REQUIRE(value_hash !=
//                 hash_objects(NMerSystem(fragmented_system_type{}, nmers)));

//         // Different n-mers
//         REQUIRE(value_hash != hash_objects(NMerSystem(frags,
//         capped_nmers{})));
//     }
// }
