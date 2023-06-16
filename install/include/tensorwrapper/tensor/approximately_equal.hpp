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
#include "tensorwrapper/tensor/allclose.hpp"
#include "tensorwrapper/tensor/allocator/allocator.hpp"
#include "tensorwrapper/tensor/approximately_equal.hpp"
#include "tensorwrapper/tensor/shapes/shapes.hpp"
#include "tensorwrapper/tensor/tensor_wrapper.hpp"

namespace tensorwrapper::tensor {

/** @brief Compares two TensorWrapper instances for closeness.
 *
 *  This function will compare two tensors, @p actual and @p ref, elementwise
 * and determine if all their values are close to one another, as specified in
 * the file "tensorwrapper/include/tensor/allclose.hpp". The function also
 * compares shape and allocator attributes of the two tensors.
 *
 *  @param[in] ref The tensor you computed and are comparing against a
 *                    reference value.
 *  @param[in] ref The tensor which @p actual is being compared to. Should
 *                 be "the correct value".
 *  @param[in] rtol The maximum percent error (as a decimal) allowed for any
 *                  particular value. Assumed to be a positive decimal. Defaults
 *                  to 1.0E-5, *i.e.*, 0.001%.
 *  @param[in] atol The effective value of zero for comparisons. Assumed to be a
 *                  positive decimal less than 1.0. Defaults to 1.0E-8.
 *  @return True if @p actual is "close" to @p ref and false otherwise.
 */

template<typename FieldType>
bool are_approximately_equal(const TensorWrapper<FieldType>& actual,
                             const TensorWrapper<FieldType>& ref, double rtol,
                             double atol) {
    return (actual.allocator().is_equal(ref.allocator())) &&
           (actual.shape() == ref.shape()) && allclose(actual, ref, rtol, atol);
}

} // namespace tensorwrapper::tensor
