#pragma once
#include "ghostfragment/types.hpp"
#include <type_traits>

namespace ghostfragment {
namespace detail_ {

/** @brief Primary template for determining if type @p T is a partition.
 *
 *  The primary template is chosen whenever @p T is not an instantiation of
 *  `type::partition`. When instantiated the primary template of IsPartition
 *  contains a static constexpr member `value` set to false.
 *
 *  @tparam T The type for this trait to determinine whether or not it is an
 *            instance of `type::partition`.
 *
 */
template<typename T>
struct IsPartition : std::false_type{};

/** @brief Specialization of IsPartition for when type @p T is a partition.
 *
 *  This specialization is chosen whenever @p T is an instantiation of
 *  `type::partition`. When instantiated this specialization of IsPartition
 *  contains a static constexpr member `value` set to true.
 *
 *  @tparam T The type for this trait to determinine whether or not it is an
 *            instance of `type::partition`.
 */
template<typename T>
struct IsPartition<type::partition<T>> : std::true_type{};

/** @brief Primary template for determining what object a partition partitions.
 *
 *  The primary template is not implemented. Instead we implement two partial
 *  specializations: one when @p IsPartition is true and one where it is false.
 *  Users of this trait can use `is_partition_v<T>` to set the correct value.
 *
 *  @note This clas is basically `std::conditional`, but we can't use
 *        `std::conditional` because @p T might not have a member `mapped_type`.
 *
 *  @tparam T This trait is tasked with determining what object @p T is a
 *            partition of.
 *  @tparam IsPartition Should be set to true if @p T is an instantiation of
 *                      `type::partition` and set to false otherwise.
 */
template<typename T, bool IsPartition>
struct PartitionedObject;

/** @brief Specializes PartitionedObject for when @p T is a partition.
 *
 *  This specialization is chosen when @p T is an instantiation of
 *  `type::partition<U>` this class will contain a member type `type` set to
 *  `U`.
 *
 *  @tparam T This trait is tasked with determining what object @p T is a
 *            partition of.
 */
template<typename T>
struct PartitionedObject<T, true> { using type = typename T::mapped_type; };

/** @brief Specializes PartitionedObject for when @p T is not a partition.
 *
 *  This specialization is chosen when @p T is not an instantiation of
 *  `type::partition<U>`. This class will contain a member type `type` set to
 *  `T`.
 *
 *  @tparam T This trait is tasked with determining what object @p T is a
 *            partition of.
 */
template<typename T>
struct PartitionedObject<T, false> { using type = T; };

} // namespace detail_

/** @brief Public API for determining if a type @p T is the type of a partition.
 *
 *  This type trait can be used to determine if @p T is an instantiation of
 *  `type::partition`. It will be set to true if @p T is an instantiation of
 *  `type::partition` and false otherwise.
 *
 *  @tparam T This trait will determine if @p T is a partition.
 */
template<typename T>
static constexpr bool is_partition_v = detail_::IsPartition<T>::value;

/** @brief Public API for determining the type of object that @p T is a
 *         partitioning of.
 *
 *  This type trait can be used to determine what object @p T is a partition of.
 *  If @p T is an instantiation of `type::partition<U>` this trait will be set
 *  to `U`. Otherwise this trait will be set to @p T (that is we define every
 *  type as trivially being a partitioning of itself).
 *
 *  @tparam T This trait will determine what the type is that @p T is a
 *            partitioning of.
 */
template<typename T>
using partitioned_object_t =
    typename detail_::PartitionedObject<T, is_partition_v<T>>::type;

} // namespace ghostfragment
