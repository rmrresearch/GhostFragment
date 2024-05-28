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
#include <chemist/chemical_system/molecule/molecule.hpp>
#include <chemist/fragmenting/capping/capping.hpp>
#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

struct ChargeMultiplicityAssignerTraits {
    using frag_type = chemist::FragmentedNuclei;
    using cap_type  = std::vector<chemist::CapSet>;
    using mol_type  = chemist::Molecule;

    using charge_type        = mol_type::charge_type;
    using charge_result_type = std::vector<charge_type>;

    using size_type        = mol_type::size_type;
    using mult_result_type = std::vector<size_type>;
};

DECLARE_PROPERTY_TYPE(ChargeMultiplicityAssigner);

PROPERTY_TYPE_INPUTS(ChargeMultiplicityAssigner) {
    using traits_type = ChargeMultiplicityAssignerTraits;
    using frag_type   = traits_type::frag_type;
    using cap_type    = traits_type::cap_type;
    using mol_type    = traits_type::mol_type;

    return pluginplay::declare_input()
      .add_field<frag_type>("Fragments")
      .template add_field<cap_type>("Set of caps")
      .template add_field<mol_type>("The original molecule");
}

PROPERTY_TYPE_RESULTS(ChargeMultiplicityAssigner) {
    using traits_type        = ChargeMultiplicityAssignerTraits;
    using charge_result_type = traits_type::charge_result_type;
    using mult_result_type   = traits_type::mult_result_type;

    return pluginplay::declare_result()
      .add_field<charge_result_type>("Charge for each fragment")
      .template add_field<mult_result_type>("Mult for each fragment");
}

} // namespace ghostfragment::pt
