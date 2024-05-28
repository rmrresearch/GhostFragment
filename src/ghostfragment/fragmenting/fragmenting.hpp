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

namespace ghostfragment::fragmenting {

DECLARE_MODULE(Cluster);
DECLARE_MODULE(HeavyAtom);
DECLARE_MODULE(NMers);
// DECLARE_MODULE(AO2Atom);
// DECLARE_MODULE(NucleiAO);
// DECLARE_MODULE(SystemAO);
DECLARE_MODULE(BondBased);
DECLARE_MODULE(IntersectionsByRecursion);
// DECLARE_MODULE(DimerMaker);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<Cluster>("Cluster Partition");
    mm.add_module<HeavyAtom>("Heavy Atom Partition");
    mm.add_module<NMers>("All nmers");
    mm.add_module<IntersectionsByRecursion>("Intersections");
    // mm.add_module<AO2Atom>("AO Center to Atom Mapper");
    // mm.add_module<NucleiAO>("Nuclei-AO Fragmenter");
    mm.add_module<BondBased>("Bond-Based Fragmenter");
    // mm.add_module<DimerMaker>("Dimer Maker");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Heavy Atom Partition", "Connectivity", "Covalent Radius");
    // mm.change_submod("Dimer Maker", "Fragmentation", "Fragment Driver");
}

} // namespace ghostfragment::fragmenting
