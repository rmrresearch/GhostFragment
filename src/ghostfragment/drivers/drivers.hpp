#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::drivers {

DECLARE_MODULE(FragmentedSystem);

/// Loads all the modules in the Drivers library into the provided ModuleManager
inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<FragmentedSystem>("FragmentedSystem Driver");
}

/// Sets the defaults for submodules in the Drivers library, when a suitable
/// default is provided by GhostFragment
inline void set_defaults(pluginplay::ModuleManger& mm) {
    mm.change_submod("FragmentedSystem Driver", "Fragmenter",
                     "cluster partition");
    mm.change_submod("FragmentedSystem Driver", "Fragment to AO Mapper",
                     "AO Center to Atom Mapper");
}

} // namespace ghostfragment::drivers
