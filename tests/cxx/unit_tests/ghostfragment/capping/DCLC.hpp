#pragma once

#include <catch2/catch.hpp>
#include <chemist/molecule/atom.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/nuclei.hpp>

namespace testing {
// Ethane Molecule (2 carbon, 2 frags)
chemist::Molecule Ethane2() {
    chemist::Molecule ethane;

    // First Hydrogen
    ethane.push_back(
      chemist::Atom("H", 1, 1837.289, 1.682281604, 1.188919091, 0));

    // Last Hydrogen
    ethane.push_back(
      chemist::Atom("H", 1, 1837.289, 0.677812, 0.479031, 0));

    return ethane;
}

// Propane Molecule (3 carbon, 2 frags)
chemist::Molecule Propane2() {
    chemist::Molecule propane;

    // First Hydrogen
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 4.04238, 0.479031, 0));

    // Last Hydrogen
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 0.677812, 0.479031, 0));

    return propane;
}

// Propane Molecule (3 carbon, 4 frags)
chemist::Molecule Propane4() {
    chemist::Molecule propane;

    // First Hydrogen
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 1.68228, 1.18892, 0));

    // Second Hydrogen
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 0.677812, 0.479031, 0));

    // Third Hydrogen
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 4.04238, 0.479031, 0));

    // Last Hydrogen
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 3.03791, 1.18892, 0));

    return propane;
}

bool AreMoleculesEqual(chemist::Molecule m1, chemist::Molecule m2) {
    int size1 = m1.size();
    int size2 = m2.size();

    // First checks that the molecules have the same number of atoms
    REQUIRE(size1 == size2);

    // Grabs the nuclei of each molecule to check each atom individually
    chemist::Molecule::const_nuclei_reference nuclei1 = m1.nuclei();
    chemist::Molecule::const_nuclei_reference nuclei2 = m2.nuclei();

    for(int i = 0; i < size1; i++) {
        // Each atom must be checked against each other for name and position
        chemist::Nuclei::const_reference atom1 = nuclei1.at(i);
        chemist::Nuclei::const_reference atom2 = nuclei2.at(i);

        // Names must be the same
        REQUIRE(atom1.name() == atom2.name());

        // Checking coordinates using a tolerance of 4 digits
        // X coordinate
        REQUIRE(atom1.x() == Approx(atom2.x()).margin(0.0001));
        // Y coordinate
        REQUIRE(atom1.y() == Approx(atom2.y()).margin(0.0001));
        // Z coordinate
        REQUIRE(atom1.z() == Approx(atom2.z()).margin(0.0001));
    }

    return true;
}
} // namespace testing