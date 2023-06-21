#pragma once

#include <catch2/catch.hpp>
#include <chemist/molecule/atom.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/nuclei.hpp>
#include <src/ghostfragment/capping/dclc.cpp>

namespace testing {
// Correct answers for three hydrocarbons -- ethane with two
// fragments, propane with two fragments, and propane with four
// fragments. Answers generated in Mathematica. 

// Methane CapSet (1 carbon, 1 frag)

std::vector<chemist::CapSet> methane_dclc_caps() {
    std::vector<chemist::CapSet> methane;
    chemist::CapSet caps;
    methane.push_back(caps);
    return(methane);
}
// Ethane CapSets (2 carbon, 2 frags)
std::vector<chemist::CapSet> ethane_dclc_caps() {
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
std::vector<chemist::CapSet> propane_dclc_2_caps() {
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
std::vector<chemist::CapSet> propane_dclc_3_caps() {
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

} // namespace testing
