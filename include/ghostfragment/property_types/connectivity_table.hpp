#pragma once
#include <chemist/chemical_system/nucleus/nuclei.hpp>
#include <chemist/topology/connectivity_table.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment {

struct ConnectivityTableTraits {
    using input_type  = chemist::Nuclei;
    using result_type = chemist::topology::ConnectivityTable;
};

DECLARE_PROPERTY_TYPE(ConnectivityTable);

PROPERTY_TYPE_INPUTS(ConnectivityTable) {
    using input_type = ConnectivityTableTraits::input_type;
    return pluginplay::declare_input().add_field<input_type>("Nuclei");
}

PROPERTY_TYPE_RESULTS(ConnectivityTable) {
    using result_type = ConnectivityTableTraits::result_type;
    return pluginplay::declare_result().add_field<result_type>(
      "ConnectivityTable");
}

} // namespace ghostfragment
