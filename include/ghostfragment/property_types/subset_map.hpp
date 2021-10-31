#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::pt {

template<typename Type2Fragment, typename MappedType>
struct SubsetMapTraits {
    /// Type of the FamilyOfSets used for the keys
    using fos_key_type = libchemist::set_theory::FamilyOfSets<Type2Fragment>;

    /// Type of the FamilyOfSets used for the values
    using fos_value_type = libchemist::set_theory::FamilyOfSets<MappedType>;

    /// Type of the key in the returned map
    using key_type = typename fos_key_type::value_type;

    /// Type of the value in the returned map
    using value_type = typename fos_value_type::value_type;

    using input0_type = const fos_key_type&;
    using input1_type = MappedType;
    using result_type = std::map<key_type, value_type>;
};

template<typename Type2Fragment, typename MappedType>
DECLARE_TEMPLATED_PROPERTY_TYPE(SubsetMap, Type2Fragment, MappedType);

template<typename Type2Fragment, typename MappedType>
TEMPLATED_PROPERTY_TYPE_INPUTS(SubsetMap, Type2Fragment, MappedType) {
    using traits_type = SubsetMapTraits<Type2Fragment, MappedType>;
    using input0_type = typename traits_type::input0_type;
    using input1_type = typename traits_type::input1_type;

    return pluginplay::declare_input()
      .add_field<input0_type>("Subsets")
      .template add_field<input1_type>("Object to map");
}

template<typename Type2Fragment, typename MappedType>
TEMPLATED_PROPERTY_TYPE_RESULTS(SubsetMap, Type2Fragment, MappedType) {
    using traits_type = SubsetMapTraits<Type2Fragment, MappedType>;
    using result_type = typename traits_type::result_type;

    return pluginplay::declare_result().add_field<result_type>("map");
}

using Frag2AO = SubsetMap<simde::type::molecule, simde::type::ao_basis_set>;
using Frag2AOTraits =
  SubsetMapTraits<simde::type::molecule, simde::type::ao_basis_set>;

} // namespace ghostfragment::pt
