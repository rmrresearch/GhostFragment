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
// #include <ghostfragment/equation/equation.hpp>
// #include <ghostfragment/nmer_system.hpp>

// namespace ghostfragment::pt {

// struct ExpressionTraits {
//     using input_type  = ghostfragment::NMerSystem;
//     using result_type = ghostfragment::equation::Expression;
// };

// DECLARE_PROPERTY_TYPE(Expression);

// PROPERTY_TYPE_INPUTS(Expression) {
//     using traits_type = ExpressionTraits;
//     using input_type  = traits_type::input_type;

//     return pluginplay::declare_input().add_field<input_type>("NMers");
// }

// PROPERTY_TYPE_RESULTS(Expression) {
//     using traits_type = ExpressionTraits;
//     using result_type = traits_type::result_type;

//     return pluginplay::declare_result().add_field<result_type>("Expression");
// }

// } // namespace ghostfragment::pt
