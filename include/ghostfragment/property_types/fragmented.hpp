#pragma once
#include <sde/sde.hpp>

namespace ghostfragment {

template<typename Type2Frag>
DECLARE_TEMPLATED_PROPERTY_TYPE(Fragmented, Type2Frag);

template<typename Type2Frag>
PROPERTY_TYPE_INPUTS(Fragmented<Type2Frag>) {
    if constexpr(std::is_base_property_type_v<Type2Frag>) {
        return Type2Frag::inputs();
    } else {
        return sde::declare_inputs().add_field<Type2Frag>("Supersystem");
    }
}

template<typename Type2Frag>
PROPERTY_TYPE_RESULTS(Fragmented<Type2Frag>) {
    if constexpr(std::is_base_property_type_v<Type2Frag>) {
        using return_type = std::map<type::tag, double>;
        return sde::declare_results().add_field<return_type>("Properties");
    } else {
        using return_type = std::map<type::tag, Type2Frag>;
        return sde::declare_results().add_field<return_type>("Objects");
    }
}

} // namespace ghostfragment