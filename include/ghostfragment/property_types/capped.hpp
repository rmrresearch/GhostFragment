#pragma once
#include <ghostfragment/caps.hpp>
#include <ghostfragment/types.hpp>

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
    using frag_type = typename Type2Cap::value_type;
    using cap_set   = type::fragmented<Caps>;
    using cap_type  = typename cap_set::value_type;

public:
    using input_type  = const Type2Cap&;
    using result_type = std::map<frag_type, cap_type>;
};

/** @brief Property type for a series of "capped" atomic systems.
 *
 *  In theories which require decomposing a molecular supersystem into
 *  molecular subsystems the decomposition of large covalently bonded molecules
 *  will usually sever covalent bonds. To restore the proper valency one "caps"
 *  the bonds. There are a number of ways of capping such bonds. The modules
 *  implementing the various capping strategies satisfy this property type.
 *
 *  @tparam Type2Cap The set of objects being capped. Expected to be a
 *                   specialization of FamilyOfSets.
 */
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
    return pluginplay::declare_result().add_field<result_type>("Caps");
}

using CappedFragments       = Capped<type::fragmented_molecule>;
using CappedFragmentsTraits = CappedTraits<type::fragmented_molecule>;

using CappedNMers       = Capped<type::nmers>;
using CappedNMersTraits = CappedTraits<type::nmers>;

} // namespace ghostfragment::pt
