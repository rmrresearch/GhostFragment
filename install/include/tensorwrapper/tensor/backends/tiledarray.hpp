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
#include <TiledArray/dist_array.h>
#include <TiledArray/tensor.h>

/* This file is intended to handle the interface between TiledArray and
 * TensorWrapper structures, e.g. wrapping or unwrapping TA distarrays.
 *
 * !! This is NOT intended to be included in the courtesy headers. !!
 */

namespace tensorwrapper::tensor::backends {

/** @brief Wrap a sparse distarray of doubles inside a Tensorwrapper
 *
 *  @param[in] ta A sparse distarray of doubles.
 *
 *  @return A ScalarTensorWrapper wrapping the input array
 */
ScalarTensorWrapper wrap_ta(TA::TSpArrayD ta);

/** @brief Wrap a sparse distarray of tensors of doubles inside a Tensorwrapper
 *
 *  @param[in] ta A sparse distarray of tensors of doubles.
 *
 *  @return A TensorOfTensorsWrapper wrapping the input array
 */
TensorOfTensorsWrapper wrap_ta(TA::TSpArray<TA::Tensor<double>> ta);

/** @brief Unwrap a sparse distarray of doubles inside a Tensorwrapper
 *
 *  @param[in] tw A ScalarTensorWrapper.
 *
 *  @return The underlying TiledArray structure
 */
TA::TSpArrayD& unwrap_ta(ScalarTensorWrapper& tw);

/** @brief Unwrap a read-only sparse distarray of doubles inside a Tensorwrapper
 *
 *  @param[in] tw A ScalarTensorWrapper.
 *
 *  @return The underlying TiledArray structure
 */
const TA::TSpArrayD& unwrap_ta(const ScalarTensorWrapper& tw);

/** @brief Unwrap a sparse distarray of tensors of doubles inside a
 *         Tensorwrapper
 *
 *  @param[in] tw A TensorOfTensorsWrapper.
 *
 *  @return The underlying TiledArray structure
 */
TA::TSpArray<TA::Tensor<double>>& unwrap_ta(TensorOfTensorsWrapper& tw);

/** @brief Unwrap a read-only sparse distarray of tensors of doubles inside a
 *         Tensorwrapper
 *
 *  @param[in] tw A TensorOfTensorsWrapper.
 *
 *  @return The underlying TiledArray structure
 */
const TA::TSpArray<TA::Tensor<double>>& unwrap_ta(
  const TensorOfTensorsWrapper& tw);

} // namespace tensorwrapper::tensor::backends
