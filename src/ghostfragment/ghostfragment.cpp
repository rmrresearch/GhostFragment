#include "ghostfragment/load_modules.hpp"
#include "modules.hpp"

namespace {

void set_defaults(sde::ModuleManager& mm) {
    mm.change_submod("Cluster Partition", "Connectivity", "Covalent Radius");
}

} // namespace

namespace ghostfragment {

void load_modules(sde::ModuleManager& mm) {
    mm.add_module<ClusterPartitioner>("Cluster Partition");
    mm.add_module<CovRadii>("Covalent Radius");

    set_defaults(mm);
}

} // namespace ghostfragment