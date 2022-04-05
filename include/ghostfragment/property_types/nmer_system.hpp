#pragma once
#include <ghostfragment/nmer_system.hpp>
#include <simde/simde.hpp>

namespace ghostfragment::pt {

struct NMerSystemTraits {
    using input0_type = ghostfragment::FragmentedSystem;
    using input1_type = unsigned int;

    using result_type = ghostfragment::NMerSystem;
};

DECLARE_PROPERTY_TYPE(NMerSystem);

PROPERTY_TYPE_INPUTS(NMerSystem) {
    using traits_type = NMerSystemTraits;
    using input0_type = traits_type::input0_type;
    using input1_type = traits_type::input1_type;

    return pluginplay::declare_input()
      .add_field<input0_type>("Fragmented System")
      .template add_field<input1_type>(" truncation order");
}

PROPERTY_TYPE_RESULTS(NMerSystem) {
    using traits_type = NMerSystemTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>("N-Mer System");
}

} // namespace ghostfragment::pt
