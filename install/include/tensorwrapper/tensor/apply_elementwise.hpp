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
#include "tensorwrapper/tensor/tensor_wrapper.hpp"
#include <functional>

namespace tensorwrapper::tensor {

/** @brief Creates a new tensor by applying a function elementwise to an
 *         existing tensor.
 *
 *  This function is a convenience function for creating a new tensor whose
 *  initial elements can be determined solely based on the element values of
 *  another tensor.
 *
 * @param[in] input The tensor supplying the input values @p op will be called
 *                  with.
 * @param[in] op The function to apply to each element of @p input to generate
 *               the resulting tensor.
 * @return A new tensor having the same shape and distribution as @p input. The
 *         @f$i@f$-th element of the new tensor is the result of `op(input[i])`,
 *         where `input[i]` is the @f$i@f$-th element of @p input.
 */
ScalarTensorWrapper apply_elementwise(const ScalarTensorWrapper& input,
                                      const std::function<double(double)>& fxn);

/** @brief Modifies an existing tensor by applying a function elementwise to its
 *         values.
 *
 *  This function is a convenience function for modifying an existing tensor
 *  by an elementwise in-place operation.
 *
 * @param[in] input The tensor supplying the input values to be changed in-place
 *                  by @p op.
 * @param[in] op The function to apply to each element of @p input to modify
 *               the values in-place.
 */
void apply_elementwise_inplace(ScalarTensorWrapper& input,
                               const std::function<void(double&)>& fxn);

} // namespace tensorwrapper::tensor
