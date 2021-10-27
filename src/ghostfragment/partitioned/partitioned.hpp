#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::partitioned {

DECLARE_MODULE(Cluster);
DECLARE_MODULE(NMers);
DECLARE_MODULE(AO2Atom);
DECLARE_MODULE(NucleiAO);
DECLARE_MODULE(SystemAO);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<Cluster>("Cluster Partition");
    mm.add_module<NMers>("All nmers");
    mm.add_module<AO2Atom>("AO Center to Atom Mapper");
    mm.add_module<NucleiAO>("Nuclei-AO Fragmenter");
    mm.add_module<SystemAO>("System-AO Fragmenter");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Cluster Partition", "Connectivity", "Covalent Radius");
    mm.change_submod("System-AO Fragmenter", "Nuclei-AO Fragmenter",
                     "Nuclei-AO Fragmenter");
}

} // namespace ghostfragment::partitioned
