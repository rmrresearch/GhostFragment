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
#include "simde/wavefunctions/transformed_wavefunction.hpp"

namespace simde {

template<typename InputWavefunction, typename OutputWavefunction>
DECLARE_TEMPLATED_PROPERTY_TYPE(Wavefunction, InputWavefunction,
                                OutputWavefunction);

template<typename InputWavefunction, typename OutputWavefunction>
TEMPLATED_PROPERTY_TYPE_INPUTS(Wavefunction, InputWavefunction,
                               OutputWavefunction) {
    using op    = const type::els_hamiltonian&;
    using in_wf = const InputWavefunction&;

    auto rv = pluginplay::declare_input()
                .add_field<op>("Hamiltonian")
                .template add_field<in_wf>("Input Space");

    return rv;
}

template<typename InputWavefunction, typename OutputWavefunction>
TEMPLATED_PROPERTY_TYPE_RESULTS(Wavefunction, InputWavefunction,
                                OutputWavefunction) {
    using out_wf = OutputWavefunction;

    auto rv =
      pluginplay::declare_result().add_field<out_wf>("Output Wavefunction");

    return rv;
}

// References all take in an AO space and return a reference wavefunction
// Generally used for initial guesses
using NoncanonicalReference =
  Wavefunction<type::ao_space, type::noncanonical_reference>;

using CanonicalReference =
  Wavefunction<type::ao_space, type::canonical_reference>;

// using CanonicalLocalReference =
//   Wavefunction<type::ao_space, type::local_reference>;

// Takes a reference wavefunction and returns a reference wavefunction
// Generally used for SCF iterations
using SCFWf =
  Wavefunction<type::canonical_reference, type::canonical_reference>;

// Takes a reference wavefunction and returns a many-boby wavefunction
// Generally used for electronic correlation methodsß
using CanonicalManyBodyWf =
  Wavefunction<type::canonical_reference, type::canonical_many_body>;

// using LocalManyBodyWf =
//   Wavefunction<type::local_reference, type::local_many_body>;

// using LocalToTManyBodyWf =
//   Wavefunction<type::local_reference, type::local_tot_many_body>;

} // namespace simde
