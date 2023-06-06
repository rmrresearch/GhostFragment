#pragma once

#include <chemist/molecule/atom.hpp>
#include <chemist/molecule/molecule.hpp>

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
    if(m1.size() != m2.size()) return false;

    return true;
}
} // namespace testing
