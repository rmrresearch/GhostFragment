#include "ghostfragment/property_types/property_types.hpp"
#include "partitioned.hpp"

namespace ghostfragment::partitioned {

namespace {
constexpr auto module_desc = R"""(
********
Synopsis
********

Driver module which handles fragmenting a ChemicalSystem instance and assigning
AO basis sets to the fragments.
)""";
} // namespace

using my_pt      = pt::FragmentedSystemAO;
using nuke2ao_pt = simde::FragmentedNucleiAO;

MODULE_CTOR(SystemAO) {
    description(module_desc);

    satisfies_property_type<my_pt>();

    add_submodule<nuke2ao_pt>("Nuclei-AO Fragmenter");
}

MODULE_RUN(SystemAO) {
    const auto& [nelectrons, nuke_aos_pair] = my_pt::unwrap_inputs(inputs);
    const auto& mol                         = std::get<0>(nuke_aos_pair);
    const auto& aos                         = std::get<1>(nuke_aos_pair);

    auto& nuke2ao_mod      = submods.at("Nuclei-AO Fragmenter");
    const auto& [nuke2aos] = nuke2ao_mod.run_as<nuke2ao_pt>(std::tie(mol, aos));

    std::vector<std::size_t> elecs_per_frag(nuke2aos.size());

    auto rv = results();
    return my_pt::wrap_results(rv, elecs_per_frag, nuke2aos);
}

} // namespace ghostfragment::partitioned