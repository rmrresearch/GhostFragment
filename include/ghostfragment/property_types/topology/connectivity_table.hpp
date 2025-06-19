/*
 * Copyright 2024 GhostFragment
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
#include <chemist/chemist.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

struct ConnectivityTableTraits {
    using input_type  = chemist::Molecule;
    using result_type = chemist::topology::ConnectivityTable;
};

DECLARE_PROPERTY_TYPE(ConnectivityTable);

PROPERTY_TYPE_INPUTS(ConnectivityTable) {
    using molecule_type = typename ConnectivityTableTraits::input_type;
    using input_type    = chemist::MoleculeView<const molecule_type>;
    return pluginplay::declare_input().add_field<input_type>("Molecule");
}

PROPERTY_TYPE_RESULTS(ConnectivityTable) {
    using result_type = ConnectivityTableTraits::result_type;
    return pluginplay::declare_result().add_field<result_type>(
      "ConnectivityTable");
}

} // namespace ghostfragment::pt
