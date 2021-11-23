#include "ghostfragment/property_types/subset_map.hpp"
#include "partitioned.hpp"

using namespace ghostfragment::pt;

namespace ghostfragment::partitioned {

using my_pt          = Frag2AO;
using atom2center_pt = simde::AtomToAO;

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

MODULE_CTOR(NucleiAO) {
    satisfies_property_type<my_pt>();

    add_submodule<atom2center_pt>("Atom to Center");
}

MODULE_RUN(NucleiAO) {
    const auto& [frags, aos] = my_pt::unwrap_inputs(inputs);
    const auto& mol          = frags.object();

    // Step 1: Map atoms to AOs
    const auto& [atom_ao] =
      submods.at("Atom to Center").run_as<atom2center_pt>(mol, aos);

    typename Frag2AOTraits::fos_value_type fragged_aos(aos);
    typename Frag2AOTraits::result_type frag2aos;
    // Step 2: Apply basis functions to fragment
    for(const auto& fragi : frags) {
        auto new_set = fragged_aos.new_subset();
        for(auto atomi : fragi) {
            for(auto centeri : atom_ao.at(atomi)) new_set.insert(centeri);
        }
        frag2aos.emplace(fragi, std::move(new_set));
    }

    auto rv = results();
    return my_pt::wrap_results(rv, frag2aos);
}

} // namespace ghostfragment::partitioned
