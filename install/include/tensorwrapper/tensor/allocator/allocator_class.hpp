/*
 * Copyright 2022 NWChemEx-Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "tensorwrapper/tensor/buffer/buffer.hpp"
#include "tensorwrapper/tensor/fields.hpp"
#include "tensorwrapper/tensor/shapes/shapes.hpp"
#include "tensorwrapper/tensor/type_traits/nd_initializer_list_traits.hpp"
#include <memory>
#include <parallelzone/runtime/runtime_view.hpp>
#include <vector>

namespace tensorwrapper::tensor::allocator {

namespace detail_ {

using tile_index_type = std::vector<size_t>;
template<typename ScalarType>
using scalar_tile_populator_type =
  std::function<void(tile_index_type, // lo_bounds
                     tile_index_type, // up_bounds
                     ScalarType*)>;   // row major data
template<typename ScalarType>
using tot_tile_populator_type =
  std::function<void(tile_index_type, // outer index
                     tile_index_type, // lo_bounds
                     tile_index_type, // up_bounds
                     ScalarType*)>;   // row major data

template<typename FieldType, typename ScalarType>
using tile_populator_type =
  std::conditional_t<field::is_scalar_field_v<FieldType>,
                     scalar_tile_populator_type<ScalarType>,
                     tot_tile_populator_type<ScalarType>>;

template<typename ScalarType>
using scalar_element_populator_type =
  std::function<ScalarType(tile_index_type)>;

template<typename ScalarType>
using tot_element_populator_type =
  std::function<ScalarType(tile_index_type,   // outer idx
                           tile_index_type)>; // inner idx

template<typename FieldType, typename ScalarType>
using element_populator_type =
  std::conditional_t<field::is_scalar_field_v<FieldType>,
                     scalar_element_populator_type<ScalarType>,
                     tot_element_populator_type<ScalarType>>;

} // namespace detail_

/** @brief Abstracts away the details of how the TensorWrapper's internal tensor
 *         is formed.
 *
 *  In TensorWrapper we basically treat the wrapped tensor as the memory of our
 *  tensor wrapper. Standard C++ practice is to have allocator classes for
 *  allocating/deallocating memory, hence we introduce a class hierarchy of
 *  allocators for allocating the wrapped tensor. Allocators are responsible for
 *  hiding the general set-up details of the wrapped tensor when given a size.
 *  Some examples of things the allocator can hide if we assume that TiledArray
 *  is the wrapped tensor library: distribution, tiling, and whether tiles are
 *  lazy.
 *
 *  The Allocator class defines the common API that all TensorWrapper allocators
 *  must have. We borrow from the C++ concept of allocator, but aren't too
 *  concerned with following it to the letter given that the tensors returned
 *  by the allocator aren't usable as memory in the C++ sense anyways (*i.e.*,
 *  even if we followed the API to the letter, you're not going to be doing
 *  something like: `std::vector<TA::DistArrayD, Allocator<DistArrayD>>`).
 *
 *  Adding A New Allocator Specialization
 *  =====================================
 *
 *  To create a new Allocator specialization of type U:
 *  1. Derive a class from Allocator<FieldType>. Depending on the details of
 *     your class it may make senese for your class to also be templated on
 *     additional details beside the field type.
 *  2. Implement `clone_()`. In most cases this implementation is just:
 *     ```
 *     allocator_ptr clone_() const overrride {
 *         return std::make_unique<U>(*this);
 *     }
 *     ```
 *     as long as the copy ctor works correctly.
 *  3. Implement `is_equal_()`. In most cases this is just:
 *     ```
 *     bool is_equal_(const Allocator<FieldType>& rhs) const noexcept
 *      override {
 *         const auto prhs = dynamic_cast<const U*>(&rhs);
 *         if(!prhs) return false;
 *         return *this == *prhs;
 *     }
 *     ```
 *     as long as the non-polymorphic comparison operator (*i.e.*, operator==)
 *     is implemented correctly.
 *  4. Implement make_tr_(). The implementation of this function is highly
 *     specific to  the derived class.
 *
 *  Realistically 4. should probably be made more general, but we're punting on
 *  that for now.
 */
