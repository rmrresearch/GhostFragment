#pragma once
#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <ghostfragment/nuclear_graph.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

struct BrokenBondsTraits {
    using fragments_type =
      chemist::fragmenting::FragmentedNuclei<chemist::Nuclei>;
    using conns_type  = chemist::topology::ConnectivityTable;
    using size_type   = typename fragments_type::size_type;
    using bond_type   = std::pair<size_type, size_type>;
    using result_type    = std::set<bond_type>;
};

DECLARE_PROPERTY_TYPE(BrokenBonds);

PROPERTY_TYPE_INPUTS(BrokenBonds) {
    using input0_type = const BrokenBondsTraits::fragments_type&;
    using input1_type = const BrokenBondsTraits::conns_type&;
    return pluginplay::declare_input()
      .add_field<input0_type>("Fragments")
      .template add_field<input1_type>("Connections");
}

PROPERTY_TYPE_RESULTS(BrokenBonds) {
    using result_type = BrokenBondsTraits::result_type;
    return pluginplay::declare_result().add_field<result_type>("Broken Bonds");
}

} // namespace ghostfragment::pt
