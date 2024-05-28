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
#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <pluginplay/pluginplay.hpp>

namespace ghostfragment::pt {

struct IntersectionTraits {
    using input_type = chemist::fragmenting::FragmentedNuclei<chemist::Nuclei>;

    using result_type = input_type;
};

DECLARE_PROPERTY_TYPE(Intersections);

PROPERTY_TYPE_INPUTS(Intersections) {
    using input0_type = typename IntersectionTraits::input_type;
    return pluginplay::declare_input().add_field<input0_type>(
      "Fragments to find intersections of");
}

PROPERTY_TYPE_RESULTS(Intersections) {
    using result_type = typename IntersectionTraits::result_type;
    return pluginplay::declare_result().add_field<result_type>(
      "Fragments with intersections");
}

} // namespace ghostfragment::pt
