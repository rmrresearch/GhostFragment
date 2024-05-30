#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::pt {

struct FragmentWeightsTraits {
    using chemical_system_type = chemist::ChemicalSystem;
    using fragments_type =
      chemist::fragmenting::FragmentedChemicalSystem<chemical_system_type>;
    using weight_type      = double;
    using weight_container = std::vector<weight_type>;
};

DECLARE_PROPERTY_TYPE(FragmentWeights);

PROPERTY_TYPE_INPUTS(FragmentWeights) {
    using fragments_type = typename FragmentWeightsTraits::fragments_type;
    using input0_type    = const fragments_type&;
    return pluginplay::declare_input().add_field<input0_type>("Fragments");
}

PROPERTY_TYPE_RESULTS(FragmentWeights) {
    using result_type = typename FragmentWeightsTraits::weight_container;
    return pluginplay::declare_result().add_field<result_type>("Weights");
}

} // namespace ghostfragment::pt
