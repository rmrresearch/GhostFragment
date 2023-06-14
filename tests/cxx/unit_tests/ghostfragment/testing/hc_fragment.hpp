#pragma once

#include "hydrocarbon/hydrocarbon.h"
#include <catch2/catch.hpp>
#include <chemist/molecule/atom.hpp>
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/fragmented_nuclei.hpp>

namespace testing {
// Methane Molecule with fragment size 1
inline auto frag_methane_one(){
    auto hc = hydrocarbon(1);
    chemist::FragmentedNuclei frags(hc.nuclei());
    frags.add_fragment({0, 1, 2, 3, 4});
    return frags;
}
// Ethane Molecule with fragments size 1
inline auto frag_ethane_one() {
    auto hc = hydrocarbon(2);
    chemist::FragmentedNuclei frags(hc.nuclei());
    frags.add_fragment({0, 2, 3, 4});
    frags.add_fragment({1, 5, 6, 7});
    return frags;
}

inline auto frag_propane_one() {
    auto hc = hydrocarbon(3);
    chemist::FragmentedNuclei frags(hc.nuclei());
    frags.add_fragment({0, 3, 4, 5});
    frags.add_fragment({1, 6, 7});
    frags.add_fragment({2, 8, 9, 10});
    return frags;
}

inline auto frag_propane_two() {
    auto hc = hydrocarbon(3);
    chemist::FragmentedNuclei frags(hc.nuclei());
    frags.add_fragment({0, 1, 3, 4, 5, 6, 7});
    frags.add_fragment({1, 2, 6, 7, 8, 9, 10});
    return frags;
}
} // namespace testing