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

/** @brief The property for a module that returns an atom based on an
 *         identifying feature (e.g. symbol or atomic number).
 */
template<typename InputType>
DECLARE_TEMPLATED_PROPERTY_TYPE(Atom, InputType);

template<typename InputType>
TEMPLATED_PROPERTY_TYPE_INPUTS(Atom, InputType) {
    using input_t = const InputType&;
    auto rv       = pluginplay::declare_input().add_field<input_t>("Atom ID");
    rv.at("Atom ID").set_description("The identifying feature of the atom");
    return rv;
}

template<typename InputType>
TEMPLATED_PROPERTY_TYPE_RESULTS(Atom, InputType) {
    using atom_t = type::atom;
    auto rv      = pluginplay::declare_result().add_field<atom_t>("Atom");
    rv.at("Atom").set_description("The requested Atom");
    return rv;
}

/// Typedef for a module that returns atoms based on atomic number
using AtomFromZ = Atom<type::atomic_number>;

/// Typedef for a module that returns atoms from a string (e.g. atomic symbol)
using AtomFromSym = Atom<type::atomic_symbol>;

} // namespace simde
