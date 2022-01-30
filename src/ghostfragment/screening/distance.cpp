#include "screening.hpp"

#include "ghostfragment/property_types/property_types.hpp"

namespace ghostfragment::screening {

using my_pt = pt::NMerScreener;

constexpr auto desc = R"""(
Distance Based Screening
------------------------

Many of the initial NMer screening routines relied on distance based cutoffs to
select which NMers survived. 
)""";

MODULE_CTOR(Distance) {
    description(desc);

    satisfies_property_type<my_pt>();
}

MODULE_RUN(Distance) {
    const auto& [capped_frags] = my_pt::unwrap_inputs(inputs);

    type::nmers nmers;
    auto rv = results();
    return my_pt::wrap_results(rv, nmers);
}

} // namespace ghostfragment::screening