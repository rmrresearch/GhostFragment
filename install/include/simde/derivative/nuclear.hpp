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
#include <simde/derivative/derivative_pt.hpp>
#include <simde/energy/ao_energy.hpp>
#include <simde/types.hpp>

namespace simde {

/** @brief Type def of Derivative for when we want the derivative
 *         with respect to nuclear coordinates.
 *
 *  This type def is used to factor out the common part of declaring derivatives
 *  with respect to nuclear coordinates.
 *
 *  @tparam T The property type we are taking the derivative of.
 */
template<typename T>
using NuclearDerivative = Derivative<T, type::molecule>;

/// Type for the gradient of an AOEnergy w.r.t. nuclear coordinates.
using AOEnergyNuclearGradient = NuclearDerivative<AOEnergy>;

/// Type for the Hessian of an AOEnergy w.r.t. nuclear coordinates
using AOEnergyNuclearHessian = NuclearDerivative<AOEnergyNuclearGradient>;

} // namespace simde
