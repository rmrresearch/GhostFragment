#pragma once
#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/molecular_graph.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

struct BrokenBondsTraits {
    using input_type = chemist::FragmentedNuclei<Nuclei>;

    using size_type   = typename input_type::size_type;
    using bond_type   = std::pair<size_type, size_type>;
    using bond_set    = std::set<bond_type>;
    using result_type = std::vector<bond_set>;
};

DECLARE_PROPERTY_TYPE(BrokenBonds);

PROPERTY_TYPE_INPUTS(BrokenBonds) {
    using input_type = BrokenBondsTraits::input_type;
    return pluginplay::declare_input().add_field<input_type>("Fragments");
}

PROPERTY_TYPE_RESULTS(BrokenBonds) {
    using result_type = BrokenBondsTraits::result_type;
    return pluginplay::declare_result().add_field<result_type>("Broken Bonds");
}

} // namespace ghostfragment::pt
