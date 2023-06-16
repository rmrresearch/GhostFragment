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

/** @brief Compares two TensorWrapper instances for closeness.
 *
 *  This function will compare two tensors, @f$A@f$ and @f$B@f$, elementwise and
 *  determine if all their values are close to one another. "Close" is defined
 *  by two parameters. The absolute tolerance, @p atol, defines the effective
 *  zero for all comparisons. If for a given index @f$I@f$,
 *  @f$\mid A[I] - B[I]\mid@f$ two differs by less than @p atol, the
 *  difference is considered indistinguishable from zero and the elements the
 *  same. Particularly for very large elements achieving a difference on the
 *  order of @p atol is not always reasonable; in these cases, one cares more
 *  about the percent error. In this case
 *  @f$\frac{\mid A[I] - B[I]\mid}{\mid B[I]\mid}@f$ must
 *  be less than a relative tolerance, @p rtol.
 *
 *  This function combines these criteria and returns true if @f$A@f$ and
 *  @f$B@f$ satisfy:
 *
 *  @f[
 *     \mid A - B\mid \le atol + rtol\mid B\mid
 *  @f]
 *
 *  Note that this is **NOT** symmetric in @f$A@f$ and @f$B@f$, but is
 *  commensurate with @f$B@f$ being the reference (thereby dictating what is an
 *  acceptable relative tolerance).
 *
 *  @param[in] actual The tensor you computed and are comparing against a
 *                    reference value.
 *  @param[in] ref The tensor which @p actual is being compared to. Should
 *                 be "the correct value".
 *  @param[in] rtol The maximum percent error (as a decimal) allowed for any
 *                  particular value. Assumed to be a positive decimal. Defaults
 *                  to 1.0E-5, *i.e.*, 0.0001%.
 *  @param[in] atol The effective value of zero for comparisons. Assumed to be a
 *                  positive decimal less than 1.0. Defaults to 1.0E-8.
 *  @return True if @p actual is "close" to @p ref and false otherwise.
 */
bool allclose(const ScalarTensorWrapper& actual, const ScalarTensorWrapper& ref,
              double rtol = 1.0E-5, double atol = 1.0E-8);

/// Same as allclose except that the tensors are hierarchical
bool allclose(const TensorOfTensorsWrapper& actual,
              const TensorOfTensorsWrapper& ref, double rtol = 1.0E-5,
              double atol = 1.0E-8);

/// Same as allclose, except comparisons are done with unsigned elements
bool abs_allclose(const ScalarTensorWrapper& actual,
                  const ScalarTensorWrapper& ref, double rtol = 1.0E-5,
                  double atol = 1.0E-8);

/// Same as allclose except comparisons are done with unsigned elements
bool abs_allclose(const TensorOfTensorsWrapper& actual,
                  const TensorOfTensorsWrapper& ref, double rtol = 1.0E-5,
                  double atol = 1.0E-8);

} // namespace tensorwrapper::tensor
