#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::capping {

DECLARE_MODULE(SingleAtom);
DECLARE_MODULE(NMer);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<SingleAtom>("Atomic Capping");
    mm.add_module<NMer>("NMer Capper");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("NMer Capper", "Fragment Capper", "Atomic Capping");
}

} // namespace ghostfragment::capping
