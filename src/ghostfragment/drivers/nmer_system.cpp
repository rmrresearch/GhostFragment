#include "drivers.hpp"
#include <ghostfragment/property_types/property_types.hpp>

namespace ghostfragment::drivers {

using nmer_screener_pt = pt::NMerScreener;
using my_pt            = pt::NMerSystem;
using traits_type      = pt::NMerSystemTraits;

const auto mod_desc = R"()";

MODULE_CTOR(NMerSystem) {
    description(mod_desc);

    satisfies_property_type<my_pt>();
    add_submodule<nmer_screener_pt>("NMer Screener");
}

MODULE_RUN(NMerSystem) {
    using result_type = traits_type::result_type;

    const auto& [frags, n] = my_pt::unwrap_inputs(inputs);
    const auto N           = frags.nfrags();

    // Basic error checking
    if(N < n)
        throw std::runtime_error("Can not create " + std::to_string(n) +
                                 "-mers with only " + std::to_string(N) +
                                 " fragments.");

    // n == 0 and n == 1 edge cases
    if(n < 2) {
        type::nmers nmers(frags.frags());

        if(n == 1) {
            for(std::size_t i = 0; i < N; ++i) {
                auto frag = nmers.new_subset();
                frag.insert(i);
                nmers.insert(frag);
            }
        }
        auto rv = results();
        result_type nmer_system(frags, nmers);
        return my_pt::wrap_results(rv, nmer_system);
    }

    type::fragment_to_caps f2cap;
    for(auto frag_i = 0; frag_i < frags.nfrags(); ++frag_i) {
        const auto& frag = frags.fragment(frag_i);
        f2cap.emplace(frag, frags.caps(frag));
    }

    auto& nmer_mod      = submods.at("NMer Screener");
    const auto& [nmers] = nmer_mod.run_as<nmer_screener_pt>(f2cap);

    result_type nmer_system(frags, nmers);

    auto rv = results();
    return my_pt::wrap_results(rv, nmer_system);
}

} // namespace ghostfragment::drivers
