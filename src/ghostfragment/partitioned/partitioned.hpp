#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::partitioned {

DECLARE_MODULE(Cluster);
DECLARE_MODULE(NMers);
DECLARE_MODULE(AO2Atom);
DECLARE_MODULE(AOSystem);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<Cluster>("Cluster Partition");
    mm.add_module<NMers>("All nmers");
    mm.add_module<AO2Atom>("AO Center to Atom Mapper");
    mm.add_module<AOSystem>("AOSystem Partition");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {}

} // namespace ghostfragment::partitioned