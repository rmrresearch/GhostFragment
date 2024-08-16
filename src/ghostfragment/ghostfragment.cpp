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

#include "capping/capping.hpp"
#include "drivers/drivers.hpp"
#include "fragmenting/fragmenting.hpp"
#include "screening/screening.hpp"
#include "topology/topology.hpp"
#include <ghostfragment/load_modules.hpp>
#include "hydrocarbon/hc.hpp"

namespace ghostfragment {

void load_modules(pluginplay::ModuleManager& mm) {
    capping::load_modules(mm);
    topology::load_modules(mm);
    drivers::load_modules(mm);
    fragmenting::load_modules(mm);
    // screening::load_modules(mm);
    hydrocarbon::load_modules(mm);

    capping::set_defaults(mm);
    topology::set_defaults(mm);
    drivers::set_defaults(mm);
    fragmenting::set_defaults(mm);
    // screening::set_defaults(mm);
}

} // namespace ghostfragment
