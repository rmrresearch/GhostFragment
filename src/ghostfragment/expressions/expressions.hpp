#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::expressions {

DECLARE_MODULE(MBE);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<MBE>("Many-body expansion");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {}

} // namespace ghostfragment::expressions
