#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::hydrocarbon {

chemist::Molecule hydrocarbon(int num_carbon);

DECLARE_MODULE(MakeHydrocarbon);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<MakeHydrocarbon>("Generate a straight chain alkane");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {

}

} // namespace ghostfragment::hydrocarbon
