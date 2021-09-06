#include "../modules.hpp"

namespace ghostfragment {

const auto mod_desc = R"(
Chemical System Partitioner
===========================

This module acts as a driver of sorts for determining all of the
ChemicalSystem instances which need to be run. This involves the following main 
steps:

- Fragmenting the input molecule
  - Capping fragments part of procedure
  - Determining intersections
- Creating dimers, trimers, n-mers
  - Capping nmers part of procedure
  - Determining intersections  
- Embedding the fragments
)";

using pt      = simde::FragmentedSystem;
using frag_pt = simde::FragmentedMolecule;
using nmer_pt = simde::NMers;

MODULE_CTOR(SystemPartitioner) {
    description(mod_desc);
    satisfies_property_type<pt>();

    add_submodule<frag_pt>("Fragment generator");
    add_submodule<nmer_pt>("N-mer generator");
}

MODULE_RUN(SystemPartitioner) {
    auto [sys]      = pt::unwrap_inputs(inputs);
    const auto& mol = sys.molecule();

    // Step 1: Make the initial fragments
    auto& fragmenter = submods.at("Fragment generator");
    auto [frags]     = fragmenter.run_as<frag_pt>(mol);

    // Step : Make n-mers
    auto& nmerer = submods.at("N-mer generator");
    auto [nmers] = nmerer.run_as<nmer_pt>(frags);

    type::fragmented_system systems;
    using system_type = typename type::fragmented_system::mapped_type;
    for(const auto& nmer : nmers) {}

    auto rv = results();
    return pt::wrap_results(rv, systems);
}

} // namespace ghostfragment
