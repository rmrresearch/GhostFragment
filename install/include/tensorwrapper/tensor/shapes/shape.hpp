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
#include "tensorwrapper/sparse_map/index.hpp"
#include "tensorwrapper/tensor/fields.hpp"
#include <map>
#include <memory>
#include <vector>

namespace tensorwrapper::tensor {
namespace detail_ {
template<typename FieldType>
class ShapePIMPL;
} // namespace detail_

/** @brief Object describing a tensor's elemental layout.
 *
 *  The shape of a tensor is usually taken to mean the number of modes, and
 *  the lengths of each of said modes. Here we generalize a bit and also
 *  include the sparsity as part of the shape.
 *
 *  The Shape class is a complete class on its own; however, it is possible to
 *  customize the behavior by deriving from this class and overriding:
 *
 *  - clone_
 *  - make_tensor_
 *
 *  @tparam FieldType The types of the elements in the tensor. Expected to
 *                    be either Scalar or Tensor.
 */
template<typename FieldType>
class Shape {
private:
    /// Type of this instance
    using my_type = Shape<FieldType>;

    /// Type of the PIMPL associated with this instance
    using pimpl_type = detail_::ShapePIMPL<FieldType>;

    /// Determines if @p T is a different field type than @p FieldType
    template<typename T>
    static constexpr bool not_my_field_v = !std::is_same_v<FieldType, T>;

    /// Enables a function when @p T is a different field than @p FieldType
    template<typename T>
    using enable_if_not_my_field_t = std::enable_if_t<not_my_field_v<T>>;

public:
    /// Type of a pointer to a PIMPL instance
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    /// Type of the field the associated tensor is over
    using field_type = FieldType;

    /// Type used for indexing and offsets
    using size_type = std::size_t;

    /// Type used for initializer_lists of sizes
    using index_type = sparse_map::Index;

    /// Type used to provide/return extents (outer extents for FieldType ==
    /// Tensor)
    using extents_type = std::vector<size_type>;

    /// Type of a read-only reference to the (outer) extents
    using const_extents_reference = const extents_type&;

    /// Type used to treat inner-extents
    using inner_extents_type =
      std::conditional_t<field::is_scalar_field_v<FieldType>, size_type,
                         std::map<index_type, Shape<field::Scalar>>>;

    /// Type of a read-only reference to the inner
    using const_inner_extents_reference = const inner_extents_type&;

    /// Type used to specify the tiling of the outer modes
    using tiling_type = std::vector<std::vector<size_type>>;

    /// Type of a read-only reference to the outer modes
    using const_tiling_reference = const tiling_type&;

    /// Type of a pointer to this class
    using pointer_type = std::unique_ptr<my_type>;

    /** @brief Creates a shape with no extents.
     *
     *  This ctor creates a Shape object with no PIMPL. The resulting object is
     *  primarily usable as a temporary and has no state unless it is assigned
     *  to.
     *
     *  @throw None No throw guarantee.
     */
    Shape() noexcept;

    /** @brief Creates a shape with the provided extents.
     *
     *  Assuming @p extents is `r` elements long, the shape which results from
     *  this call describes:
     *
     *  - A rank `r` tensor such that the `i`-th mode has a length of
     *    `extents[i]` (FieldType == field::Scalar), or
     *  - A tensor with `r` independent modes such that the `i`-the independent
     *    mode has a length of `extents[i]` (FieldType == field::Tensor)
     *
     *  @param[in] extents How long each mode of the corresponding tensor is.
     *
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL. Strong
     *                        throw guarantee.
     */
    explicit Shape(extents_type extents, inner_extents_type inner_extents = {});

    /** @brief Creates a shape with the provided tiling.
     *
     *  @param[in] tiling How each mode of the corresponding tensor is tiled.
     *
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL. Strong
     *                        throw guarantee.
     */
    explicit Shape(tiling_type tiling, inner_extents_type inner_extents = {});

    /** @brief Creates a shape by copying another shape.
     *
     *  Copies internal state of passed shape instance to the constructed
     *  instance.
     *
     *  @param[in] other Shape instance from which to create the constructed
     *                         shape.
     *
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL. Strong
     *                        throw guarantee.
     */
    Shape(const Shape& other);

    /** @brief Creates a shape by moving another shape.
     *
     *  Moves internal state of passed shape instance to the constructed
     *  instance.
     *
     *  @param[in/out] other Shape instance from which to create the constructed
     *                       shape. Contains default state on return.
     */
    Shape(Shape&& other) noexcept;

    /** @brief Copies the internal state of another Shape instance to the
     *         current instance.
     *
     *  Replace the internal state of the current Shape instance with
     *  a copy of the internal state of another instance.
     *
     *  @param[in] other Shape instance which is to be copied.
     *  @returns   Reference to current shape instance after copy
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL. Strong
     *                        throw guarantee.
     */
    Shape& operator=(const Shape& other);

    /** @brief Moves the internal state of another Shape instance to the
     *         current instance.
     *
     *  Replace the internal state of the current Shape instance with
     *  the internal state of another instance.
     *
     *  @param[in/out] other Shape instance which is to be moved. Contains
     *                       default state on return.
     *  @returns   Reference to current shape instance after move
     */
    Shape& operator=(Shape&& other) noexcept;

    /// Defaulted dtor
    virtual ~Shape() noexcept;

    /** @brief Polymorphic deep-copy.
     *
     *  This function makes a deep-copy of the current instance. The deep copy
     *  includes all state in the Shape class as well as in any derived classes.
     *
     *  @return A deep copy of this instance, returned as a pointer to the base
     *          class.
     *
     *  @throw std::bad_alloc if there is a problem allocating the new instance.
     *                        Strong throw guarantee.
     */
    pointer_type clone() const { return clone_(); }

