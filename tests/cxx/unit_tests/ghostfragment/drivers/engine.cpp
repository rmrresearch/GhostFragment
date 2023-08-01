#include "../test_ghostfragment.hpp"
#include "hydrocarbon/hydrocarbon.h"
#include <ghostfragment/drivers/engine.cpp>
#include <ghostfragment/property_types/fragmented_molecule.hpp>
#include <ghostfragment/property_types/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/property_types.hpp>

using namespace ghostfragment;
using namespace testing;

using system_type = chemist::ChemicalSystem;
using pair_type   = std::pair<system_type, double>;
using input_type  = std::vector<pair_type>;
using energy_type = simde::Energy;

namespace {

system_type methane(hydrocarbon(1));
system_type ethane(hydrocarbon(2));
system_type propane(hydrocarbon(3));

auto make_lambda() {
    return pluginplay::make_lambda<energy_type>([=](const auto& pair_in) {
        if(pair_in == methane)
            return 1.1;
        else if(pair_in == ethane)
            return -2.2;
        else if(pair_in == propane)
            return 3.3;
        else
            return 100.0;
    });
}

} // namespace

TEST_CASE("Engine") {
    SECTION("Empty System") {
        input_type input;
        float test = engine(input, make_lambda());

        float corr = 0.0;

        REQUIRE(test == Approx(corr));
    }

    SECTION("One System") {
        input_type input{{methane, 1.0}};
        float test = engine(input, make_lambda());

        float corr = 1.1;

        REQUIRE(test == Approx(corr));
    }

    SECTION("Two Unique Systems") {
        input_type input{{methane, 1.0}, {ethane, 2.0}};
        float test = engine(input, make_lambda());

        float corr = -3.3;

        REQUIRE(test == Approx(corr));
    }

    SECTION("Two Equivalent Systems") {
        input_type input{{methane, 1.0}, {methane, 2.0}};
        float test = engine(input, make_lambda());

        float corr = 3.3;

        REQUIRE(test == Approx(corr));        
    }

    SECTION("Three Unique Systems") {
        input_type input{{methane, 1.0}, {ethane, 2.0}, {propane, 3.0}};
        float test = engine(input, make_lambda());

        float corr = 6.6;

        REQUIRE(test == Approx(corr));
    }

    SECTION("Three Systems with One Pair") {
        input_type input{{methane, 1.0}, {methane, 2.0}, {propane, 3.0}};
        float test = engine(input, make_lambda());

        float corr = 13.2;

        REQUIRE(test == Approx(corr));  
    }
}
