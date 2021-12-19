#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::connectivity {

DECLARE_MODULE(CovRadii);
DECLARE_MODULE(MolecularGraph);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<CovRadii>("Covalent Radius");
    mm.add_module<MolecularGraph>("Molecular Graph");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Molecular Graph", "Atomic connectivity",
                     "Covalent Radius");
}

} // namespace ghostfragment::connectivity
