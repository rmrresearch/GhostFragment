#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::drivers {

DECLARE_MODULE(Fragment);
// DECLARE_MODULE(FragmentBasedMethod);
DECLARE_MODULE(FragmentedChemicalSystem);
// DECLARE_MODULE(NeutralSinglet);
// DECLARE_MODULE(InputQueue);

/// Loads all the modules in the Drivers library into the provided ModuleManager
inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<Fragment>("Fragment Driver");
    //     // mm.add_module<FragmentBasedMethod>("Fragment Based Method");
    mm.add_module<FragmentedChemicalSystem>("FragmentedChemicalSystem Driver");
    //     // mm.add_module<NMerSystem>("NMerSystem Driver");
    //     mm.add_module<NeutralSinglet>("Neutral Singlet");
    //     mm.add_module<InputQueue>("Input Queue");
}

/// Sets the defaults for submodules in the Drivers library, when a suitable
/// default is provided by GhostFragment
inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Fragment Driver", "Molecular graph", "Nuclear Graph");
    mm.change_submod("Fragment Driver", "Molecular graph to fragments",
                     "Bond-Based Fragmenter");
    mm.change_submod("Fragment Driver", "Find broken bonds", "Broken bonds");
    mm.change_submod("Fragment Driver", "Cap broken bonds",
                     "Weighted distance");
    mm.change_submod("FragmentedChemicalSystem Driver", "Fragmenter",
                     "Fragment Driver");
    //     // mm.change_submod("FragmentedSystem Driver", "Atom to AO Mapper",
    //     //                 "AO Center to Atom Mapper");

    //     // mm.change_submod("Fragment Based Method", "Fragment Maker",
    //     //                  "FragmentedSystem Driver");
    //     // mm.change_submod("Fragment Based Method", "N-Mer Maker",
    //     //                  "NMerSystem Driver");
}

} // namespace ghostfragment::drivers
