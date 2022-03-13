// #include "drivers.hpp"
// #include <ghostfragment/property_types/property_types.hpp>

// namespace ghostfragment::drivers {

// using nmers_pt        = pt::NMers;
// using capped_nmers_pt = pt::CappedNMers;
// using my_pt           = pt::NMerSystem;
// using traits_type     = pt::NMerSystemTraits;

// const auto mod_desc = R"()";

// MODULE_CTOR(NMerSystem) {
//     description(mod_desc);

//     satisfies_property_type<my_pt>();

//     add_submodule<nmers_pt>("Fragments to NMers");
//     add_submodule<capped_nmers_pt>("NMers to Capped NMers");
// }

// MODULE_RUN(NMerSystem) {
//     using result_type = traits_type::result_type;

//     const auto& [frags] = my_pt::unwrap_inputs(inputs);

//     auto& nmer_mod      = submods.at("Fragments to NMers");
//     const auto& [nmers] = nmer_mod.run_as<nmers_pt>(frags);

//     auto& cap_mod              = submods.at("NMers to Capped NMers");
//     const auto& [capped_nmers] = cap_mod.run_as<capped_nmers_pt>(nmers);

//     result_type nmer_system(frags, capped_nmers);

//     auto rv = results();
//     return my_pt::wrap_results(rv, nmers);
// }

// } // namespace ghostfragment::drivers