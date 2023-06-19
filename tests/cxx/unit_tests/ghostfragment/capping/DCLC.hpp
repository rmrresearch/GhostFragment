#pragma once

#include <catch2/catch.hpp>
#include <chemist/molecule/atom.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/nuclei.hpp>
#include <src/ghostfragment/capping/DCLC.cpp>

namespace testing {
// Correct answers for three hydrocarbons -- ethane with two
// fragments, propane with two fragments, and propane with four
// fragments. Answers generated in Mathematica. 

// Ethane CapSets (2 carbon, 2 frags)
std::vector<chemist::CapSet> Ethane2() {
    std::vector<chemist::CapSet> ethane;
    chemist::CapSet caps1;
    chemist::CapSet caps2;

    // First CapSet
    caps1.add_cap(0, 1, chemist::Atom("H", 1, 1837.289, 
      1.682281604, 1.188919091, 0));
    ethane.push_back(caps1);

    // Last CapSet
    caps2.add_cap(1, 0, chemist::Atom("H", 1, 1837.289,
      0.677812, 0.479031, 0));
    ethane.push_back(caps2);

    return ethane;
}

// Propane CapSet (3 carbon, 2 frags)
std::vector<chemist::CapSet> Propane2() {
    std::vector<chemist::CapSet> propane;
    chemist::CapSet caps1;
    chemist::CapSet caps2;

    // First Cap
    caps1.add_cap(1, 2, chemist::Atom("H", 1, 1837.289, 
    4.04238, 0.479031, 0));
    propane.push_back(caps1);

    // Last Cap
    caps2.add_cap(1, 0, chemist::Atom("H", 1, 1837.289, 
    0.677812, 0.479031, 0));
    propane.push_back(caps2);

    return propane;
}

// Propane CapSet (3 carbon, 4 frags)
std::vector<chemist::CapSet> Propane4() {
    std::vector<chemist::CapSet> propane;
    chemist::CapSet caps1;
    chemist::CapSet caps2;
    chemist::CapSet caps3;

    // First Cap
    caps1.add_cap(0, 1, chemist::Atom("H", 1, 1837.289, 
    1.68228, 1.18892, 0));
    propane.push_back(caps1);

    // Second Cap
    caps2.add_cap(1, 0, chemist::Atom("H", 1, 1837.289, 
    0.677812, 0.479031, 0));
    caps2.add_cap(1, 2, chemist::Atom("H", 1, 1837.289, 
    4.04238, 0.479031, 0));
    propane.push_back(caps2);

    // Last Cap
    caps3.add_cap(2, 1, chemist::Atom("H", 1, 1837.289, 
    3.03791, 1.18892, 0));
    propane.push_back(caps3);

    return propane;
}

// Function checks to see if two sets of caps (inputs are Molecules
// but the constituent atoms are the capping atoms) are equal. Loops
// over each atom, checks position and name.

bool AreCapsEqual(std::vector<chemist::CapSet> m1,
std::vector<chemist::CapSet> m2) {
    int size1 = m1.size();
    int size2 = m2.size();
    int cap_size1 = 0;
    int cap_size2 = 0;

    // First checks that the cap sets are equal in size
    REQUIRE(size1 == size2);

    // Loops over the vector of CapSets
    for(int i = 0; i < size1; i++) {
        cap_size1 = m1[i].size();
        cap_size2 = m2[i].size();

        // Corresponding CapSets must be the same size
        REQUIRE(cap_size1 == cap_size2);

        // Loops through the CapSets
        for(int j = 0; j < cap_size1; j++) {
          // Must share atomic number
          REQUIRE(m1[i][j].cap_atom(0).Z() == m2[i][j].cap_atom(0).Z());

          // Checking coordinates using a tolerance of 8 digits
          // X coordinate
          REQUIRE(m1[i][j].cap_atom(0).x() == 
          Approx(m2[i][j].cap_atom(0).x()).margin(0.0000001));
          // Y coordinate
          REQUIRE(m1[i][j].cap_atom(0).y() == 
          Approx(m2[i][j].cap_atom(0).y()).margin(0.0000001));
          // Z coordinate
          REQUIRE(m1[i][j].cap_atom(0).z() == 
          Approx(m2[i][j].cap_atom(0).z()).margin(0.0000001));
        }
    }

    return true;
}
} // namespace testing