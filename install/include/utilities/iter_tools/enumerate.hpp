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
#include "utilities/iter_tools/range.hpp"
#include "utilities/iter_tools/zip.hpp"
#include <array>

namespace utilities {

/** @brief Enumerates the elements in a container.
 *
 *  The Enumerate class simulates a container filled with tuples such that the
 *  i-th tuple is `std::tuple{i, A[i], B[i], ...}` where `A`, `B`, etc. are
 *  containers. The Enumerate class does not actually hold all of these
 *  tuples, instead they are computed on-the-fly.
 *
 *  @note This class is a thin-wrapper around the Zip class and works by zipping
 *        a Range to the containers. Users should consult the Zip class's
 *        documentations for more details, all of which are pertinent to this
 *        class.
 *
 *  @tparam Containers The types of the containers which are getting their
 *                     elements enumerated.
 */
template<typename... Containers>
class Enumerate : public Zip<Range<std::size_t>, Containers...> {
public:
    /** @brief Creates a new Enumerate instance by zipping together the
     *         provided containers.
     *
     *  Enumerate is ultimately a thin wrapper around creating a Range object
     *  and zipping it to the provided containers. That is what this ctor does.
     *  The containers that are provided to this ctor are forwarded to the
     *  Zip base class's ctor. Thus one should also see the Zip class's ctor for
     *  more details pertaining to this class's usage.
     *
     *  @param[in] containers The containers whose content this class is being
     *                        enumerated.
     *
     *  @throw ??? if the Zip class's ctor throws. Same throw guarantee.
     */
    explicit Enumerate(Containers... containers);
}; // class Enumerate

// -------------------------------Implementations-------------------------------

template<typename... Args>
Enumerate(Args&&...) -> Enumerate<Args...>;

template<typename... Containers>
Enumerate<Containers...>::Enumerate(Containers... containers) :
  Zip<Range<std::size_t>, Containers...>(
    Range([&]() {
        std::array<std::size_t, sizeof...(Containers)> sizes{
          containers.size()...};
        return *std::min_element(sizes.begin(), sizes.end());
    }()),
    containers...) {}

} // namespace utilities
