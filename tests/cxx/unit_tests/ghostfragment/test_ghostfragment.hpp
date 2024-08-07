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
#include "testing/are_caps_equal.hpp"
#include "testing/hydrocarbon/hydrocarbon.hpp"
#include "testing/water/water.hpp"
#include <catch2/catch.hpp>
#include <ghostfragment/load_modules.hpp>
#include <simde/simde.hpp>

namespace testing {

// Common set-up all tests have
inline auto initialize() {
    pluginplay::ModuleManager mm;
    ghostfragment::load_modules(mm);
    return mm;
}

} // namespace testing
