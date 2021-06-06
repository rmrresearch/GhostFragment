#pragma once
#include "ghostfragment/load_modules.hpp"
#include "ghostfragment/property_types/property_types.hpp"
#include <catch2/catch.hpp>
#include <sde/sde.hpp>

namespace testing {

inline auto initialize() {
    sde::ModuleManager mm;
    ghostfragment::load_modules(mm);
    return mm;
}

} // namespace testing