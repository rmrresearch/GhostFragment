#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::hydrocarbon {

DECLARE_MODULE(make_hc);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<make_hc>("Make Hydrocarbon");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {

}

} // namespace ghostfragment::hydrocarbon
