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

/** @brief The property for a module that returns an atomic density based on the
 *         atomic identity.
 *
 */
template<typename InputType, typename DensityType>
DECLARE_TEMPLATED_PROPERTY_TYPE(AtomicDensity, InputType, DensityType);

template<typename InputType, typename DensityType>
TEMPLATED_PROPERTY_TYPE_INPUTS(AtomicDensity, InputType, DensityType) {
    using input_t = const InputType&;
    auto rv       = pluginplay::declare_input().add_field<input_t>("Atom ID");
    rv.at("Atom ID").set_description("The identifying feature of the atom");
    return rv;
}

template<typename InputType, typename DensityType>
TEMPLATED_PROPERTY_TYPE_RESULTS(AtomicDensity, InputType, DensityType) {
    auto rv =
      pluginplay::declare_result().add_field<DensityType>("Atomic Density");
    rv.at("Atomic Density")
      .set_description("The atomic density for the specified atom");
    return rv;
}

/// Typedef for modules that return atomic densities from atomic number
using AtomDenFromZ = AtomicDensity<type::atomic_number, std::vector<double>>;

/// Typedef for modules that return atomic densities from a string
using AtomDenFromSym = AtomicDensity<type::atomic_symbol, std::vector<double>>;

} // namespace simde
