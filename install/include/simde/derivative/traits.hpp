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

#include <type_traits>

namespace simde {

/// Forward declare Derivative property type
template<typename T, typename U>
class Derivative;

namespace detail_ {

/** @brief Deduces if @p T is a specialization of Derivative.
 *
 *  This is the primary class template for the IsDerivative type trait. This
 *  template is used when @p T is not a specialization of Derivative. As such
 *  it always contains a static constexpr member `value` set to false.
 *  This class template should be partially specialized for the scenario
 *  when @p T is a specialization of Derivative.
 *
 *  @tparam T The type to inspect. This trait will determine if @p T is a
 *            specialization of Derivative. @p T is expected to be an
 *            unqualified type.
 */
template<typename T>
struct IsDerivative : std::false_type {};

/** @brief Deduces if @p T is a specialization of Derivative.
 *
 *  This partial specialization of IsDerivative is used when the template
 *  parameter is a specialization of Derivative. Instances of this class
 *  template contain a static constexpr member `value` set to true.
 *
 *  @tparam T The property type we are taking the derivative of.
 *  @tparam U The type we are taking the derivative with respect to.
 */
template<typename T, typename U>
struct IsDerivative<Derivative<T, U>> : std::true_type {};

/** @brief Deduces the derivative order of a property type.
 *
 *  This is the primary class template for the DerivativeOrder type trait. This
 *  template is not defined and attempting to instantiate it will lead to a
 *  compiler error. This template is selected when @p T is not a specialization
 *  of the Derivative class template.
 *
 *  @todo This should probably check if @p T is a property type other than a
 *        specialization of Derivative. If it is, then it should return 0.
 *
 *  @tparam T The type to inspect. This trait will determine the derivative
 *            order of the type @p T. @p T is expected to be an unqualified
 *            type.
 */
template<typename T>
struct DerivativeOrder;

/** @brief Deduces the derivative order of a property type.
 *
 *  This partial specialization is used when the template parameter for
 *  DerivativeOrder is a specialization of Derivative. The resulting class will
 *  have a member `value` set to the order of the derivative, i.e., 1 if the
 *  property type is for a gradient, 2 if the property type is for a Hessian,
 *  etc.
 *
 *  @tparam T The property type we are taking the derivative of.
 *  @tparam U The type we are taking the derivative with respect to.
 *
 */
template<typename T, typename U>
struct DerivativeOrder<Derivative<T, U>> {
private:
    /** @brief Actually works out the derivative order.
     *
     *  This method is basically a ternary condition based on whether or not
     *  @p T is itself a specialization of Derivative. If @p T is a
     *  specialization of Derivative it recurses into the class resulting from
     *  instantiating DerivativeOrder<T>. If @p T is not a specialization of
     *  Derivative it returns 1.
     *
     *  @return The number of Derivative nestings in @p T plus 1.
     */
    static constexpr std::size_t value_() {
        if constexpr(IsDerivative<T>::value) {
            return DerivativeOrder<T>::value + 1;
        } else {
            return 1;
        }
    }

public:
    /// The number of times Derivative is nested in @p T, plus 1.
    static constexpr auto value = value_();
};

} // namespace detail_

/** @brief Global constant determining if a type @p T is a specialization
 *         of Derivative.
 *
 *  This global constant is set to true if @p T is a specialization of the
 *  Derivative class template and false otherwise.
 *
 *  @tparam T The type being inspected. @p T is expected to be an uqualified
 *            type.
 */
template<typename T>
static constexpr auto is_derivative_v = detail_::IsDerivative<T>::value;

/** @brief Global constant determining the derivative order of @p T.
 *
 *  This global constant is only defined when @p T is a specialization of the
 *  Derivative class template. If @p T is a specialization  of the Derivative
 *  class template, then this constant is set to the derivative order of @p T,
 *  i.e., if @p T is a property type for a gradient this constant is set to 1,
 *  if @p T is a property type for a Hessian this constant is 2, etc.
 *
 *  @tparam T The type we want to know the derivative order of. @p T must be an
 *            unqualified specialization of Derivative for this to compile.
 */
template<typename T>
static constexpr auto derivative_order_v = detail_::DerivativeOrder<T>::value;

} // namespace simde
