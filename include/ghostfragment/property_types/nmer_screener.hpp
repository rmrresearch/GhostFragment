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

// #pragma once
// #include <ghostfragment/property_types/capped.hpp>
// #include <ghostfragment/type/type.hpp>
// #include <simde/simde.hpp>
// namespace ghostfragment::pt {

// DECLARE_PROPERTY_TYPE(NMerScreener);

// PROPERTY_TYPE_INPUTS(NMerScreener) {
//     using input_t = typename CappedFragmentsTraits::result_type;
//     auto inputs   = pluginplay::declare_input()
//                     .add_field<input_t>("Capped fragments")
//                     .template add_field<unsigned int>("N");
//     return inputs;
// }

// PROPERTY_TYPE_RESULTS(NMerScreener) {
//     using result_type = type::nmers;
//     return pluginplay::declare_result().add_field<result_type>("NMers");
// }

// } // namespace ghostfragment::pt
