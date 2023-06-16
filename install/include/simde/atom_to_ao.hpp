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
#include <pluginplay/property_type/property_type.hpp>

namespace simde {
namespace detail_ {

/// Struct for us to work out the return type w/o contaminating the namespace
struct AtomToCenterTraits {
    /// Type AOBasisSet uses for offsets
    using ao_size_type = typename simde::type::ao_basis_set::size_type;
    /// Type of a set of Center offsets
    using ao_set_type = std::set<ao_size_type>;
    /// Map from atom index to a set of Cernter offsets
    using return_type = std::vector<ao_set_type>;
};

} // namespace detail_

/// For user convenience this is the type returned by AtomToCenter
using atom_to_center_return_type = detail_::AtomToCenterTraits::return_type;

/** @brief Property type defining the API for assigning atoms to centers of AOs.
 *
 *  @note Design-wise we have opted to return indices not objects. This is for
 *        convenience. Since the user must provide us a Molecule and an
 *        AOBasisSet instance this should prove no problem for the user.
 *
 *  @todo Change the input from Molecule to PointSet, once PointSet becomes
 *        available.
 *
 */
template<typename InputOrbitalType>
DECLARE_TEMPLATED_PROPERTY_TYPE(AtomToCenter, InputOrbitalType);

template<typename InputOrbitalType>
TEMPLATED_PROPERTY_TYPE_INPUTS(AtomToCenter, InputOrbitalType) {
    return pluginplay::declare_input()
      .add_field<const simde::type::molecule&>("Molecule")
      .template add_field<const InputOrbitalType&>("Orbital Basis");
}

template<typename InputOrbitalType>
TEMPLATED_PROPERTY_TYPE_RESULTS(AtomToCenter, InputOrbitalType) {
    using r_t = atom_to_center_return_type;
    return pluginplay::declare_result().add_field<r_t>("Atom to Center map");
}

/// Maps points to AOs
using AtomToAO = AtomToCenter<simde::type::ao_basis_set>;

/// Maps points to MOs
using AtomToMO = AtomToCenter<simde::type::derived_space>;

} // namespace simde
