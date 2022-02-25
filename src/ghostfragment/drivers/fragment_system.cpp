#include "drivers.hpp"
#include "ghostfragment/property_types/fragmented_system.hpp"
#include "ghostfragment/property_types/subset_map.hpp"

namespace ghostfragment::drivers {

using frags_pt    = simde::FragmentedMolecule;
using atom2ao_pt  = simde::AtomToAO;
using my_pt       = pt::FragmentedSystem;
using traits_type = pt::FragmentedSystemTraits;

const auto mod_desc = R"(
FragmentedSystem Driver
-----------------------

This module is responsible for wrapping the process of turning a ChemicalSystem
and AOBasisSet instance into a FragmentedSystem instance. This has three steps:

#. Fragment the system.
#. Assign AOs to atoms.
#. Assign electrons to fragments.

Step 1 is done by a submodule of type simde::FragmentedMolecule. Step 2 is done
by a submodule of type pt::Frag2AO. For the moment Step 3 is done by the module,
and in a naive manner (simply assuming each atom has Z electrons, where Z is
that atom's atomic number).
)";

MODULE_CTOR(FragmentedSystem) {
    description(mod_desc);

    satisfies_property_type<my_pt>();

    add_submodule<frags_pt>("Fragmenter");
    add_submodule<atom2ao_pt>("Atom to AO Mapper");
}

MODULE_RUN(FragmentedSystem) {
    using result_type  = traits_type::result_type;
    using atom2ao_type = typename result_type::nucleus_to_ao_basis_type;

    // Step 0: Unpack input and bounds checking
    const auto& [sys, aos] = my_pt::unwrap_inputs(inputs);
    const auto& mol        = sys.molecule();

    if(sys.charge()) throw std::runtime_error("Charged systems are NYI.");

    // Step 1: Form fragments
    auto& fragmenter    = submods.at("Fragmenter");
    const auto& [frags] = fragmenter.run_as<frags_pt>(mol);

    // Step 2: Map atoms to AOs
    auto& atom2ao_mapper       = submods.at("Atom to AO Mapper");
    const auto& [atom_idx2aos] = atom2ao_mapper.run_as<atom2ao_pt>(mol, aos);

    atom2ao_type atom2aos;
    type::fragmented_aos ao_sets(aos);
    for(std::size_t atom_i = 0; atom_i < mol.size(); ++atom_i) {
        auto ao_set = ao_sets.new_subset();
        for(auto ao_i : atom_idx2aos.at(atom_i)) ao_set.insert(ao_i);
        auto atom_set = frags.new_subset();
        atom_set.insert(atom_i);
        atom2aos.emplace(atom_set, ao_set);
    }

    // Step 3: Assign electrons to fragments
    using a2ne_type = result_type::atom2nelectron_type;
    a2ne_type a2ne(mol.size());
    for(decltype(a2ne.size()) i = 0; i < a2ne.size(); ++i) a2ne[i] = mol[i].Z();

    // Step 4: Assemble and return FragmentedSystem
    result_type fragmented_system(std::move(frags), std::move(atom2aos),
                                  std::move(a2ne));

    auto rv = results();
    return my_pt::wrap_results(rv, fragmented_system);
}

} // namespace ghostfragment::drivers
