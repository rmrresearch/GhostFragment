#include "ghostfragment/nmer_system.hpp"
#include "test_ghostfragment.hpp"

using namespace ghostfragment;
using namespace testing;

TEST_CASE("NMerSystem") {
    using fragmented_system_type = NMerSystem::fragmented_system_type;
    using capped_nmers           = NMerSystem::capped_nmers;
    using vector_type            = fragmented_system_type::atom2nelectron_type;
    auto water3                  = fragmented_water(3);
    auto dimers                  = make_nmers(water3, 2);

    simde::type::molecule all_caps;
    type::fragmented_molecule caps(all_caps);
    auto empty_set = caps.new_subset();
    capped_nmers nmers;
    for(const auto& dimer_i : dimers) nmers.emplace(dimer_i, empty_set);

    vector_type es{8, 1, 1, 8, 1, 1, 8, 1, 1};
    fragmented_system_type frags(water3, water_ao_pairs(3), es);

    NMerSystem defaulted;
    NMerSystem has_value(frags, nmers);
}