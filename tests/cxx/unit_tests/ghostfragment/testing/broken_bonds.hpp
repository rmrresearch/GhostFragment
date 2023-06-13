#pragma once
#include "ghostfragment/connectivity/hydrocarbon/hydrocarbon.h"
#include "ghostfragment/property_types/broken_bonds.hpp"
#include <catch2/catch.hpp>
#include <chemist/molecule/atom.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/fragmented_nuclei.hpp>

namespace testing {
using input_type = chemist::FragmentedNuclei;

using size_type   = typename input_type::size_type;
using bond_type   = std::pair<size_type, size_type>;
using bond_set    = std::set<bond_type>;
using result_type = std::vector<bond_set>;
// Broken bonds of an ethane molecule with fragments of size 1
inline auto bonds_ethane_one() {
    result_type bonds;

    bond_set set1;
    set1.insert(bond_type(0, 1));

    bond_set set2;
    set2.insert(bond_type(0, 1));

    bonds.push_back(set1);
    bonds.push_back(set2);

    return bonds;
}

inline auto bonds_propane_one() {
    result_type bonds;

    bond_set set1;
    set1.insert(bond_type(0, 1));

    bond_set set2;
    set2.insert(bond_type(0, 1));
    set2.insert(bond_type(1, 2));

    bond_set set3;
    set3.insert(bond_type(1, 2));

    bonds.push_back(set1);
    bonds.push_back(set2);
    bonds.push_back(set3);

    return bonds;
}

inline auto bonds_propane_two() {
    result_type bonds;

    bond_set set1;
    set1.insert(bond_type(0, 1));

    bond_set set2;
    set2.insert(bond_type(1, 2));

    bonds.push_back(set1);
    bonds.push_back(set2);

    return bonds;
}


} // namespace testing