template<typename FieldType>
class Allocator {
private:
    /// The type of this allocator
    using my_type = Allocator<FieldType>;

public:
    /// The type of object this allocator can make
    using value_type    = buffer::Buffer<FieldType>;
    using value_pointer = std::unique_ptr<value_type>;

    /// The base type of an object which models a tensor's shape
    using shape_type = Shape<FieldType>;

    /// Unsigned integral type used to specify the extent of a mode
    using extent_type = typename shape_type::size_type;

    /// Container-of-extents type used to specify the extents of all modes
    using extents_type = typename shape_type::extents_type;

    /// Container-of-tiling type used to specify the tiling of all modes
    using tiling_type = typename shape_type::tiling_type;

    /// Pointer to the base class of the allocator hierarchy
    using allocator_ptr = std::unique_ptr<my_type>;

    /// Type of the object describing the runtime
    using runtime_type = parallelzone::runtime::RuntimeView;

    /// A read-write reference to the runtime object
    using runtime_reference = runtime_type&;

    /// Type of the scalars in the tensor
    using scalar_type = double;

    /// Type of tensor population functor
    using tile_populator_type =
      detail_::tile_populator_type<FieldType, scalar_type>;
    using element_populator_type =
      detail_::element_populator_type<FieldType, scalar_type>;

    /// TODO: Add parallelzone::Runtime parameters back once it has sane
    ///       construction options
    // /** @brief Creates a new allocator with the optionally specified runtime.
    //  *
    //  *  Allocator is a pure-virtual class, so instances of it can not
    //  actually
    //  *  be created. Instead the ctor provides derived classes with an API for
    //  *  setting the runtime.
    //  *
    //  *  @param[in] world The runtime the allocator will use for allocating.
    //  *                   Defaults to `TA::get_default_world()`.
    //  *
    //  *  @throw None No throw guarantee.
    //  */
    // explicit Allocator(runtime_reference world = runtime_type{});

    /** @brief Polymorphic copy.
     *
     *  The `clone()` member allows users of an Allocator to create polymorphic
     *  copies (*i.e.*, copies that include the derived state too) through the
     *  base class. This is important since the TensorWrapper class interacts
     *  with Allocator hierarchies through the base class.
     *
     *  @return A deep-, polymoprhic-copy of the current allocator.
     *
     *  @throw std::bad_alloc if there is insufficient memory to allocate the
     *                        copy. Strong throw guarantee.
     */
    allocator_ptr clone() const { return clone_(); }

    /** @brief Polymorphic comparison operator.
     *
     *  This function comares two Allocator instances polymorphically. Two
     *  Allocator instances are equal if they were both declared as the same
     *  type, and all parts of the class hierarchy compare equal.
     *
     *
     *  @param[in] other The allocator we are comparing to.
     *
     *  @return True if this is polymorphically equal to @p other. False
     *          otherwise.
     */
    bool is_equal(const Allocator& other) const;

    /// Standard default dtor
    virtual ~Allocator() noexcept = default;

    value_pointer allocate(const tile_populator_type& fxn,
                           const shape_type& shape) const;
    value_pointer allocate(const element_populator_type& fxn,
                           const shape_type& shape) const;
    value_pointer allocate(const shape_type& shape) const;

    value_pointer reallocate(const value_type& buf,
                             const shape_type& shape) const;

