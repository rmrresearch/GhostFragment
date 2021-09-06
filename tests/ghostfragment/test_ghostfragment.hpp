#pragma once
#include "ghostfragment/ghostfragment.hpp"
#include <catch2/catch.hpp>
#include <simde/simde.hpp>

namespace testing {

inline auto initialize() {
    pluginplay::ModuleManager mm;
    ghostfragment::load_modules(mm);
    return mm;
}

inline auto some_atoms() {
    using molecule = simde::type::molecule;
    using atom     = typename molecule::value_type;
    atom H{"H", 1ul};
    atom He{"He", 2ul};
    atom O{"O", 8ul};
    return std::make_tuple(H, He, O);
}

} // namespace testing