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

template<typename OutputType, typename InputType>
DECLARE_TEMPLATED_PROPERTY_TYPE(TransformedWavefunction, OutputType, InputType);

template<typename OutputType, typename InputType>
TEMPLATED_PROPERTY_TYPE_INPUTS(TransformedWavefunction, OutputType, InputType) {
    using input_type = const InputType&;

    auto rv =
      pluginplay::declare_input().add_field<input_type>("Input wavefunction");

    return rv;
}

template<typename OutputType, typename InputType>
TEMPLATED_PROPERTY_TYPE_RESULTS(TransformedWavefunction, OutputType,
                                InputType) {
    auto rv =
      pluginplay::declare_result().add_field<OutputType>("Result wavefunction");

    return rv;
}

/*
using NoncanonicalToLocal =
  TransformedWavefunction<type::local_reference, type::noncanonical_reference>;

using CanonicalToLocal =
  TransformedWavefunction<type::local_reference, type::canonical_reference>;

using LocalMBToToTMB =
  TransformedWavefunction<type::local_tot_many_body, type::local_many_body>;

using LocalToLocal =
  TransformedWavefunction<type::local_reference, type::local_reference>;
*/

} // namespace simde