    /** @brief Non-polymorphically compares two Allocators for equality.
     *
     *  This is a non-polymorphic comparison of two Allocator instances, meaning
     *  that derived state is NOT considered in the comparison. The only state
     *  that an allocator possess is the runtime. Two Allocators are equivalent
     *  if they share the same runtime.
     *
     *  @todo When ParallelZone rolls out actually compare runtimes.
     *
     *  @param[in] rhs The Allocator instance we are comparing to.
     *
     *  @return True if this instance is equal to @p rhs and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const Allocator& rhs) const { return true; }

    /** @brief Non-polymorphically compares two Allocators for equality.
     *
     *  This is a non-polymorphic comparison of two Allocator instances, meaning
     *  that derived state is NOT considered in the comparison. The only state
     *  that an allocator possess is the runtime. Two Allocators are equivalent
     *  if they share the same runtime.
     *
     *  @todo When ParallelZone rolls out actually compare runtimes.
     *
     *  @param[in] rhs The Allocator instance we are comparing to.
     *
     *  @return False if this instance is equal to @p rhs and true otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator!=(const Allocator& rhs) const { return !((*this) == rhs); }

    // /** @brief Provides access to the runtime to which the tensor will
    // belong.
    //  *
    //  *  At the moment the runtime associated with the tensor is just a
    //  *  TiledArray World. This will change when ParallelZone rolls out.
    //  *
    //  *  @return A read/write reference to the runtime.
    //  *
    //  *  @throw None No throw guarantee.
    //  */
    // runtime_reference runtime() const { return m_world_; }

protected:
    /// Temporary until runtime is sorted
    Allocator() = default;

    /// To help derived classes implement clone_
    Allocator(const Allocator&) = default;

    /// Deleted to avoid slicing
    Allocator(Allocator&&) = delete;

    /// Deleted to avoid slicing
    Allocator& operator=(const Allocator&) = delete;

    /// Deleted to avoid slicing
    Allocator& operator=(Allocator&&) = delete;

    /** @brief Hook for polymorphic copy.
     *
     *  The clone_ member needs to be implemented by the derived class such that
     *  it returns an object of type allocator_ptr that is a deep copy of the
     *  current instance.
     *
     *  @throw std::bad_alloc The derived class may throw std::bad_alloc if a
     *                        problem arises making the deep copy. The derived
     *                        class is responsible for ensuring that if an
     *                        exception does arise, this function obeys a strong
     *                        throw guarantee.
     */
    virtual allocator_ptr clone_() const = 0;

    virtual value_pointer allocate_(const tile_populator_type&,
                                    const shape_type&) const   = 0;
    virtual value_pointer allocate_(const element_populator_type&,
                                    const shape_type&) const   = 0;
    virtual value_pointer reallocate_(const value_type&,
                                      const shape_type&) const = 0;

    /** @brief Hook for polymorphically comparing two Allocators.
     *
     *  The derived class is responsible for checking that @p rhs is the same
     *  type as it (via a dynamic_cast). If @p rhs is the same type, then the
     *  derived class is also responsible for comparing all state between the
     *  current instance and @p rhs.
     *
     *  @param[in] rhs The allocator to compare to.
     *
     *  @return True if the current instance polymorphically
     *
     *  @throw None The derived class is responsible for making sure the
     *              comparison is done in a no-throw manner.
     */
    virtual bool is_equal_(const Allocator& rhs) const noexcept;
};

//------------------------------------------------------------------------------
//                         Inline Implementations
//------------------------------------------------------------------------------

template<typename FieldType>
bool Allocator<FieldType>::is_equal(const Allocator& other) const {
    // Needs to be symmetrized to verify both have the same most-derived type
    return is_equal_(other) && other.is_equal_(*this);
}

template<typename FieldType>
typename Allocator<FieldType>::value_pointer Allocator<FieldType>::allocate(
  const tile_populator_type& fxn, const shape_type& shape) const {
    return allocate_(fxn, shape);
}

template<typename FieldType>
typename Allocator<FieldType>::value_pointer Allocator<FieldType>::allocate(
  const element_populator_type& fxn, const shape_type& shape) const {
    return allocate_(fxn, shape);
}

template<typename FieldType>
typename Allocator<FieldType>::value_pointer Allocator<FieldType>::allocate(
  const shape_type& shape) const {
    tile_populator_type fxn;
    return allocate_(fxn, shape);
}

template<typename FieldType>
typename Allocator<FieldType>::value_pointer Allocator<FieldType>::reallocate(
  const value_type& buffer, const shape_type& shape) const {
    return reallocate_(buffer, shape);
}

template<typename FieldType>
bool Allocator<FieldType>::is_equal_(const Allocator& rhs) const noexcept {
    return *this == rhs;
}

} // namespace tensorwrapper::tensor::allocator
