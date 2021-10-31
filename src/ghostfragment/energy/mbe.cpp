// #include "energy.hpp"
// #include "ghostfragment/property_types/property_types.hpp"
// #include <simde/simde.hpp>

// namespace ghostfragment::energy {
// namespace {

// constexpr auto module_desc = R"""(
// ########
// Synopsis
// ########

// Driver routine for computing the energy of a chemical system using a traditional
// many-body expansion.
// )""";

// }

// using my_pt   = simde::AOEnergy;
// using frag_pt = simde::FragmentedMolecule;
// using nmer_pt = simde::NMers;

// MODULE_CTOR(MBE) {
//     description(module_desc);

//     satisfies_property_type<my_pt>();

//     add_submodule<frag_pt>("Fragmenter");
//     // add_submodule<nmer_pt>("NMers");
// }

// MODULE_RUN(MBE) {
//     auto [aos, sys] = my_pt::unwrap_inputs(inputs);
//     const auto& mol = sys.molecule();

//     auto& frag_mod      = submods.at("Fragmenter");
//     const auto& [frags] = frag_mod.run_as<frag_pt>(mol);

//     // auto [cs, el_per_nmer, nmers] = nmer_mod.run_as<nmer_pt>(el_per_frag,
//     // frags);
//     // auto [nmers] = submods.at("NMers").run_as<nmer_pt>(frags);

//     // auto [sys_aos]

//     double E = 0.0;
//     auto rv  = results();
//     return my_pt::wrap_results(rv, E);
// }

// } // namespace ghostfragment::energy
