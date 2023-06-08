#pragma once
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <ghostfragment/molecular_graph.hpp>

namespace ghostfragment::pt {

struct MolecularGraphToFragmentsTraits {
    /// Type of input to a MolecularGraphToFragments module
    using graph_type = ghostfragment::MolecularGraph;

    /// Type of result from a MolecularGraphToFragments module
    using fragment_type = chemist::FragmentedNuclei;
};

DECLARE_PROPERTY_TYPE(MolecularGraphToFragments);

PROPERTY_TYPE_INPUTS(MolecularGraphToFragments) {
    using graph_type = MolecularGraphToFragmentsTraits::graph_type;

    return pluginplay::declare_input().add_field<graph_type>("Molecular Graph");
}

PROPERTY_TYPE_RESULTS(MolecularGraphToFragments) {
    using fragment_type = MolecularGraphToFragmentsTraits::fragment_type;

    return pluginplay::declare_result().add_field<fragment_type>("Fragments");
}

} // namespace ghostfragment::pt
