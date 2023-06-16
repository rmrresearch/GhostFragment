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
#include "simde/types.hpp"
#include <chemist/set_theory/set_theory.hpp>
#include <pluginplay/pluginplay.hpp>

namespace simde {

/** @brief Provides users of the Fragmented PT with type information.
 *
 *  The FragmentedTraits struct is useful for users of the Fragmented property
 *  type that want to progmatically know the input or return types of a
 *  particular Fragmented instance.
 *
 *  @tparam Type2Fragment The type we are fragmenting. Same type expectations as
 *                        the Fragmented property type.
 */
template<typename Type2Fragment>
struct FragmentedTraits {
    /// Type of the inputs to the Fragmented property type
    using input_type = Type2Fragment;
    /// Type of the object returned by the Fragmented property type
    using return_type = chemist::set_theory::FamilyOfSets<Type2Fragment>;
};

/** @brief Property type for requesting that an object be Fragmented
 *
 *  Chemistry concepts such as functional groups, polymers, coordination
 *  compounds, etc. are predicated on the idea that we can understand the
 *  chemistry of large systems by understanding the chemistry of the system's
 *  parts. That said there are a lot of different ways to "fragment" a system
 *  (for a molecule with @f$n@f$ atoms there are @f$B_n@f$ partitions where
 *  @f$B_n@f$ is the @f$n@f$-th Bell number). In practice the fragmenting is
 *  usually not arbitrary, but the result of some algorithm which relies on
 *  chemical concepts such as bonds and/or spatial distances to assign the
 *  fragments. Nonetheless, there are still a large number of algorithms and
 *  this property type is for any module which fragments an object into
 *  subobjects. Examples are:
 *  - `Fragmented<Molecule>` for fragmenting a molecular system
 *  - `Fragmented<AOBasisSet<double>>` for fragmenting basis sets
 *
 *  @tparam Type2Fragment The object type we are fragmenting. Expected to be
 *                        set-like although exactly what the module does with
 *                        the type is up to the module.
 */

template<typename Type2Fragment>
DECLARE_TEMPLATED_PROPERTY_TYPE(Fragmented, Type2Fragment);

/** @brief Declares the inputs to a module which Fragments something
 *
 *  Modules which fragment objects of type @p Type2Fragment need to take an
 *  object of @p Type2Fragment. For forward compatability, the exact input
 *  type (with all cv qualifiers) is accessible via
 *  `FragmentedTraits<Type2Fragment>::input_type`.
 *
 */
template<typename Type2Fragment>
PROPERTY_TYPE_INPUTS(Fragmented<Type2Fragment>) {
    using traits_type = FragmentedTraits<Type2Fragment>;
    using input_type  = typename traits_type::input_type;
    return pluginplay::declare_input().add_field<input_type>(
      "Object to Fragment");
}

/** @brief Declares the results to a module which Fragments something
 *
 *  Modules which fragment objects of type @p Type2Fragment return a container
 *  filled with subsets of the input object. For forward compatability, the
 *  exact result type (with all cv qualifiers) is accessible via
 *  `FragmentedTraits<Type2Fragment>::return_type`.
 *
 */
template<typename Type2Fragment>
PROPERTY_TYPE_RESULTS(Fragmented<Type2Fragment>) {
    using return_type = typename FragmentedTraits<Type2Fragment>::return_type;
    return pluginplay::declare_result().add_field<return_type>(
      "Fragmented Object");
}

/// Property type for splitting a molecule
using FragmentedMolecule = Fragmented<type::molecule>;

} // namespace simde
