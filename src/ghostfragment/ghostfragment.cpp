#include "connectivity/connectivity.hpp"
#include "energy/energy.hpp"
#include "ghostfragment/load_modules.hpp"
#include "partitioned/partitioned.hpp"
namespace ghostfragment {

void load_modules(pluginplay::ModuleManager& mm) {
    connectivity::load_modules(mm);
    energy::load_modules(mm);
    partitioned::load_modules(mm);

    energy::set_defaults(mm);
    partitioned::set_defaults(mm);
}

} // namespace ghostfragment
