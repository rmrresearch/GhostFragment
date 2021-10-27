#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::energy {

DECLARE_MODULE(MBE);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<MBE>("Many-Body Expansion");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Many-Body Expansion", "Fragmenter",
                     "System-AO Fragmenter");
}

} // namespace ghostfragment::energy
