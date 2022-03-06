#pragma once
#include "ghostfragment/nmer_system.hpp"
#include <simde/simde.hpp>

namespace ghostfragment::pt {

struct NMerSystemTraits {
    using input_type = ghostfragment::FragmentedSystem;

    using result_type = ghostfragment::NMerSystem;
};

DECLARE_PROPERTY_TYPE(NMerSystem);

PROPERTY_TYPE_INPUTS(NMerSystem) {
    using traits_type = NMerSystemTraits;
    using input_type  = traits_type::input_type;

    return pluginplay::declare_input().add_field<input_type>(
      "Fragmented System");
}

PROPERTY_TYPE_RESULTS(NMerSystem) {
    using traits_type = NMerSystemTraits;
    using result_type = traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>("N-Mer System");
}

} // namespace ghostfragment::pt