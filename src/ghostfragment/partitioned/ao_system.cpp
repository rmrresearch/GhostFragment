#include "ghostfragment/types.hpp"
#include "partitioned.hpp"

namespace ghostfragment::partitioned {

using my_pt          = simde::FragmentedAOSystem;
using frag_pt        = simde::FragmentedMolecule;
using atom2center_pt = simde::AtomToCenter;

const auto mod_desc = R"(
AOSpace/Molecule Partitioner
----------------------------

This module serves as a driver of sorts for fragmenting a molecule and then
assigning AO basis sets to the fragments. How fragments are formed, and how AOs
are mapped to atoms is determined by submodules. This module then uses the
results of the two submodules to associate each fragment with an AO basis set.

.. note::

   The AO basis set associated with each fragment is more akin to applying an
   atomic basis set to the fragment, than the AO basis set one would use for say
   performing a basis-set superposition error calculation. The exact details
   depend on the "Atom to Center" module though.
)";

MODULE_CTOR(AOSystem) {
    satisfies_property_type<my_pt>();

    add_submodule<frag_pt>("Fragmenter");
    add_submodule<atom2center_pt>("Atom to Center");
}

MODULE_RUN(AOSystem) {
    using return_type = type::fragmented_mols_and_aos;

    const auto& [mol_ao_pair] = my_pt::unwrap_inputs(inputs);
    const auto& mol           = std::get<0>(mol_ao_pair);
    const auto& aos           = std::get<1>(mol_ao_pair);

    // Step 1: Fragments
    const auto& [frags] = submods.at("Fragmenter").run_as<frag_pt>(mol);

    // Step 2: Map atoms to AOs
    const auto& [atom_ao] =
      submods.at("AO to Center").run_as<atom2center_pt>(mol, aos);

    // Step 3: Apply basis functions to fragments
    return_type frags_and_aos(mol_ao_pair);

    for(const auto& fragi : frags) {
        auto new_set = frags_and_aos.new_subset();
        for(auto atomi : fragi) {
            std::get<0>(new_set).insert(atomi);
            for(auto centeri : atom_ao.at(atomi)) {
                std::get<1>(new_set).insert(centeri);
            }
        }
        frags_and_aos.insert(std::move(new_set));
    }

    auto rv = results();
    return my_pt::wrap_results(rv, frags_and_aos);
}

} // namespace ghostfragment::partitioned