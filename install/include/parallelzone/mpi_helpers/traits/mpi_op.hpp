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
#include <algorithm>
#include <functional>
#include <mpi.h>

namespace parallelzone::mpi_helpers {

/** @brief Maps a functor to an MPI operation.
 *
 *  In C++ when an algorithm needs a generic function, one typically passes a
 *  functor (or lambda). This trait maps the functors in the C++ standard
 *  library to their MPI operation counterparts. This is the primary template
 *  for such mappings. The primary template is selected when MPIOp<T> is not
 *  specialized for a type @p T. The primary template contains a single member
 *  `value` which is set to false. `value` is a flag indicating whether or no
 *  @p T maps to an MPI_Op type.
 *
 *  Specializations of MPIOp should define a static constexpr member op()
 *  which returns the correct MPI_Op type and inherit from std::true_type.
 *
 *  @tparam T The functor type being mapped to an MPI operation
 */
template<typename T>
struct MPIOp : std::false_type {};

/// Wraps the process of associating functor @p cxx_op with the MPI operation
/// @p mpi_op. @p cxx_op is just the name of the functor (no template params)
#define REGISTER_OP(cxx_op, mpi_op)            \
    template<typename T>                       \
    struct MPIOp<cxx_op<T>> : std::true_type { \
        static auto op() { return mpi_op; }    \
    }

REGISTER_OP(std::plus, MPI_SUM);
REGISTER_OP(std::multiplies, MPI_PROD);
REGISTER_OP(std::logical_and, MPI_LAND);
REGISTER_OP(std::bit_and, MPI_BAND);
REGISTER_OP(std::logical_or, MPI_LOR);
REGISTER_OP(std::bit_or, MPI_BOR);
REGISTER_OP(std::bit_xor, MPI_BXOR);

#undef REGISTER_OP

/** @brief Convenience variable for determining if a type @p T maps to an MPI_Op
 *         or not.
 *
 *  This variable simply aliases the value of MPIOp<T>::value.
 *
 *  @tparam T The type we are attempting to map to an MPI_Op.
 */
template<typename T>
constexpr auto has_mpi_op_v = MPIOp<T>::value;

/** @brief Convenience variable for getting the MPI_Op @p T maps to.
 *
 *  This variable simply aliases the result of calling MPIOp<T>::op().
 *  Attempting to instantiate this variable for types @p T for which
 *  has_mpi_op_v<T> is false will result in a compile error along the lines of:
 *  "MPIOp<T> has no member op".
 *
 *  @tparam T The type we want to map to an MPI_Op
 */
template<typename T>
static auto mpi_op_v = MPIOp<T>::op();

} // namespace parallelzone::mpi_helpers
