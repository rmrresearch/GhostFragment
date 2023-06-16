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
#include "simde/tensor_representation/general_transformed_tensor_representation.hpp"
#include "simde/types.hpp"
namespace simde {

using TransformedERI3 = TransformedTensorRepresentation<3, type::el_el_coulomb>;
using TransformedERI4 = TransformedTensorRepresentation<4, type::el_el_coulomb>;
using TransformedExchange = TransformedTensorRepresentation<2, type::el_scf_k>;
using TransformedF12Commutator =
  TransformedTensorRepresentation<4, type::el_el_f12_commutator>;
using TransformedFock = TransformedTensorRepresentation<2, type::fock>;
using TransformedOverlap =
  TransformedTensorRepresentation<2, type::el_identity>;
using TransformedSTG4 = TransformedTensorRepresentation<4, type::el_el_stg>;
using TransformedYukawa4 =
  TransformedTensorRepresentation<4, type::el_el_yukawa>;

using TransformedLocalERI4 =
  GeneralTransformedTensorRepresentation<4, type::el_el_coulomb>;

using TransformedLocalOverlap =
  GeneralTransformedTensorRepresentation<2, type::el_identity>;

} // namespace simde
