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

/** @brief The property type for modules that compute a pair energy.
 *
 *  @tparam OccType The type of the occupied orbital energies.
 *  @tparam VirtType The type of the virtual orbital energies.
 */
template<typename OccType, typename VirtType>
DECLARE_TEMPLATED_PROPERTY_TYPE(PairEnergy, OccType, VirtType);

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_INPUTS(PairEnergy, OccType, VirtType) {
    auto rv = pluginplay::declare_input()
                .add_field<const OccType&>("Occupieds")
                .template add_field<const VirtType&>("Virtuals");
    return rv;
}

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_RESULTS(PairEnergy, OccType, VirtType) {
    using tensor_type =
      std::decay_t<decltype(std::declval<OccType>().orbital_energies())>;
    auto rv =
      pluginplay::declare_result().add_field<tensor_type>("Pair Energies");
    return rv;
}

// using SparsePairEnergy =
//   PairEnergy<type::independent_space, type::independent_space>;

} // namespace simde
