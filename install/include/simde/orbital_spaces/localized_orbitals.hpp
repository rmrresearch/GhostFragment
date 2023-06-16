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
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

/** @brief API for modules that compute localized orbitals
 *
 *  This property type is envisioned as being the property type for any module
 *  that computes localized orbitals. This accounts for conventional localized
 *  molecular orbitals, as well as things like pair-natural orbitals.
 *
 *  @tparam InputOrbitals The type of the input orbitals
 *  @tparam OutputOrbitals the type iof the output orbitals
 */
template<typename InputOrbitals, typename OutputOrbitals = InputOrbitals>
DECLARE_TEMPLATED_PROPERTY_TYPE(LocalizedOrbitals, InputOrbitals,
                                OutputOrbitals);

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_INPUTS(LocalizedOrbitals, InputOrbitals,
                               OutputOrbitals) {
    auto rv =
      pluginplay::declare_input().add_field<const InputOrbitals&>("Orbitals");
    rv["Orbitals"].set_description("The orbitals to localize");
    return rv;
}

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_RESULTS(LocalizedOrbitals, InputOrbitals,
                                OutputOrbitals) {
    auto rv =
      pluginplay::declare_result().add_field<OutputOrbitals>("Local Orbitals");
    rv["Local Orbitals"].set_description("The localized orbitals");
    return rv;
}

extern template class LocalizedOrbitals<type::derived_space>;
extern template class LocalizedOrbitals<type::canonical_space>;

} // namespace simde
