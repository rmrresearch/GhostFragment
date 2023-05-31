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
