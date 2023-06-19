#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::capping {

DECLARE_MODULE(SingleAtom);
DECLARE_MODULE(DCLC);

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<SingleAtom>("Atomic Capping");
    mm.add_module<DCLC>("DCLC Capping");
}

double average_bond_length(chemist::Nuclei m,
const chemist::topology::ConnectivityTable connections,
std::size_t z_x, std::size_t z_c);

inline void set_defaults(pluginplay::ModuleManager& mm) {}

} // namespace ghostfragment::capping
