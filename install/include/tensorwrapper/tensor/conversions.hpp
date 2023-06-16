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

namespace tensorwrapper::tensor {

/** @brief Flattens a tensor out into an std::vector.
 *
 *  This function will replicate the provided tensor (assuming it is distributed
 *  to begin with) and then flatten it into a vector. The flattening will
 *  occur in row-major format.
 *
 *  @note This function is primarily intended for use with low rank @p t, e.g.
 *        in taking actions based on the value of an eigenvalue. Direct access
 *        of high-rank tensors should be avoided.
 *
 *  @param[in] t The tensor to vectorize.
 *
 *  @return The tensor vectorized into an std::vector.
 */
std::vector<double> to_vector(const ScalarTensorWrapper& t);

/** @brief Flattens a tensor out into a contiguous buffer
 *
 *  This function will replicate the provided tensor (assuming it is distributed
 *  to begin with) and then flatten it into a contiguous buffer. The flattening
 * will occur in row-major format.
 *
 *  @note This function is primarily intended for use with low rank @p t, e.g.
 *        in taking actions based on the value of an eigenvalue. Direct access
 *        of high-rank tensors should be avoided.
 *
 *  @param[in]    t The tensor to vectorize.
 *  @param[out]   buffer_begin The start of the contiguous buffer
 *  @param[out]   buffer_end   The end of the contiguous buffer
 */
void to_contiguous_buffer(const ScalarTensorWrapper& t, double* buffer_begin,
                          const double* buffer_end);

/** @brief Convert a std::vector into a 1D ScalarTensorWrapper
 *
 *  @param[in] v The std::vector to wrap.
 *
 *  @return A 1D ScalarTensorWrapper wrapping the values of @p v.
 */
ScalarTensorWrapper wrap_std_vector(std::vector<double> v);

} // namespace tensorwrapper::tensor
