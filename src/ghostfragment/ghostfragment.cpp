#include "ghostfragment/load_modules.hpp"
#include "modules.hpp"
#include "partitioned/partitioned.hpp"
namespace {

void set_defaults(pluginplay::ModuleManager& mm) {
    mm.change_submod("Cluster Partition", "Connectivity", "Covalent Radius");
}

} // namespace

namespace ghostfragment {

void load_modules(pluginplay::ModuleManager& mm) {
    partitioned::load_modules(mm);
    mm.add_module<CovRadii>("Covalent Radius");
    set_defaults(mm);
}

} // namespace ghostfragment