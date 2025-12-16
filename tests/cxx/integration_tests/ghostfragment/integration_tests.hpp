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
#include <catch2/catch.hpp>
#include <chemcache/chemcache.hpp>
#include <ghostfragment/load_modules.hpp>
#include <integrals/integrals.hpp>
#include <nux/nux.hpp>
#include <scf/scf.hpp>
#include <simde/simde.hpp>

namespace testing {

// Common set-up all tests have
inline auto initialize() {
    auto rv = std::make_shared<parallelzone::runtime::RuntimeView>();
    pluginplay::ModuleManager mm(rv);
    scf::load_modules(mm);
    integrals::load_modules(mm);
    nux::load_modules(mm);
    chemcache::load_modules(mm);
    ghostfragment::load_modules(mm);

    mm.change_submod("SCF Driver", "Hamiltonian",
                     "Born-Oppenheimer approximation");

    const auto ao_driver_key = "SCF integral driver";
    mm.change_submod(ao_driver_key, "Fundamental matrices",
                     "AO integral driver");

    mm.change_submod("Diagonalization Fock update", "Overlap matrix builder",
                     "Overlap");

    mm.change_submod("Loop", "Overlap matrix builder", "Overlap");

    mm.change_submod("XYZ to Molecule", "Z from symbol", "Z from symbol");
    mm.change_submod("XYZ to Molecule", "Atom from z", "Atom");

    return mm;
}

} // namespace testing
