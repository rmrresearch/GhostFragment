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

DECLARE_PROPERTY_TYPE(IntegralShape);

PROPERTY_TYPE_INPUTS(IntegralShape) {
    using bases_t = const std::vector<simde::type::ao_basis_set>&;
    auto rv       = pluginplay::declare_input().add_field<bases_t>("bases");
    rv["bases"].set_description("The basis sets of the integral");
    return rv;
}

PROPERTY_TYPE_RESULTS(IntegralShape) {
    using shape_t = typename simde::type::tensor::shape_type;
    auto rv       = pluginplay::declare_result().add_field<shape_t>("Shape");
    rv["Shape"].set_description("The shape of the integral");
    return rv;
}

} // namespace simde
