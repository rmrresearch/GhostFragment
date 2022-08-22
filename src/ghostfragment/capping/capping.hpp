#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::capping {

DECLARE_MODULE(SingleAtom);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<SingleAtom>("Atomic Capping");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Atomic Capping", "Connectivity", "Covalent Radius");
}

} // namespace ghostfragment::capping
