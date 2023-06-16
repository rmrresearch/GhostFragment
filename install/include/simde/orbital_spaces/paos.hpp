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
#include <pluginplay/pluginplay.hpp>

namespace simde {

template<typename InputOrbitals, typename OutputOrbitals>
DECLARE_TEMPLATED_PROPERTY_TYPE(PAOs, InputOrbitals, OutputOrbitals);

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_INPUTS(PAOs, InputOrbitals, OutputOrbitals) {
    auto rv =
      pluginplay::declare_input().add_field<const InputOrbitals&>("Orbitals");
    return rv;
}

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_RESULTS(PAOs, InputOrbitals, OutputOrbitals) {
    auto rv = pluginplay::declare_result().add_field<OutputOrbitals>("PAOs");
    return rv;
}

using paos = PAOs<type::derived_space, type::derived_space>;

} // namespace simde
