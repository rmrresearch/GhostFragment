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

/** @brief The property for a module that returns an electronic configuration
 * based on the atomic identity.
 */
template<typename InputType, typename ConfType>
DECLARE_TEMPLATED_PROPERTY_TYPE(ElecConfiguration, InputType, ConfType);

template<typename InputType, typename ConfType>
TEMPLATED_PROPERTY_TYPE_INPUTS(ElecConfiguration, InputType, ConfType) {
    using input_t = const InputType&;
    auto rv       = pluginplay::declare_input().add_field<input_t>("Atom ID");
    rv.at("Atom ID").set_description("The identifying feature of the atom");
    return rv;
}

template<typename InputType, typename ConfType>
TEMPLATED_PROPERTY_TYPE_RESULTS(ElecConfiguration, InputType, ConfType) {
    auto rv = pluginplay::declare_result().add_field<ConfType>(
      "Electronic Configuration");
    rv.at("Electronic Configuration")
      .set_description("The electronic configuration for the specified atom");
    return rv;
}

/// Typedef for elec config from Z
using ElecConfigFromZ =
  ElecConfiguration<type::atomic_number, std::vector<type::size>>;

/// Typedef for elec config from a string
using ElecConfigFromSym =
  ElecConfiguration<type::atomic_symbol, std::vector<type::size>>;

/// Typedef for fractional elec config from Z
using FracConfigFromZ =
  ElecConfiguration<type::atomic_number, std::vector<double>>;

/// Typedef for fractional elec config from a string
using FracConfigFromSym =
  ElecConfiguration<type::atomic_symbol, std::vector<double>>;

/// Typedef for full elec config from Z
using FullConfigFromZ =
  ElecConfiguration<type::atomic_number, type::full_elec_conf>;

/// Typedef for full elec config from a string
using FullConfigFromSym =
  ElecConfiguration<type::atomic_symbol, type::full_elec_conf>;

} // namespace simde
