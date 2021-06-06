#include "ghostfragment/load_modules.hpp"
#include "modules.hpp"

namespace ghostfragment {

void load_modules(sde::ModuleManager& mm) {
    mm.add_module<CovRadii>("Covalent Radius");
}

} // namespace ghostfragment