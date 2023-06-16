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

/** @brief The property type for modules that return an atomic basis set from an
 *         atomic identity.
 */
template<typename InputType>
DECLARE_TEMPLATED_PROPERTY_TYPE(AtomicBasisSet, InputType);

template<typename InputType>
TEMPLATED_PROPERTY_TYPE_INPUTS(AtomicBasisSet, InputType) {
    using input_t = const InputType&;
    auto rv       = pluginplay::declare_input().add_field<input_t>("Atom ID");
    rv.at("Atom ID").set_description("The identifying feature of the atom");
    return rv;
}

template<typename InputType>
TEMPLATED_PROPERTY_TYPE_RESULTS(AtomicBasisSet, InputType) {
    using atom_basis_t = type::atomic_basis_set;
    auto rv =
      pluginplay::declare_result().add_field<atom_basis_t>("Atomic Basis Set");
    rv.at("Atomic Basis Set").set_description("The basis set for the atom");
    return rv;
}

/// Typedef for a module that returns an atomic basis set from atomic number
using AtomicBasisSetFromZ = AtomicBasisSet<type::atomic_number>;

/// Typedef for a module that returns an atomic basis set from atomic symbol
using AtomicBasisSetFromSym = AtomicBasisSet<type::atomic_symbol>;

} // namespace simde
