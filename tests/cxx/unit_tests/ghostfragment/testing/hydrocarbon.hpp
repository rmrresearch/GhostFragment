#pragma once

#include <chemist/molecule/atom.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/nuclei.hpp>

#include <iostream>

namespace testing {
// Methane Molecule (1 carbon)
chemist::Molecule Methane() {
    chemist::Molecule methane;

    // Carbon Atom
    methane.push_back(chemist::Atom("C", 6, 21874.662, 0, 0, 0));

    // First Hydrogen
    methane.push_back(
      chemist::Atom("H", 1, 1837.289, -0.8901392951, 0.6290882571, 0));

    // Side Hydrogens
    methane.push_back(
      chemist::Atom("H", 1, 1837.289, 0, -0.6290882571, -0.8901392951));
    methane.push_back(
      chemist::Atom("H", 1, 1837.289, 0, -0.6290882571, 0.8901392951));

    // Last Hydrogen
    methane.push_back(
      chemist::Atom("H", 1, 1837.289, 0.8901392951, 0.6290882571, 0));

    return methane;
}

// Ethane Molecule (2 carbons)
chemist::Molecule Ethane() {
    chemist::Molecule ethane;

    // Carbon Atoms
    ethane.push_back(chemist::Atom("C", 6, 21874.662, 0, 0, 0));
    ethane.push_back(
      chemist::Atom("C", 6, 21874.662, 1.249461579, 0.8830321408, 0));

    // First Hydrogen
    ethane.push_back(
      chemist::Atom("H", 1, 1837.289, -0.8901392951, 0.6290882571, 0));

    // Side Hydrogens
    ethane.push_back(
      chemist::Atom("H", 1, 1837.289, 0, -0.6290882571, -0.8901392951));
    ethane.push_back(
      chemist::Atom("H", 1, 1837.289, 0, -0.6290882571, 0.8901392951));
    ethane.push_back(
      chemist::Atom("H", 1, 1837.289, 1.249461579, 1.512120398, -0.8901392951));
    ethane.push_back(
      chemist::Atom("H", 1, 1837.289, 1.249461579, 1.512120398, 0.8901392951));

    // Last Hydrogen
    ethane.push_back(
      chemist::Atom("H", 1, 1837.289, 2.139600874, 0.2539438837, 0));

    return ethane;
}

// Propane Molecule (3 carbons)
chemist::Molecule Propane() {
    chemist::Molecule propane;

    // Carbon Atoms
    propane.push_back(chemist::Atom("C", 6, 21874.662, 0, 0, 0));
    propane.push_back(
      chemist::Atom("C", 6, 21874.662, 1.249461579, 0.8830321408, 0));
    propane.push_back(chemist::Atom("C", 6, 21874.662, 2.498923159, 0, 0));

    // First Hydrogen
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, -0.8901392951, 0.6290882571, 0));

    // Side Hydrogens
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 0, -0.6290882571, -0.8901392951));
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 0, -0.6290882571, 0.8901392951));
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 1.249461579, 1.512120398, -0.8901392951));
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 1.249461579, 1.512120398, 0.8901392951));
    propane.push_back(chemist::Atom("H", 1, 1837.289, 2.498923159,
                                    -0.6290882571, -0.8901392951));
    propane.push_back(chemist::Atom("H", 1, 1837.289, 2.498923159,
                                    -0.6290882571, 0.8901392951));

    // Last Hydrogen
    propane.push_back(
      chemist::Atom("H", 1, 1837.289, 3.389062454, 0.6290882571, 0));

    return propane;
}

bool AreMoleculesEqual(chemist::Molecule m1, chemist::Molecule m2) {
    int size1 = m1.size();
    int size2 = m2.size();

    // First checks that the molecules have the same number of atoms
    if(size1 != size2) {
        std::cout << "Size 1: " << size1 << " does not equal Size 2: " << size2
                  << "." << std::endl;
        return false;
    }

    // Grabs the nuclei of each molecule to check each atom individually
    chemist::Molecule::const_nuclei_reference nuclei1 = m1.nuclei();
    chemist::Molecule::const_nuclei_reference nuclei2 = m2.nuclei();

    for(int i = 0; i < size1; i++) {
        // Each atom must be checked against each other for name and position
        chemist::Nuclei::const_reference atom1 = nuclei1.at(i);
        chemist::Nuclei::const_reference atom2 = nuclei2.at(i);

        // Checking the name
        if(atom1.name() != atom2.name()) {
            std::cout << "Name 1: " << atom1.name()
                      << " is not equal to Name 2: " << atom2.name() << "."
                      << std::endl;
            return false;
        }

        // Checking coordinates using a tolerance of 8 digits
        // X coordinate
        if((atom1.x() - atom2.x()) > 0.0000001) {
            std::cout << atom1.name() << " " << i << " x: " << atom1.x()
                      << " is not equal to " << atom2.name() << " " << i
                      << " x: " << atom2.x() << "." << std::endl;
            return false;
        }
        // Y coordinate
        if((atom1.y() - atom2.y()) > 0.0000001) {
            std::cout << atom1.name() << " " << i << " y: " << atom1.y()
                      << " is not equal to " << atom2.name() << " " << i
                      << " y: " << atom2.y() << "." << std::endl;
            return false;
        }
        // Z coordinate
        if((atom1.z() - atom2.z()) > 0.0000001) {
            std::cout << atom1.name() << " " << i << " z: " << atom1.z()
                      << " is not equal to " << atom2.name() << " " << i
                      << " z: " << atom2.z() << "." << std::endl;
            return false;
        }
    }

    return true;
}
} // namespace testing
