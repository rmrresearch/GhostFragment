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
#include <chemist/orbital_space/orbital_space.hpp>
#include <simde/tensor_representation/mode_to_basis_map.hpp>
#include <simde/types.hpp>

namespace simde::detail_ {

/** @brief Struct used to synchronized input types across the tensor
 *         representation component of SimDE.
 *
 *
 *  @tparam T The orbital space we are generating types for. Assumed to be one
 *            of (or implicitly convertible to one of):
 *            - type::ao_space,
 *            - type::derived_space,
 *            - type::tot_derived_space, or
 *            - type::independent_space
 *
 */
template<typename T>
struct TensorRepTraits {
private:
    /// Base type for AO spaces
    using ao_space_type = type::ao_space;

    /// Base type for (non-ToT) derived spaces
    using derived_space_type = type::derived_space;

    /// Base type for (ToT) derived spaces
    using tot_space_type = type::tot_derived_space;

public:
    /// Type of a map from mode offsets to orbital spaces
    using map_type = ModeToBasisMap<T>;

    /// Type used to index modes in the intergral, is unsigned integer-like
    using mode_type = typename map_type::mode_type;

    /// Type used to hold a read-only reference to an orbital space of type @p T
    using const_reference = typename map_type::const_basis_set_reference;

    /// Is T an AO space?
    static constexpr bool is_ao_space = std::is_base_of_v<ao_space_type, T>;

    /// Is T a normal, non-ToT, transformation?
    static constexpr bool is_derived = std::is_base_of_v<derived_space_type, T>;

    /// Is T a ToT transformation?
    static constexpr bool is_tot_derived = std::is_base_of_v<tot_space_type, T>;

    /// Is T an independent space?
    static constexpr bool is_independent =
      chemist::orbital_space::is_independent_space_v<T>;
};

} // namespace simde::detail_
