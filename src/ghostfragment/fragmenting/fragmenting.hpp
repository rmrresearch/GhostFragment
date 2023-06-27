#pragma once
#include <simde/simde.hpp>

#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::fragmenting {

DECLARE_MODULE(Cluster);
DECLARE_MODULE(HeavyAtom);
// DECLARE_MODULE(NMers);
DECLARE_MODULE(AO2Atom);
DECLARE_MODULE(NucleiAO);
// DECLARE_MODULE(SystemAO);
DECLARE_MODULE(BondBased);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<Cluster>("Cluster Partition");
    mm.add_module<HeavyAtom>("Heavy Atom Partition");
    // mm.add_module<NMers>("All nmers");
    mm.add_module<AO2Atom>("AO Center to Atom Mapper");
    mm.add_module<NucleiAO>("Nuclei-AO Fragmenter");
    mm.add_module<BondBased>("Bond-Based Fragmenter");
}

inline void set_defaults(pluginplay::ModuleManager& mm) {
}

} // namespace ghostfragment::fragmenting
