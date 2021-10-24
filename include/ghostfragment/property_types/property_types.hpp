#pragma once
#include "ghostfragment/types.hpp"
#include <simde/simde.hpp>

namespace ghostfragment::pt {

DECLARE_DERIVED_PROPERTY_TYPE(FragmentedSystemAO, simde::FragmentedNucleiAO);

PROPERTY_TYPE_INPUTS(FragmentedSystemAO) {
    return pluginplay::declare_input().add_field<std::size_t>("NElectrons");
}

PROPERTY_TYPE_RESULTS(FragmentedSystemAO) {
    return pluginplay::declare_result().add_field<std::vector<std::size_t>>(
      "NElectrons");
}

} // namespace ghostfragment::pt
