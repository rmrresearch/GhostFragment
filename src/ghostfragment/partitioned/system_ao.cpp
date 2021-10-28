// #include "ghostfragment/property_types/property_types.hpp"
// #include "partitioned.hpp"

// namespace ghostfragment::partitioned {

// namespace {
// constexpr auto module_desc = R"""(
// ********
// Synopsis
// ********

// Driver module which handles:

// #. fragmenting a Molecule instance,
// #. assigning AO basis sets to the fragments,
// #. and assigning electrons to the fragments.
// )""";
// } // namespace

// using my_pt      = pt::FragmentedSystemAO;
// using nuke2ao_pt = simde::FragmentedNucleiAO;

// MODULE_CTOR(SystemAO) {
//     description(module_desc);

//     satisfies_property_type<my_pt>();

//     add_submodule<nuke2ao_pt>("Nuclei-AO Fragmenter");
// }

// MODULE_RUN(SystemAO) {
//     const auto& [nelectrons, nuke_aos_pair] = my_pt::unwrap_inputs(inputs);
//     const auto& mol                         = std::get<0>(nuke_aos_pair);
//     const auto& aos                         = std::get<1>(nuke_aos_pair);
//     const auto pair                         = std::make_tuple(mol, aos);

//     auto& nuke2ao_mod      = submods.at("Nuclei-AO Fragmenter");
//     const auto& [nuke2aos] = nuke2ao_mod.run_as<nuke2ao_pt>(pair);

//     std::vector<std::size_t> elecs_per_frag(nuke2aos.size(), 0);

//     std::size_t i = 0;
//     for(const auto& [atoms, aos] : nuke2aos) {
//         for(const auto& atomi : atoms) elecs_per_frag[i] += mol[atomi].Z();
//         ++i;
//     }

//     auto sum = std::accumulate(elecs_per_frag.begin(), elecs_per_frag.end(),
//     0);

//     // Basic error-checking
//     if(nuke2aos.disjoint() && sum != nelectrons)
//         throw std::runtime_error("Don't know what to do with charged
//         species");

//     auto rv = results();
//     return my_pt::wrap_results(rv, elecs_per_frag, nuke2aos);
// }

// } // namespace ghostfragment::partitioned
