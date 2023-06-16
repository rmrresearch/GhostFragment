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
#include <optional>
#include <parallelzone/mpi_helpers/traits/needs_serialized.hpp>

namespace parallelzone::mpi_helpers {

/** @brief Works out what the result of gathering objects of type @p T.
 *
 *  Let's start with the easiest scenario @p T needs to be serialized. In this
 *  case, we internally serialize the @p T object to binary and get back a
 *  binary buffer. Still internal, on the root process we need to convert from
 *  the binary buffer to a std::vector<T> (the return of gather is N objects of
 *  type @p T, one for each rank which is arguably most naturally expressed as
 *  a std::vector). Ranks other than root get nothing. This dependent output is
 *  best expressed as a std::optional, so our final type is
 *  `std::optional<vector<T>>`.
 *
 *  Now the harder scenario, @p T doesn't need to be serialized. In this case
 *  we directly pass the @p T object to gather, the hard part is where we go
 *  from there. If @p T is something like std::vector<double> we could get
 *  back a return of std::vector<std::vector<double>>, but a return of
 *  std::vector<double> is more efficient (i.e., we flatten it).
 *
 *  All of this logic is wrapped up in this type def.
 *
 *  @tparam T The input type to the gather call. This should be an unqualified
 *            type.
 *
 */
template<typename T>
using gather_return_t =
  std::optional<std::conditional_t<needs_serialized_v<T>, std::vector<T>, T>>;

} // namespace parallelzone::mpi_helpers
