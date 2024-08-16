#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::hydrocarbon {

DECLARE_MODULE(makehydrocarbon);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<makehydrocarbon>("Generate Hydrocabon");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {

}

} // namespace ghostfragment::hydrocarbon
