// #pragma once

// #include <catch2/catch.hpp>
// #include <chemist/molecule/atom.hpp>
// #include <chemist/molecule/molecule.hpp>
// #include <chemist/nucleus/nuclei.hpp>

// namespace testing {
// // Methane Molecule (1 carbon)
// chemist::Molecule Methane() {
//     chemist::Molecule methane;

//     // Carbon Atom
//     methane.push_back(chemist::Atom("C", 6, 21874.662, 0, 0, 0));

//     // First Hydrogen
//     methane.push_back(
//       chemist::Atom("H", 1, 1837.289, -1.682281604, 1.188919091, 0));

//     // Side Hydrogens
//     methane.push_back(
//       chemist::Atom("H", 1, 1837.289, 0, -1.188919091, -1.682281604));
//     methane.push_back(
//       chemist::Atom("H", 1, 1837.289, 0, -1.188919091, 1.682281604));

//     // Last Hydrogen
//     methane.push_back(
//       chemist::Atom("H", 1, 1837.289, 1.682281604, 1.188919091, 0));

//     return methane;
// }

// // Ethane Molecule (2 carbons)
// chemist::Molecule Ethane() {
//     chemist::Molecule ethane;

//     // Carbon Atoms
//     ethane.push_back(chemist::Atom("C", 6, 21874.662, 0, 0, 0));
//     ethane.push_back(
//       chemist::Atom("C", 6, 21874.662, 2.360094094, 1.667949599, 0));

//     // First Hydrogen
//     ethane.push_back(
//       chemist::Atom("H", 1, 1837.289, -1.682281604, 1.188919091, 0));

//     // Side Hydrogens
//     ethane.push_back(
//       chemist::Atom("H", 1, 1837.289, 0, -1.188919091, -1.682281604));
//     ethane.push_back(
//       chemist::Atom("H", 1, 1837.289, 0, -1.188919091, 1.682281604));
//     ethane.push_back(
//       chemist::Atom("H", 1, 1837.289, 2.360094094, 2.85686869,
//       -1.682281604));
//     ethane.push_back(
//       chemist::Atom("H", 1, 1837.289, 2.360094094, 2.85686869, 1.682281604));

//     // Last Hydrogen
//     ethane.push_back(
//       chemist::Atom("H", 1, 1837.289, 4.042375698, 0.4790305075, 0));

//     return ethane;
// }

// // Propane Molecule (3 carbons)
// chemist::Molecule Propane() {
//     chemist::Molecule propane;

//     // Carbon Atoms
//     propane.push_back(chemist::Atom("C", 6, 21874.662, 0, 0, 0));
//     propane.push_back(
//       chemist::Atom("C", 6, 21874.662, 2.360094094, 1.667949599, 0));
//     propane.push_back(chemist::Atom("C", 6, 21874.662, 4.720188189, 0, 0));

//     // First Hydrogen
//     propane.push_back(
//       chemist::Atom("H", 1, 1837.289, -1.682281604, 1.188919091, 0));

//     // Side Hydrogens
//     propane.push_back(
//       chemist::Atom("H", 1, 1837.289, 0, -1.188919091, -1.682281604));
//     propane.push_back(
//       chemist::Atom("H", 1, 1837.289, 0, -1.188919091, 1.682281604));
//     propane.push_back(
//       chemist::Atom("H", 1, 1837.289, 2.360094094, 2.85686869,
//       -1.682281604));
//     propane.push_back(
//       chemist::Atom("H", 1, 1837.289, 2.360094094, 2.85686869, 1.682281604));
//     propane.push_back(
//       chemist::Atom("H", 1, 1837.289, 4.720188189, -1.188919091,
//       -1.682281604));
//     propane.push_back(
//       chemist::Atom("H", 1, 1837.289, 4.720188189,
//       -1.188919091, 1.682281604));

//     // Last Hydrogen
//     propane.push_back(
//       chemist::Atom("H", 1, 1837.289, 6.402469793, 1.188919091, 0));

//     return propane;
// }

// bool AreMoleculesEqual(chemist::Molecule m1, chemist::Molecule m2) {
//     int size1 = m1.size();
//     int size2 = m2.size();

//     // First checks that the molecules have the same number of atoms
//     REQUIRE(size1 == size2);

//     // Grabs the nuclei of each molecule to check each atom individually
//     chemist::Molecule::const_nuclei_reference nuclei1 = m1.nuclei();
//     chemist::Molecule::const_nuclei_reference nuclei2 = m2.nuclei();

//     for(int i = 0; i < size1; i++) {
//         // Each atom must be checked against each other for name and position
//         chemist::Nuclei::const_reference atom1 = nuclei1.at(i);
//         chemist::Nuclei::const_reference atom2 = nuclei2.at(i);

//         // Checking the name
//         REQUIRE(atom1.name() == atom2.name());

//         // Checking coordinates using a tolerance of 8 digits
//         // X coordinate
//         REQUIRE(atom1.x() == Approx(atom2.x()).margin(0.000001));
//         // Y coordinate
//         REQUIRE(atom1.y() == Approx(atom2.y()).margin(0.000001));
//         // Z coordinate
//         REQUIRE(atom1.y() == Approx(atom2.y()).margin(0.000001));
//     }

//     return true;
// }
// } // namespace testing
