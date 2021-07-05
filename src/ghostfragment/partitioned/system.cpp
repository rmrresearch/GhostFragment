// #include "../modules.hpp"
// #include "ghostfragment/property_types/property_types.hpp"

// namespace ghostfragment {

// const auto mod_desc = R"(
// Chemical System Partitioner
// ===========================

// This module acts as a driver of sorts for determining all of the
// ChemicalSystem instances which need to be run. This involves two main steps:

// - Fragmenting the input molecule
// - Assigning electrons to the fragments
// - Capping fragments
// - Creating dimers, trimers, n-mers
// - Determining intersections
// - Embedding the fragments
// )";

// MODULE_CTOR(SystemPartitioner) {
//     description(mod_desc);
//     satisfies_property_type<pt::fragmented_system>();

//     add_submodule<pt::fragmented_mol>("Fragment generator");
//     add_submodule<pt::nmer_maker>("N-mer generator");
// }

// MODULE_RUN(SystemPartitioner) {
//     auto [sys]      = pt::fragmented_system::unwrap_inputs(inputs);
//     const auto& mol = sys.molecule();

//     // Step 1: Make the initial fragments
//     auto& fragmenter = submods.at("Fragment generator");
//     auto [frags]     = fragmenter.run_as<pt::fragmented_mol>(mol);

//     // Step : Make n-mers
//     auto& nmerer = submods.at("N-mer generator");
//     auto [nmers] = nmerer.run_as<pt::nmer_maker>(frags);

//     type::fragmented_system systems;

//     auto rv = results();
//     return pt::fragmented_system::wrap_results(rv, systems);
// }

// } // namespace ghostfragment
