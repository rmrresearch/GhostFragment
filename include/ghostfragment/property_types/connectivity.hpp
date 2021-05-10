#pragma once
#include "ghostfragment/connectivity_table.hpp"
#include "ghostfragment/types.hpp"
#include <sde/sde.hpp>

namespace ghostfragment {

DECLARE_PROPERTY_TYPE(Connectivity);

PROPERTY_TYPE_INPUTS(Connectivity) {
    using mol_input_t = const type::molecule&;
    auto rv = sde::declare_inputs().add_field<mol_input_t>("Molecule");
    rv.at("Molecule")
      .set_description("The molecule whose bonds are being assigned.");
    return rv;
}

PROPERTY_TYPE_RESULTS(Connectivity) {
    using table_t = ConnectivityTable;
    auto rv = sde::declare_results().add_field<table_t>("Connectivity Table");
    rv.at("Connectivity Table")
      .set_description("Connectivity of the input molecule.");
    return rv;
}

} // namespace ghostfragment