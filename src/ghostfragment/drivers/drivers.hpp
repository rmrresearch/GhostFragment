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
#include <simde/simde.hpp>

namespace ghostfragment::drivers {

DECLARE_DRIVER_MODULE(Fragment);
DECLARE_MODULE(FragmentBasedMethod);
DECLARE_MODULE(FragmentedChemicalSystem);

/// Loads all the modules in the Drivers library into the provided ModuleManager
inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<Fragment>("Fragment Driver");
    mm.add_module<FragmentedChemicalSystem>("FragmentedChemicalSystem Driver");
    mm.add_module<FragmentBasedMethod>("Fragment Based Method");
}

/// Sets the defaults for submodules in the Drivers library, when a suitable
/// default is provided by GhostFragment
inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Fragment Driver", "Atomic connectivity",
                     "Covalent Radius");
    mm.change_submod("Fragment Driver", "Molecular graph", "Nuclear Graph");
    mm.change_submod("Fragment Driver", "Fragment builder",
                     "Bond-Based Fragmenter");
    mm.change_submod("Fragment Driver", "N-mer builder", "All nmers");

    mm.change_submod("Fragment Driver", "Intersection finder", "intersections");
    mm.change_submod("Fragment Driver", "Find broken bonds", "Broken bonds");
    mm.change_submod("Fragment Driver", "Cap broken bonds",
                     "Weighted distance");

    mm.change_submod("FragmentedChemicalSystem Driver", "Fragmenter",
                     "Fragment Driver");

    mm.change_submod("Fragment Based Method", "Subsystem former",
                     "FragmentedChemicalSystem Driver");
    mm.change_submod("Fragment Based Method", "Weighter", "GMBE Weights");
}

} // namespace ghostfragment::drivers
