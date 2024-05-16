#pragma once
#include <chemist/fragmenting/capping/cap_set.hpp>
#include <chemist/fragmenting/fragmented_nuclei.hpp>

#include <simde/simde.hpp>

namespace ghostfragment::pt {

/** @brief Struct for helping determine the types associated with the Capped
 *         property type.
 *
 *  @tparam Type2Cap The type of the object we are capping. Expected to be a
 *                   specialization of FamilyOfSets.
 */
struct CappedTraits {
    using input_type  = const chemist::FragmentedNuclei<Nuclei>&;
    using result_type = chemist::CapSet;
};

DECLARE_PROPERTY_TYPE(Capped);

PROPERTY_TYPE_INPUTS(Capped) {
    using traits_type = CappedTraits;
    using input_type  = typename traits_type::input_type;
    return pluginplay::declare_input().add_field<input_type>("Systems to cap");
}

PROPERTY_TYPE_RESULTS(Capped) {
    using traits_type = CappedTraits;
    using result_type = typename traits_type::result_type;
    return pluginplay::declare_result().add_field<result_type>("Caps");
}

} // namespace ghostfragment::pt
