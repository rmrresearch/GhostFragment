#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::connectivity {

DECLARE_MODULE(CovRadii);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<CovRadii>("Covalent Radius");
}

}
