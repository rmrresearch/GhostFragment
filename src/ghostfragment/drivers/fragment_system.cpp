// #include "../detail_/fragmented_system_pimpl.hpp"
// #include "drivers.hpp"
// #include <ghostfragment/property_types/property_types.hpp>

// namespace ghostfragment::drivers {

// using my_pt      = pt::FragmentedSystem;
// using frags_pt   = pt::FragmentedMolecule;
// using cap_pt     = pt::CappedFragments;
// using ao_pt      = pt::AtomicOrbitals;
// using atom2ao_pt = simde::AtomToAO;

// using pimpl_type = detail_::FragmentedSystemPIMPL;

// namespace {

// auto convert_atom2ao(pluginplay::SubmoduleRequest& atom2ao,
//                      const type::nuclei_set& mol,
//                      const type::ao_basis_set& aos) {
//     const auto& [atom_idx2aos] = atom2ao.run_as<atom2ao_pt>(mol, aos);

//     typename pimpl_type::idx2ao_map_type atom2aos;
//     type::fragmented_aos ao_sets(aos);
//     for(std::size_t atom_i = 0; atom_i < mol.size(); ++atom_i) {
//         auto ao_set = ao_sets.new_subset();
//         for(auto ao_i : atom_idx2aos.at(atom_i)) ao_set.insert(ao_i);
//         atom2aos.emplace_back(ao_set);
//     }
//     return atom2aos;
// }

// auto assign_electrons(const type::nuclei_set& mol) {
//     typename pimpl_type::idx2ne_map_type a2ne(mol.size());
//     for(decltype(a2ne.size()) i = 0; i < a2ne.size(); ++i) a2ne[i] =
//     mol[i].Z(); return a2ne;
// }

// } // namespace

// const auto mod_desc = R"(
// FragmentedSystem Driver
// -----------------------

// This module is responsible for wrapping the process of turning a
// ChemicalSystem and AOBasisSet instance into a FragmentedSystem instance. This
// has the following steps:

// #. Fragment the system.
// #. Cap the fragments
// #. Determine the AO basis for the caps
// #. Assign AOs to the caps
// #. Assign AOs to atoms.
// #. Assign electrons to fragments.

// Step 1 is done by a submodule of type simde::FragmentedMolecule. Step 2 is
// done by a submodule of type pt::Frag2AO. For the moment Step 3 is done by the
// module, and in a naive manner (simply assuming each atom has Z electrons,
// where Z is that atom's atomic number).
// )";

// MODULE_CTOR(FragmentedSystem) {
//     description(mod_desc);

//     satisfies_property_type<my_pt>();

//     add_submodule<frags_pt>("Fragmenter");
//     add_submodule<cap_pt>("Capper");
//     add_submodule<ao_pt>("Cap Basis");
//     add_submodule<atom2ao_pt>("Atom to AO Mapper");
// }

// MODULE_RUN(FragmentedSystem) {
//     // Step 0: Unpack input and bounds checking
//     const auto& [sys, aos] = my_pt::unwrap_inputs(inputs);
//     const auto& mol        = sys.molecule();

//     if(sys.charge()) throw std::runtime_error("Charged systems are NYI.");

//     using pimpl_type = detail_::FragmentedSystemPIMPL;
//     auto pimpl       = std::make_unique<pimpl_type>();

//     // Step 1: Form fragments
//     auto& fragmenter    = submods.at("Fragmenter");
//     const auto& [frags] = fragmenter.run_as<frags_pt>(mol);

//     // Step 2: Cap fragments
//     auto& capper           = submods.at("Capper");
//     const auto& [frag2cap] = capper.run_as<cap_pt>(frags);

//     // Bit of a hack to get the caps object
//     const auto& caps = frag2cap.begin()->second.object();

//     // Step 3: Make the AO basis for the caps
//     auto& cap_basis_mod   = submods.at("Cap Basis");
//     const auto& [cap_aos] = cap_basis_mod.run_as<ao_pt>(caps.nuclei());

//     // Step 4: Map atoms and caps to AOs
//     auto& atom2ao_mapper = submods.at("Atom to AO Mapper");
//     pimpl->m_atom2aos    = convert_atom2ao(atom2ao_mapper, mol, aos);
//     pimpl->m_cap2aos =
//       convert_atom2ao(atom2ao_mapper, caps.nuclei(), cap_aos.basis_set());

//     // Step 5: Assign electrons to atoms and caps
//     pimpl->m_atom2ne = assign_electrons(mol);
//     pimpl->m_cap2ne  = assign_electrons(caps.nuclei());

//     // Step 6: Assemble and return FragmentedSystem
//     pimpl->m_frags     = std::move(frags);
//     pimpl->m_frag2caps = std::move(frag2cap);
//     ghostfragment::FragmentedSystem fragmented_system(std::move(pimpl));

//     auto rv = results();
//     return my_pt::wrap_results(rv, fragmented_system);
// }

// } // namespace ghostfragment::drivers
