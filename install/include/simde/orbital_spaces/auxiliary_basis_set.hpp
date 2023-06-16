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

DECLARE_PROPERTY_TYPE(AuxiliaryBasisSet);

PROPERTY_TYPE_INPUTS(AuxiliaryBasisSet) {
    using basis_type = const simde::type::ao_space&;
    auto rv =
      pluginplay::declare_input().add_field<basis_type>("AtomicBasisSet");
    rv["AtomicBasisSet"].set_description("The atomic basis set");
    return rv;
}

PROPERTY_TYPE_RESULTS(AuxiliaryBasisSet) {
    using basis_type = simde::type::ao_space;
    auto rv =
      pluginplay::declare_result().add_field<basis_type>("AuxiliaryBasisSet");
    rv["AuxiliaryBasisSet"].set_description("The density fitting basis set");
    return rv;
}

} // namespace simde