#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::drivers {

DECLARE_MODULE(Fragment);
DECLARE_MODULE(FragmentedSystem);
DECLARE_MODULE(NMer);

/// Loads all the modules in the Drivers library into the provided ModuleManager
inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<Fragment>("Fragment Driver");
    mm.add_module<FragmentedSystem>("FragmentedSystem Driver");
    mm.add_module<NMer>("NMer Driver");
}

/// Sets the defaults for submodules in the Drivers library, when a suitable
/// default is provided by GhostFragment
inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Fragment Driver", "Pseudoatoms", "Heavy Atom Partition");
    mm.change_submod("Fragment Driver", "Molecular graph", "Molecular graph");
    mm.change_submod("Fragment Driver", "Molecular graph to fragments",
                     "Cluster Partition");

    mm.change_submod("FragmentedSystem Driver", "Fragmenter",
                     "Fragment Driver");
    mm.change_submod("FragmentedSystem Driver", "Fragment to AO Mapper",
                     "Nuclei-AO Fragmenter");

    mm.change_submod("NMer Driver", "Capper", "Atomic Capping");
    mm.change_submod("NMer Driver", "Screener", "Screen by minimum distance");
}

} // namespace ghostfragment::drivers
