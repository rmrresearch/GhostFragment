#pragma once
#include <sde/sde.hpp>

namespace property_types {

/** @brief Property type for quantities associated with subsystems.
 *
 *  In computational chemistry we often think of the entire system as being
 *  comprised of several subsystems. The idea of this property type is to
 *  express progrmatically that we need a quantity to be computed for each
 *  subsystem. There are at least two ways we see modules
 *  Fragmented property type:
 *
 *  1. By fragmenting an object
 *  2. By fragmenting a property type
 *
 *  The first scenario uses a property type `Fragmented<Object>` where `Object`
 *  is a normal class. For example, a module satisfying the property type
 *  `Fragmented<Molecule>` takes a Molecule instance as input and fragments it.
 *  The second scenario looks like `Fragmented<PropertyType>` where
 *  `PropertyType` is another property type. For example `Fragmented<Energy>`
 *  computes the energy of each subsystem. The distinction between these two
 *  scenarios primarily depends on whether the thing being fragmented is
 *  computed via a module or if it is typically provided as an input.
 *
 *  @tparam Type2Frag Either an object to fragment or a property type to call on
 *                    a set of fragmented objects.
 *
 *  @todo Should we separate these two scenarios into different property types?
 */

template<typename Type2Frag>
DECLARE_TEMPLATED_PROPERTY_TYPE(Fragmented, Type2Frag);

template<typename Type2Frag>
PROPERTY_TYPE_INPUTS(Fragmented<Type2Frag>) {
    // if constexpr(std::is_base_property_type_v<Type2Frag>) {
    //     return Type2Frag::inputs();
    // } else {
    //     return sde::declare_inputs().add_field<Type2Frag>("Supersystem");
    // }
}

template<typename Type2Frag>
PROPERTY_TYPE_RESULTS(Fragmented<Type2Frag>) {
    // T
    // if constexpr(std::is_base_property_type_v<Type2Frag>) {
    //     using return_type = std::map<, double>;
    //     return sde::declare_results().add_field<return_type>("Properties");
    // } else {
    //     using return_type = std::map<type::tag, Type2Frag>;
    //     return sde::declare_results().add_field<return_type>("Objects");
    // }
}

} // namespace property_types