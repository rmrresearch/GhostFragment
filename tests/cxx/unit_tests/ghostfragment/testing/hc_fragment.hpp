#pragma once

#include "../../../../../src/ghostfragment/connectivity/hydrocarbon/hydrocarbon.h"
#include <chemist/molecule/molecule.hpp>
#include <chemist/molecule/atom.hpp>
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <catch2/catch.hpp>

namespace testing {
// Ethane Molecule fragmented into two fragments with one carbon each
inline auto frag_two_two() {
    auto hc = hydrocarbon(2);
    chemist::FragmentedNuclei frags(hc.nuclei());
    frags.add_fragment({1, 3, 4, 5});
    frags.add_fragment({2, 7, 8, 9});
    return frags;
}
} // namespace testing