#pragma once
#include "ghostfragment/types.hpp"
#include "ghostfragment/type_traits.hpp"
#include <sde/sde.hpp>

namespace property_types {

/** @brief Property type for requesting that an object be partitioned
 *
 *  Chemistry concepts such as functional groups, polymers, coordination
 *  compounds, etc. are predicated on the idea that we can understand the
 *  chemistry of large systems by understanding the chemistry of the system's
 *  parts. That said there are a lot of different ways to partition a system
 *  (for a molecule with @f$n@f$ atoms there are @f$B_n@f$ partitions where
 *  @f$B_n@f$ is the @f$n@f$-th Bell number). In practice the partitioning is
 *  usually not arbitrary, but the result of some algorithm which relies on
 *  chemical concepts such as bonds and/or spatial distances to assign the
 *  partitions. Nonetheless, there are still a large number of algorithms and
 *  this property type is for any module which partitions an object into
 *  subobjects. Examples are:
 *  - `Partitoned<Molecule>` for partitioning a molecular system
 *  - `Partitoned<AOBasisSet<double>>` for partitiong basis sets
 *
 *  @tparam Type2Partition The object type we are partitioning. Expected to be
 *                         set-like although exactly what the module does with
 *                         the type is up to the module.
 *
 *  @note This property type should not be confused with ManyBody<T> which
 *        computes a property type for a partitoned system. For ManyBody<T>, T
 *        will always be a property type, whereas for Partitoned<T> T will be
 *        an object like Molecule, ChemicalSystem, etc.
 */

template<typename Type2Partition>
DECLARE_TEMPLATED_PROPERTY_TYPE(Partitioned, Type2Partition);

template<typename Type2Partition>
PROPERTY_TYPE_INPUTS(Partitioned<Type2Partition>) {
    return sde::declare_input().add_field<Type2Partition>(
      "Object to Partition");
}

template<typename Type2Partition>
PROPERTY_TYPE_RESULTS(Partitioned<Type2Partition>) {
    // Fundamental type of the object being partitioned (needed in case
    // Type2Partition is also a partition)
    using obj_type = ghostfragment::partitioned_object_t<Type2Partition>;

    using return_type = ghostfragment::type::partition<obj_type>;
    return sde::declare_result().add_field<return_type>("Partitioned Object");
}

} // namespace property_types
