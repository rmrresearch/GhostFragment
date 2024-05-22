#pragma once
#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <chemist/topology/connectivity_table.hpp>
#include <ghostfragment/property_types/topology/broken_bonds.hpp>
#include <simde/simde.hpp>

namespace ghostfragment::pt {

/** @brief Struct for helping determine the types associated with the Capped
 *         property type.
 *
 *  @tparam Type2Cap The type of the object we are capping. Expected to be a
 *                   specialization of FamilyOfSets.
 */
struct CappedFragmentsTraits {
    using frags_type = chemist::fragmenting::FragmentedNuclei<chemist::Nuclei>;
    using broken_bonds_type = BrokenBondsTraits::result_type;
    using result_type       = frags_type;
};

DECLARE_PROPERTY_TYPE(CappedFragments);

PROPERTY_TYPE_INPUTS(CappedFragments) {
    using traits_type = CappedFragmentsTraits;
    using input0_type = typename traits_type::frags_type;
    using input1_type = const typename traits_type::broken_bonds_type&;
    return pluginplay::declare_input()
      .add_field<input0_type>("Fragments to cap")
      .template add_field<input1_type>("System connectivity");
}

PROPERTY_TYPE_RESULTS(CappedFragments) {
    using traits_type = CappedFragmentsTraits;
    using result_type = typename traits_type::result_type;
    return pluginplay::declare_result().add_field<result_type>(
      "Capped Fragments");
}

} // namespace ghostfragment::pt
