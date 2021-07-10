#pragma once
#include "property_types/types.hpp"

namespace property_types {

template<typename ElementType>
DECLARE_TEMPLATED_PROPERTY_TYPE(AOSpace, ElementType);

template<typename ElementType>
PROPERTY_TYPE_INPUTS(AOSpace<ElementType>) {
    return sde::declare_input().add_field<type::molecule>("Molecule");
}

template<typename ElementType>
PROPERTY_TYPE_RESULTS(AOSpace<ElementType>) {
    using return_t = type::ao_space_t<ElementType>;
    return sde::declare_result().add_field<return_t>("AO Basis Set");
}

} // namespace property_types