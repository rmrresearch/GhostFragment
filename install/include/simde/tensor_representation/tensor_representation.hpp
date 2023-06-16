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
#include "simde/tensor_representation/ao_integrals.hpp"
#include "simde/tensor_representation/ao_tensor_representation.hpp"
#include "simde/tensor_representation/bra_ket.hpp"
#include "simde/tensor_representation/general_ao_tensor_representation.hpp"
#include "simde/tensor_representation/general_transformed_tensor_representation.hpp"
#include "simde/tensor_representation/integral_shape.hpp"
#include "simde/tensor_representation/tensor_representation_fxn.hpp"
#include "simde/tensor_representation/transformed.hpp"
#include "simde/tensor_representation/transformed_tensor_representation.hpp"
#include "simde/tensor_representation/type_traits.hpp"

namespace simde {

template<typename T>
using space_map_t = typename detail_::TensorRepTraits<T>::map_type;

using TotalCanonicalEnergy = TotalEnergy<type::canonical_reference>;

using WfEnergy [[deprecated("Use TotalCanonicalEnergy instead")]] =
  TotalCanonicalEnergy;

using CanonicalElectronicEnergy = ElectronicEnergy<type::canonical_reference>;

using CanonicalCorrelationEnergy =
  CorrelationEnergy<type::canonical_reference, type::canonical_many_body>;

// using LocalCorrelationEnergy =
//   CorrelationEnergy<type::local_tot_reference, type::local_tot_many_body>;

} // namespace simde
