#include <simde/simde.hpp>
#include <pluginplay/module.hpp>

using input_type = std::vector<std::pair<chemist::ChemicalSystem, double>>;
using pt = simde::Energy;
using mod_type = pluginplay::Module;

inline auto engine(input_type input, mod_type mod) {
    auto weighted_sum = 0.0;
    for(auto in : input) {
        weighted_sum += mod.run_as<pt>(in.first);
    }

    return weighted_sum;
}