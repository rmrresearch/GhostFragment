#include "connectivity/connectivity.hpp"
#include "drivers/drivers.hpp"
#include "energy/energy.hpp"
#include "ghostfragment/load_modules.hpp"
#include "partitioned/partitioned.hpp"

namespace ghostfragment {

void load_modules(pluginplay::ModuleManager& mm) {
    connectivity::load_modules(mm);
    drivers::load_modules(mm);
    energy::load_modules(mm);
    partitioned::load_modules(mm);

    connectivity::set_defaults(mm);
    drivers::set_defaults(mm);
    energy::set_defaults(mm);
    partitioned::set_defaults(mm);
}

} // namespace ghostfragment
