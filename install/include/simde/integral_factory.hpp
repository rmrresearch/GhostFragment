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

template<typename OpType>
DECLARE_TEMPLATED_PROPERTY_TYPE(IntegralFactory, OpType);

template<typename OpType>
TEMPLATED_PROPERTY_TYPE_INPUTS(IntegralFactory, OpType) {
    using ao_basis_set_input_t = const std::vector<type::ao_basis_set>&;
    OpType op;
    auto op_key = op.as_string();
    auto rv     = pluginplay::declare_input()
                .add_field<ao_basis_set_input_t>("Basis Sets")
                .template add_field<const OpType&>(op_key)
                .template add_field<size_t>("Derivative Order");
    rv.at("Basis Sets")
      .set_description("A vector of the basis sets used in the integrals.");
    rv.at(op_key).set_description("The operator for the desired integrals.");
    rv.at("Derivative Order").set_description("The derivative order");
    return rv;
}

template<typename OpType>
TEMPLATED_PROPERTY_TYPE_RESULTS(IntegralFactory, OpType) {
    using return_t = type::integral_factory;
    auto rv =
      pluginplay::declare_result().add_field<return_t>("Integral Factory");
    rv.at("Integral Factory")
      .set_description("An factory to compute blocks of the desired integral "
                       "for the given basis sets");
    return rv;
}

/// Typedef common cases
using ERIFactory     = IntegralFactory<type::el_el_coulomb>;
using KineticFactory = IntegralFactory<type::el_kinetic>;
using NuclearFactory = IntegralFactory<type::el_nuc_coulomb>;
using OverlapFactory = IntegralFactory<type::el_identity>;
using STGFactory     = IntegralFactory<type::el_el_stg>;
using YukawaFactory  = IntegralFactory<type::el_el_yukawa>;
using F12Factory     = IntegralFactory<type::el_el_f12_commutator>;

} // namespace simde
