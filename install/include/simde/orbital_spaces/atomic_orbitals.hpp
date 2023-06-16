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
#include <pluginplay/property_type/property_type.hpp>
#include <simde/types.hpp>

namespace simde {

/** @brief PT for going from a set of nuclei to a set of point-center orbitals.
 *
 *  Modules which take a set of nuclei and return a set of point-centered
 *  (in general they will be atom-centered, but in theory there could be
 *  mid-bond functions or something) are said to obey the AtomicOrbitals PT.
 *
 *  Examples of algorithms that could fall under this PT are:
 *
 *  - The usual AO basis formation (i.e., looking up hard-coded parameters for
 *    a specific atomic number and taking the union of the translated orbitals)
 *  - Computing mid-bond functions
 *  - User-specified bases via lambda modules
 *  - Opaque processing of an assigned set of AOs (e.g., nesting
 *    AtomicOrbitals modules so that the inner one forms the usual AO basis and
 *    the latter prunes diffuse functions or something)
 */
DECLARE_PROPERTY_TYPE(AtomicOrbitals);

PROPERTY_TYPE_INPUTS(AtomicOrbitals) {
    using mol_t = const type::molecule&;
    auto rv     = pluginplay::declare_input().add_field<mol_t>("Nuclei");
    return rv;
}

PROPERTY_TYPE_RESULTS(AtomicOrbitals) {
    using aos_t = type::ao_space;
    auto rv = pluginplay::declare_result().add_field<aos_t>("Atomic Orbitals");
    return rv;
}

} // namespace simde
