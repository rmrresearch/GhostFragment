// #include "ghostfragment/property_types/property_types.hpp"

// namespace ghostfragment {

// const auto mod_desc = R"(
// Chemical System Partitioner
// ===========================

// This module acts as a driver of sorts for determining all of the ChemicalSystem
// instances which need to be run. This involves two main steps:

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

// }

// }
