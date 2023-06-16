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

template<typename OperatorType>
DECLARE_TEMPLATED_PROPERTY_TYPE(ShellNorms, OperatorType);

//------------------------Implementations---------------------------------------

template<typename OperatorType>
TEMPLATED_PROPERTY_TYPE_INPUTS(ShellNorms, OperatorType) {
    using basis_type = const simde::type::ao_space&;
    OperatorType op;
    auto op_key = op.as_string();
    auto rv     = pluginplay::declare_input()
                .add_field<basis_type>("bra")
                .template add_field<const OperatorType&>(op_key)
                .template add_field<basis_type>("ket");
    rv["bra"].set_description("The first basis set");
    rv[op_key].set_description("The integral operator");
    rv["ket"].set_description("The second basis set");
    return rv;
}

template<typename OperatorType>
TEMPLATED_PROPERTY_TYPE_RESULTS(ShellNorms, OperatorType) {
    using return_type = std::vector<std::vector<double>>;
    auto rv =
      pluginplay::declare_result().add_field<return_type>("Screening Matrix");
    rv["Screening Matrix"].set_description(
      "The Cauchy Schwarz screening matrix");
    return rv;
}

} // namespace simde
