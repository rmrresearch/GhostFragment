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
namespace ghostfragment::topology {

DECLARE_MODULE(CovRadii);
DECLARE_MODULE(NuclearGraphFromConnectivity);
// DECLARE_MODULE(BrokenBonds);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<CovRadii>("Covalent Radius");
    mm.add_module<NuclearGraphFromConnectivity>("Nuclear Graph");
    //     mm.add_module<BrokenBonds>("Broken Bonds");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Nuclear Graph", "Nodes", "Heavy Atom Partition");
    mm.change_submod("Nuclear Graph", "Connectivity", "Covalent Radius");
    //     mm.change_submod("Broken Bonds", "Atomic connectivity", "Covalent
    //     Radius");
}

} // namespace ghostfragment::topology
