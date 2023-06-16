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

/** @brief Elminates linear dependencies in the provided transformation.
 *
 *  Given a matrix of column vectors, @p C, and their inner products, @p S, such
 *  that the inner product of vector @f$i@f$ with vector @f$j@f$ is given by
 *  @f$S_{ij}@f$. This function will return a new set of linearly-independent
 *  vectors by diagonalizing @p S and dropping vectors associated with eigen
 *  values below @p thresh.
 *
 *  @param[in] C A set of column vectors which may have some linear
 *               dependencies.
 *  @param[in] S The overlap of the column vectors.
 *  @param[in] thresh Vectors associated with eigen values below this value will
 *                    be dropped.
 *
 *  @return The new, linearly-independent, vectors.
 */
ScalarTensorWrapper remove_redundancy(const ScalarTensorWrapper& C,
                                      const ScalarTensorWrapper& S,
                                      double thresh = 1.0E-8);

} // namespace tensorwrapper::tensor
