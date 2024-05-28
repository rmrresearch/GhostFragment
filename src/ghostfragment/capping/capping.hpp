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

namespace ghostfragment::capping {

DECLARE_MODULE(SingleAtom);
DECLARE_MODULE(DCLC);
DECLARE_MODULE(WeightedDistance);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<SingleAtom>("Atomic Capping");
    mm.add_module<DCLC>("DCLC Capping");
    mm.add_module<WeightedDistance>("Weighted Distance");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("DCLC Capping", "Connectivity", "Covalent Radius");
}

} // namespace ghostfragment::capping
