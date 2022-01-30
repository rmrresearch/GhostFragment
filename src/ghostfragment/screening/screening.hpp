#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::screening {

DECLARE_MODULE(Distance);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<Distance>("Screen by distance");
}

inline void set_defaults(pluginplay::ModuleManager&) {}

} // namespace ghostfragment::screening