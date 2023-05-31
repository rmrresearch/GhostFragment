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
