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

/**
 * @brief The property type for modules that calculate atomic charges.
 */
DECLARE_PROPERTY_TYPE(AtomicCharges);

//---------------------------Implementations------------------------------------
PROPERTY_TYPE_INPUTS(AtomicCharges) {
    auto rv = pluginplay::declare_input()
                .add_field<const type::molecule&>("Molecule")
                .add_field<const type::el_density&>("Density");
    rv["Molecule"].set_description("The molecular system");
    rv["Density"].set_description("The electronic density");
    return rv;
}

PROPERTY_TYPE_RESULTS(AtomicCharges) {
    auto rv =
      pluginplay::declare_result().add_field<type::tensor>("Partial Charges");
    rv["Partial Charges"].set_description("The calculated partial charges");
    return rv;
}

} // namespace simde
