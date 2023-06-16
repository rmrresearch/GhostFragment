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

/** @brief The property for a module that returns an atomic symbol based on the
 *         atomic number.
 *
 */
DECLARE_PROPERTY_TYPE(SymbolFromZ);

PROPERTY_TYPE_INPUTS(SymbolFromZ) {
    auto rv = pluginplay::declare_input().add_field<type::atomic_number>("Z");
    rv.at("Z").set_description("Atomic Number");
    return rv;
}

PROPERTY_TYPE_RESULTS(SymbolFromZ) {
    auto rv =
      pluginplay::declare_result().add_field<type::atomic_symbol>("Symbol");
    rv.at("Symbol").set_description("Atomic Symbol");
    return rv;
}

} // namespace simde
