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
#include <complex>
#include <mpi.h>
#include <type_traits>

namespace parallelzone::mpi_helpers {

/** @brief Primary template for mapping type @p T to its MPI enum.
 *
 *  Each MPI implementation needs to define MPI enumerations for types like
 *  MPI_DOUBLE and MPI_INT. The type of those enums is up to the implementation.
 *  This class aids in mapping unqualified C++ type @p T to its MPI data type
 *  (if it exists). This has two parts. First, for every @p T which maps to an
 *  MPI data type, MPIDataType<T>::value will be set to true; for all other @p T
 *  MPIDataType<T>::value will be false. Second, if @p T maps to an MPI data
 *  type, then MPIDataType<T>::type() will return this type (N.B. this is a
 *  function and not a typedef to get around weirdness with how various MPI
 *  vendors implement the enumerations).
 *
 *  @tparam T The type we are mapping to an MPI data type.
 */
template<typename T>
struct MPIDataType : std::false_type {};

/// Facilitates mapping C++ type @p cxx_type to MPI enumeration @p mpi_type
#define REGISTER_TYPE(cxx_type, mpi_type)           \
    template<>                                      \
    struct MPIDataType<cxx_type> : std::true_type { \
        static auto type() { return mpi_type; }     \
    }

REGISTER_TYPE(char, MPI_CHAR);
REGISTER_TYPE(signed short, MPI_SHORT);
REGISTER_TYPE(signed int, MPI_INT);
REGISTER_TYPE(signed long, MPI_LONG);
REGISTER_TYPE(signed char, MPI_SIGNED_CHAR);
REGISTER_TYPE(unsigned char, MPI_UNSIGNED_CHAR);
REGISTER_TYPE(unsigned short, MPI_UNSIGNED_SHORT);
REGISTER_TYPE(unsigned int, MPI_UNSIGNED);
REGISTER_TYPE(unsigned long int, MPI_UNSIGNED_LONG);
REGISTER_TYPE(float, MPI_FLOAT);
REGISTER_TYPE(double, MPI_DOUBLE);
REGISTER_TYPE(long double, MPI_LONG_DOUBLE);
REGISTER_TYPE(bool, MPI_C_BOOL);
REGISTER_TYPE(std::complex<float>, MPI_C_FLOAT_COMPLEX);
REGISTER_TYPE(std::complex<double>, MPI_C_DOUBLE_COMPLEX);
REGISTER_TYPE(std::complex<long double>, MPI_C_LONG_DOUBLE_COMPLEX);
REGISTER_TYPE(std::byte, MPI_BYTE);

#undef REGISTER_TYPE

/// Convenience variable for determining if @p T maps to an MPI data type
template<typename T>
static constexpr bool has_mpi_data_type_v = MPIDataType<T>::value;

/** @brief Convenience variable for getting the MPI data type @p T maps to.
 *
 *  Attempting to use this variable with a type @p T for which
 *  `has_mpi_data_type_v<T>` is false will result in a compile error along the
 *  lines of "MPIDataType<T> has no member type()".
 *
 *  @tparam T The type to map to its MPI data type.
 */
template<typename T>
static inline auto mpi_data_type_v = MPIDataType<T>::type();

/** @brief Facilitates using SFINAE based on whether or not @p T has an MPI data
 *         type associated with it.
 *
 *  This template type is useful for SFINAE purposes, whereby this type can be
 *  used enable/disable an option based on whether or not @p T has a
 *  corresponding MPI type.
 *
 *  @tparam T The type we are dispatching on.
 *  @tparam U If has_mpi_data_type<T> is true, enable_if_mpi_data_type_t will be
 *            a typedef of @p U. By default U is `void`.
 */
template<typename T, typename U = void>
using enable_if_has_mpi_data_type_t =
  std::enable_if_t<has_mpi_data_type_v<T>, U>;

} // namespace parallelzone::mpi_helpers
