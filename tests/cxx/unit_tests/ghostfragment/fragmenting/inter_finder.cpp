// #include "../test_ghostfragment.hpp"
// #include <ghostfragment/fragmenting/inter_finder.hpp>
// #include <iostream>

// using namespace ghostfragment::fragmenting;

// using mol_type  = chemist::FragmentedMolecule;
// using nuke_type = chemist::FragmentedNuclei;

// using inter_type = std::vector<std::size_t>;
// using res_type   = std::map<inter_type, float>;

// using nucleus_type = chemist::Nuclei;
// using atom_type    = nucleus_type::value_type;

// TEST_CASE("Intersection Finder") {
//     nucleus_type nuclei;

//     for(auto i = 0; i < 8; ++i) {
//         nuclei.push_back(atom_type("H", 1ul, 1.0, i, 0.0, 0.0));
//     }

//     nuke_type frag_nuke(nuclei);
//     res_type corr;

//     SECTION("No Fragments") {
//         mol_type mol(frag_nuke);
//         REQUIRE(intersections(mol) == corr);
//     }

//     SECTION("One Fragment") {
//         frag_nuke.add_fragment({0, 1, 2, 3, 4, 5, 6, 7});
//         mol_type mol(frag_nuke);
//         REQUIRE(intersections(mol) == corr);
//     }

//     SECTION("Two Fragments") {
//         SECTION("Disjoint") {
//             frag_nuke.add_fragment({0, 1, 2, 3});
//             frag_nuke.add_fragment({4, 5, 6, 7});
//             mol_type mol(frag_nuke);
//             REQUIRE(intersections(mol) == corr);
//         }

//         SECTION("Overlap") {
//             frag_nuke.add_fragment({0, 1, 2, 3, 4});
//             frag_nuke.add_fragment({4, 5, 6, 7});
//             mol_type mol(frag_nuke);

//             corr.insert({{4}, -1.0});

//             REQUIRE(intersections(mol) == corr);
//         }
//     }

//     SECTION("Three Fragments") {
//         SECTION("Disjoint") {
//             frag_nuke.add_fragment({0, 1, 2});
//             frag_nuke.add_fragment({3, 4, 5});
//             frag_nuke.add_fragment({6, 7});
//             mol_type mol(frag_nuke);
//             REQUIRE(intersections(mol) == corr);
//         }

//         SECTION("One Overlap") {
//             frag_nuke.add_fragment({0, 1, 2});
//             frag_nuke.add_fragment({2, 3, 4});
//             frag_nuke.add_fragment({5, 6, 7});
//             mol_type mol(frag_nuke);

//             corr.insert({{2}, -1.0});

//             REQUIRE(intersections(mol) == corr);
//         }

//         SECTION("Two Overlaps") {
//             frag_nuke.add_fragment({0, 1, 2});
//             frag_nuke.add_fragment({2, 3, 4});
//             frag_nuke.add_fragment({4, 5, 6, 7});
//             mol_type mol(frag_nuke);

//             corr.insert({{2}, -1.0});
//             corr.insert({{4}, -1.0});

//             REQUIRE(intersections(mol) == corr);
//         }

//         SECTION("Three Overlaps") {
//             frag_nuke.add_fragment({0, 1, 2, 3});
//             frag_nuke.add_fragment({2, 3, 4, 5});
//             frag_nuke.add_fragment({3, 4, 5, 6});
//             mol_type mol(frag_nuke);

//             corr.insert({{2, 3}, -1.0});
//             corr.insert({{3, 4, 5}, -1.0});
//             corr.insert({{3}, 0.0});

//             REQUIRE(intersections(mol) == corr);
//         }
//     }

//     SECTION("Four Fragments") {
//         SECTION("Disjoint") {
//             frag_nuke.add_fragment({0, 1});
//             frag_nuke.add_fragment({2, 3});
//             frag_nuke.add_fragment({4, 5});
//             frag_nuke.add_fragment({6, 7});
//             mol_type mol(frag_nuke);
//             REQUIRE(intersections(mol) == corr);
//         }

//         SECTION("One Overlap") {
//             frag_nuke.add_fragment({0, 1, 2});
//             frag_nuke.add_fragment({2, 3});
//             frag_nuke.add_fragment({4, 5});
//             frag_nuke.add_fragment({6, 7});
//             mol_type mol(frag_nuke);

//             corr.insert({{2}, -1.0});

//             REQUIRE(intersections(mol) == corr);
//         }

//         SECTION("Two Overlaps") {
//             frag_nuke.add_fragment({0, 1, 2});
//             frag_nuke.add_fragment({2, 3});
//             frag_nuke.add_fragment({4, 5, 6});
//             frag_nuke.add_fragment({6, 7});
//             mol_type mol(frag_nuke);

//             corr.insert({{2}, -1.0});
//             corr.insert({{6}, -1.0});

//             REQUIRE(intersections(mol) == corr);
//         }

//         SECTION("Three Overlaps") {
//             frag_nuke.add_fragment({0, 1, 2});
//             frag_nuke.add_fragment({2, 3, 4});
//             frag_nuke.add_fragment({2, 4, 5, 6});
//             frag_nuke.add_fragment({6, 7});
//             mol_type mol(frag_nuke);

//             corr.insert({{2}, -1.0});
//             corr.insert({{2, 4}, -1.0});
//             corr.insert({{6}, -1.0});

//             REQUIRE(intersections(mol) == corr);
//         }

//         SECTION("Four Overlaps") {
//             frag_nuke.add_fragment({0, 1, 2, 3});
//             frag_nuke.add_fragment({2, 3, 4});
//             frag_nuke.add_fragment({2, 4, 5, 6});
//             frag_nuke.add_fragment({2, 6, 7});
//             mol_type mol(frag_nuke);

//             corr.insert({{2}, 0});
//             corr.insert({{2, 3}, -1.0});
//             corr.insert({{2, 4}, -1.0});
//             corr.insert({{2, 6}, -1.0});

//             REQUIRE(intersections(mol) == corr);
//         }
//     }
// }
