/*
 * Copyright 2022 NWChemEx-Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "simde/types.hpp"
#include <pluginplay/pluginplay.hpp>

namespace simde {

/** @brief The property type for modules that return a molecular basis set from
 *         a molecule.
 */
DECLARE_PROPERTY_TYPE(MolecularBasisSet);

PROPERTY_TYPE_INPUTS(MolecularBasisSet) {
    using mol_t = const type::molecule&;
    auto rv     = pluginplay::declare_input().add_field<mol_t>("Molecule");
    rv.at("Molecule")
      .set_description("The molecule for which to generate the basis set");
    return rv;
}

PROPERTY_TYPE_RESULTS(MolecularBasisSet) {
    using basis_t = type::ao_basis_set;
    auto rv =
      pluginplay::declare_result().add_field<basis_t>("Molecular Basis Set");
    rv.at("Molecular Basis Set")
      .set_description("The basis set for the molecule");
    return rv;
}

} // namespace simde