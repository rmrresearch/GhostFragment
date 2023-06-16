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

template<typename InputOrbitals, typename OutputOrbitals>
DECLARE_TEMPLATED_PROPERTY_TYPE(QCMOs, InputOrbitals, OutputOrbitals);

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_INPUTS(QCMOs, InputOrbitals, OutputOrbitals) {
    auto rv = pluginplay::declare_input()
                .add_field<const type::fock&>("Fock Operator")
                .template add_field<const InputOrbitals&>("Orbitals");
    return rv;
}

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_RESULTS(QCMOs, InputOrbitals, OutputOrbitals) {
    auto rv = pluginplay::declare_result().add_field<OutputOrbitals>("PAOs");
    return rv;
}

/// Type of the property type for QC-NR-PAOs
using qcpaos = QCMOs<type::derived_space, type::canonical_space>;
/// Type of the property type for QC-LMOs
using qclmos = QCMOs<type::derived_space, type::canonical_space>;

} // namespace simde
