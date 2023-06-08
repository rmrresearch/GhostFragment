#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::partitioned {

DECLARE_MODULE(Cluster);
DECLARE_MODULE(HeavyAtom);
// DECLARE_MODULE(NMers);
DECLARE_MODULE(AO2Atom);
DECLARE_MODULE(NucleiAO);
// DECLARE_MODULE(SystemAO);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<Cluster>("Cluster Partition");
    mm.add_module<HeavyAtom>("Heavy Atom Partition");
    // mm.add_module<NMers>("All nmers");
    mm.add_module<AO2Atom>("AO Center to Atom Mapper");
    mm.add_module<NucleiAO>("Nuclei-AO Fragmenter");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Heavy Atom Partition", "Connectivity", "Covalent Radius");
}

} // namespace ghostfragment::partitioned
