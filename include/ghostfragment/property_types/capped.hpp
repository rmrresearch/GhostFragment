#pragma once
#include "ghostfragment/types.hpp"
#include <simde/simde.hpp>

namespace ghostfragment::pt {

/** @brief Struct for helping determine the types associated with the Capped
 *         property type.
 *
 *  @tparam Type2Cap The type of the object we are capping. Expected to be a
 *                   specialization of FamilyOfSets.
 */
template<typename Type2Cap>
struct CappedTraits {
private:
    using subset_type = typename Type2Cap::value_type;
    using cap_set     = typename type::fragmented_molecule::value_type;

public:
    using input_type = const Type2Cap&;

    using result_type = std::map<subset_type, cap_set>;
};

template<typename Type2Cap>
DECLARE_TEMPLATED_PROPERTY_TYPE(Capped, Type2Cap);

template<typename Type2Cap>
TEMPLATED_PROPERTY_TYPE_INPUTS(Capped, Type2Cap) {
    using traits_type = CappedTraits<Type2Cap>;
    using input_type  = typename traits_type::input_type;
    return pluginplay::declare_input().add_field<input_type>("Systems to cap");
}

template<typename Type2Cap>
TEMPLATED_PROPERTY_TYPE_RESULTS(Capped, Type2Cap) {
    using traits_type = CappedTraits<Type2Cap>;
    using result_type = typename traits_type::result_type;
    return pluginplay::declare_result().add_field<result_type>(
      "Capped systems");
}

using CappedFragments       = Capped<type::fragmented_molecule>;
using CappedFragmentsTraits = CappedTraits<type::fragmented_molecule>;

} // namespace ghostfragment::pt