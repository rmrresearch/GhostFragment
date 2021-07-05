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

inline auto some_atoms() {
    using molecule = ghostfragment::type::molecule;
    using atom     = typename molecule::value_type;
    atom H{"H", 1ul};
    atom He{"He", 2ul};
    atom O{"O", 8ul};
    return std::make_tuple(H, He, O);
}

} // namespace testing