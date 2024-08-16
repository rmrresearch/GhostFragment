#include <iostream>
#include "hydrocarbon.hpp"
#include "hc.hpp"
#include <simde/simde.hpp>

namespace ghostfragment::hydrocarbon {

using n_type = unsigned short;

const auto mod_desc = R"(
Hydrocarbon Chain Generator
---------------------------
)";

MODULE_CTOR(makehydrocarbon) {
    description(mod_desc);
    satisfies_property_type<simde::MoleculeFromString>();

    add_input<n_type>("n")
      .set_description("Number of carbons in carbon chain to generate")
      .set_default(n_type(1));
}

MODULE_RUN(makehydrocarbon) {
    auto num_carbon = inputs.at("n").value<n_type>();

    chemist::Molecule hc = hydrocarbon(int num_carbon);

    return hc;
}
}
