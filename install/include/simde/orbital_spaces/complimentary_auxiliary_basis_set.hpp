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

template<typename ResultBasis, typename InputBasis>
DECLARE_TEMPLATED_PROPERTY_TYPE(ComplimentaryAuxiliaryBasisSet, ResultBasis,
                                InputBasis);

template<typename ResultBasis, typename InputBasis>
TEMPLATED_PROPERTY_TYPE_INPUTS(ComplimentaryAuxiliaryBasisSet, ResultBasis,
                               InputBasis) {
    auto rv =
      pluginplay::declare_input().add_field<const InputBasis&>("orbital basis");
    return rv;
}

template<typename ResultBasis, typename InputBasis>
TEMPLATED_PROPERTY_TYPE_RESULTS(ComplimentaryAuxiliaryBasisSet, ResultBasis,
                                InputBasis) {
    auto rv = pluginplay::declare_result().add_field<ResultBasis>("CABS");
    return rv;
}

using CABS =
  ComplimentaryAuxiliaryBasisSet<type::derived_space, type::ao_space>;

} // namespace simde