    /** @brief Returns the extents of the tensor described by this Shape.
     *
     *  The extents describe the length of each of the tensor's (independent)
     *  modes. Note that for `FieldType == field::Scalar` all modes are
     *  independent.
     *
     *  @return For a tensor with `r` independent modes the resulting object is
     *          an `r` element random-access container, such that the `i`-th
     *          element is the length of the `i`-th mode of the tensor.
     *
     *  @throw std::runtime_error if the instance does not have a PIMPL. Strong
     *                            throw guarantee.
     */
    const_extents_reference extents() const;

    const_inner_extents_reference inner_extents() const;
    const_tiling_reference tiling() const;
    size_type field_rank() const;

    bool is_hard_zero(const index_type& i) const { return is_hard_zero_(i); }
    bool is_hard_zero(const index_type& lo, const index_type& hi) const {
        return is_hard_zero_(lo, hi);
    }

    pointer_type slice(const index_type& lo, const index_type& hi) const {
        return slice_(lo, hi);
    };

    /** @brief Non-polymorphic equality comparison for shapes with the same
     *         field.
     *
     *  This function will determine if the Shape part of the current instance
     *  is equal to the Shape part of @p rhs. In other words, state in derived
     *  classes, for either this instance or @p rhs, is not considered. Two
     *  Shapes are considered equal if they have the same field, both contain a
     *  PIMPL (or both don't contain a PIMPL), and if they do contain a PIMPL
     *  the PIMPL must have the same extents.
     *
     *  @param[in] rhs The instance we are comparing to.
     *
     *  @return True if the Shape part of this instance compares equal to the
     *          Shape part of @p rhs, false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const Shape& rhs) const noexcept;

    /** @brief Non-polymorphic equality comparison for Shapes with different
     *         fields.
     *
     *  This function always returns false since Shapes with different field
     *  types can not be equal.
     *
     *  @tparam RHSType The field type of rhs. Assumed to be either
     *                  field::Scalar or field::Tensor.
     *  @tparam <anonymous> Type used to enable this function, via SFINAE, when
     *                      @p RHSType is different than FieldType.
     *
     *  @return False. This function is only considered when the field types are
     *          different.
     *
     *  @throw None No throw guarantee.
     */
    template<typename RHSType, typename = enable_if_not_my_field_t<RHSType>>
    bool operator==(const Shape<RHSType>& rhs) const noexcept {
        return false;
    }

    /** @brief Polymorphic equality comparison.
     *
     *
     */
    bool is_equal(const Shape& rhs) const noexcept;

protected:
    /** @brief Creates the Shape with the specified PIMPL
     *
     *  This ctor is intended for use by derived classes. In the derived class
     *  ctors, they will initialize a PIMPL and then the base will store it via
     *  this ctor.
     *
     *  @param[in] pimpl The PIMPL the base should store. The PIMPL may be
     *                   polymorphic.
     *
     *  @throw None No throw guarantee.
     */
    Shape(pimpl_pointer pimpl) noexcept;

    /** @brief Returns the PIMPL in a read-only state.
     *
     *  This function will assert that the instance has a PIMPL (throwing if it
     *  does not) and then return the PIMPL if it does.
     *
     *  @return A read-only reference to the PIMPL.
     *
     *  @throw std::runtime_error if the current instance is PIMPL-less. Strong
     *                            throw guarantee.
     */
    const pimpl_type& pimpl_() const;

    /** @brief Raises an exception if the Shape instance does not contain a
     *         PIMPL.
     *
     *  This function is code factorization for determining if the instance has
     *  a PIMPL, or not. As long as the Shape was not default constructed, or
     *  moved from, it should have a PIMPL.
     *
     *  @throw std::runtime_error if the current instance is PIMPL-less. Strong
     *                            throw guarantee.
     */
    void assert_pimpl_() const;

    /** @brief Determines if the instance has a PIMPL or not.
     *
     *  @return True if the instance has a PIMPL and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool has_pimpl_() const noexcept;

private:
    /// Derived class should override to implement is_hard_zero
    virtual bool is_hard_zero_(const index_type&) const;
    virtual bool is_hard_zero_(const index_type&, const index_type&) const;

    virtual pointer_type slice_(const index_type&, const index_type&) const;

    /// Derived class should override to implement polymorphic deep-copy
    virtual pointer_type clone_() const;

    /// Derived class should override to implement is_equal
    virtual bool is_equal_(const Shape<FieldType>& rhs) const noexcept;

    /// Object actually holding the state of the instance
    pimpl_pointer m_pimpl_;
};

/** @brief Determines if two Shape instances are different.
 *
 *  @relates Shape
 *
 *  This function simply negates a call to Shape::operator==. Hence it returns
 *  false when the Shape instances compare equal (non-polymorphically) and true
 *  otherwise. See Shape::operator== for the definition of non-polymorphic
 *  equality.
 *
 *  @tparam LHSType The type of the field associated with @p lhs. Assumed to be
 *                  either field::Scalar or field::Tensor.
 *  @tparam RHSType The type of the field associated with @p rhs. Assumed to be
 *                  either field::Scalar or field::Tensor.
 *
 *  @param[in] lhs The instance on the left side of the inequality operator.
 *  @param[in] rhs The instance on the right side of the inequality operator.
 *
 *  @return False if @p lhs compares non-polymorphically equal to @p rhs and
 *          true otherwise.
 *
 *  @throw None No throw guarantee.
 */
template<typename LHSType, typename RHSType>
bool operator!=(const Shape<LHSType>& lhs, const Shape<RHSType>& rhs) {
    return !(lhs == rhs);
}

extern template class Shape<field::Scalar>;
extern template class Shape<field::Tensor>;

} // namespace tensorwrapper::tensor
