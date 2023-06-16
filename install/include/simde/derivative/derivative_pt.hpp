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
#include <pluginplay/pluginplay.hpp>
#include <simde/derivative/traits.hpp>
#include <simde/types.hpp>

namespace simde {

/** @brief Declares the Derivative property type.
 *
 *  The Derivative template property type is templated on the quantity we are
 *  taking the derivative of and the type we are taking the derivative with
 *  respect to. For example:
 *
 *  ```.cpp
 *  Derivative<AOEnergy, Molecule>;
 *  ```
 *
 *  is the property type for a module which computes the gradient of the total
 *  (AO-based) energy with respect to nuclear coordinates.
 *
 *  N.B. that property types for higher order derivatives, e.g., Hessians, can
 *  be formed by nesting Derivative specializations. For example the Hessian
 *  of the total (AO-based) energy, with respect to nuclear coordinates, is:
 *
 *  ```.cpp
 *  Derivative<Derivative<AOEnergy, Molecule>, Molecule>;
 *  ```
 *
 *  @tparam PT2Differentiate The unqualified property type being differentiated.
 *  @tparam WithRespectTo The unqualified type we are taking the derivative with
 *                        respect to.
 */
template<typename PT2Differentiate, typename WithRespectTo>
DECLARE_TEMPLATED_PROPERTY_TYPE(Derivative, PT2Differentiate, WithRespectTo);

template<typename PT2Differentiate, typename WithRespectTo>
TEMPLATED_PROPERTY_TYPE_INPUTS(Derivative, PT2Differentiate, WithRespectTo) {
    using my_type = Derivative<PT2Differentiate, WithRespectTo>;
    auto desc     = "Arg " + std::to_string(derivative_order_v<my_type>);
    return PT2Differentiate::inputs().template add_field<WithRespectTo>(desc);
}

template<typename PT2Differentiate, typename WithRespectTo>
TEMPLATED_PROPERTY_TYPE_RESULTS(Derivative, PT2Differentiate, WithRespectTo) {
    return pluginplay::declare_result().template add_field<type::tensor>(
      "Derivative");
}

} // namespace simde
