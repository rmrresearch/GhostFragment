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

/** @brief The property type for modules that return a molecule from a string
 *         input.
 *
 * The usage of this property type can be pretty varied. Modules that satisfy
 * this property type could potentially produce a molecule from a string with
 * XYZ inputs, a SMILES string, or a molecule name outright.
 *
 */
DECLARE_PROPERTY_TYPE(MoleculeFromString);

PROPERTY_TYPE_INPUTS(MoleculeFromString) {
    using str_t = const std::string&;
    auto rv     = pluginplay::declare_input().add_field<str_t>("String");
    rv.at("String").set_description(
      "The string identifying the desired molecule");
    return rv;
}

PROPERTY_TYPE_RESULTS(MoleculeFromString) {
    using mol_t = type::molecule;
    auto rv     = pluginplay::declare_result().add_field<mol_t>("Molecule");
    rv.at("Molecule")
      .set_description("The molecule corresponding to the input string");
    return rv;
}

} // namespace simde
