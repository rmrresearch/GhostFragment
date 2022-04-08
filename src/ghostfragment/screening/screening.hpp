#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::screening {

DECLARE_MODULE(MinimumDistance);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<MinimumDistance>("Screen by minimum distance");
}

inline void set_defaults(pluginplay::ModuleManager&) {}

} // namespace ghostfragment::screening
