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

namespace simde {

DECLARE_PROPERTY_TYPE(ExchangeCorrelationEnergy);

PROPERTY_TYPE_INPUTS(ExchangeCorrelationEnergy) {
    using const_ao_space_t = const simde::type::ao_space;
    using const_molecule_t = const simde::type::molecule&;
    using operator_t       = simde::type::el_scf_xc;

    return pluginplay::declare_input()
      .add_field<const_ao_space_t>("bra")
      .add_field<const operator_t&>("xc")
      .add_field<const_ao_space_t>("ket");
}

PROPERTY_TYPE_RESULTS(ExchangeCorrelationEnergy) {
    return pluginplay::declare_result().add_field<double>("EXC");
}

using MeanFieldXCEnergy = ExchangeCorrelationEnergy;
} // namespace simde
