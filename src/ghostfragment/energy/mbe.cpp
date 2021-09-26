#include "../modules.hpp"
#include <simde/simde.hpp>

namespace ghostfragment {

using pt      = simde::AOEnergy;
using frag_pt = simde::FragmentedMolecule;
using nmer_pt = simde::NMers;

// auto assign_aos(const simde::type::ao_space& aos, const auto&& frags) {
//     auto partioned_basis;

// }

MODULE_CTOR(MBE) {
    satisfies_property_type<pt>();

    add_submodule<frag_pt>("Fragmenter");
    add_submodule<nmer_pt>("NMers");
}

MODULE_RUN(MBE) {
    auto [aos, sys] = pt::unwrap_inputs(inputs);

    auto [frags] = submods.at("Fragmenter").run_as<frag_pt>(sys.molecule());
    // auto [frag2aos] =;
    auto [nmers] = submods.at("NMers").run_as<nmer_pt>(frags);

    // auto [sys_aos]

    double E = 0.0;
    auto rv  = results();
    return pt::wrap_results(rv, E);
}

} // namespace ghostfragment