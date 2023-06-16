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

/** @brief Performs a traditional eigen solve on a matrix @p X.
 *
 *  This function will compute the eigen values and eigen vectors of the matrix
 *  @p X.
 *
 *  @param[in] X A symmetric matrix.
 *
 *  @return A pair of tensors, such that first tensor is a vector containing the
 *          eigenvalues and the second tensor is a matrix whose colums are the
 *          eigenvectors.
 */
std::pair<ScalarTensorWrapper, ScalarTensorWrapper> eigen_solve(
  const ScalarTensorWrapper& X);

/** @brief Performs a generalized eigen solve.
 *
 *  @param[in] X The (symmetric) matrix to diagonalize.
 *  @param[in] S The (symmetric) metric matrix.
 *
 *  @return A pair of tensors, such that the first tensor is a vector containing
 *          the eigenvalues, and the second tensor is a matrix whose columsn are
 *          the eigenvectors.
 */
std::pair<ScalarTensorWrapper, ScalarTensorWrapper> eigen_solve(
  const ScalarTensorWrapper& X, const ScalarTensorWrapper& S);

ScalarTensorWrapper cholesky_linv(const ScalarTensorWrapper& M);

/** @brief Raises a Hermitian matrix to a power.
 *
 *  This function returns the matrix which behaves as the matrix @p S raised to
 *  the power @p pow. This is NOT the same as raising each element of @p S to
 *  the power @p pow (unless @p S is diagonal). By "behaves like" we mean that
 *  for integer powers @f$p@f$:
 *
 *  @f[
 *  S^p = \sum_{jk\cdots} S_{ij}S_{jk}\cdots
 *  @f]
 *
 *  where the ellipses contain @f$p-2@f$ more matrix multiplications. Fractional
 *  power @f$p=\frac{1}{q}@f$ is the @f$q@f$-th root of the matrix, and negative
 *  powers are powers/roots of the inverse of @p S.
 *
 *  @param[in] S The matrix we are raising to power @p pow.
 *  @param[in] pow The power we are raising @p S to.
 *
 *  @return A matrix which behaves like @p S raised to the power @p pow.
 */
ScalarTensorWrapper hmatrix_pow(const ScalarTensorWrapper& S, double pow);

/** @brief Performs singular value decomposition on matrix @p M and returns the
 *         singular values.
 *
 *  @param[in] M A matrix.
 *
 *  @return A vector containing the singular values of the matrix.
 */
ScalarTensorWrapper SVDValues(const ScalarTensorWrapper& M);

/** @brief Performs singular value decomposition on matrix @p M and returns the
 *         singular values and left vectors.
 *
 *  @param[in] M A matrix.
 *
 *  @return A pair of tensors, such that the first is a vector containing the
 *          singular values of the matrix, and the second contains the left
 *          singular vectors.
 */
std::pair<ScalarTensorWrapper, ScalarTensorWrapper> SVDLeft(
  const ScalarTensorWrapper& M);

/** @brief Performs singular value decomposition on matrix @p M and returns the
 *         singular values and right vectors.
 *
 *  @param[in] M A matrix.
 *
 *  @return A pair of tensors, such that the first is a vector containing the
 *          singular values of the matrix, and the second contains the right
 *          singular vectors.
 */
std::pair<ScalarTensorWrapper, ScalarTensorWrapper> SVDRight(
  const ScalarTensorWrapper& M);

/** @brief Performs singular value decomposition on matrix @p M and returns the
 *         singular values and vectors.
 *
 *  @param[in] M A matrix.
 *
 *  @return A tuple of three tensors, such that the first is a vector containing
 *          the singular values of the matrix, the second contains the left
 *          singular vectors, and the third contains the right singular vectors.
 */
std::tuple<ScalarTensorWrapper, ScalarTensorWrapper, ScalarTensorWrapper> SVD(
  const ScalarTensorWrapper& M);

} // namespace tensorwrapper::tensor
