#include "capping/capping.hpp"
#include "connectivity/connectivity.hpp"
#include "drivers/drivers.hpp"
#include "expressions/expressions.hpp"
#include "partitioned/partitioned.hpp"
#include "screening/screening.hpp"
#include <ghostfragment/load_modules.hpp>

namespace ghostfragment {

DEFINE_PLUGIN(ghostfragment) {
    capping::load_modules(mm);
    connectivity::load_modules(mm);
    drivers::load_modules(mm);
    expressions::load_modules(mm);
    partitioned::load_modules(mm);
    screening::load_modules(mm);

    capping::set_defaults(mm);
    connectivity::set_defaults(mm);
    drivers::set_defaults(mm);
    expressions::set_defaults(mm);
    partitioned::set_defaults(mm);
    screening::set_defaults(mm);
}

} // namespace ghostfragment
