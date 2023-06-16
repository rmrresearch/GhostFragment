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
#include "tensorwrapper/tensor/tensor_wrapper.hpp"

namespace tensorwrapper::tensor::detail_ {

/** @brief Holds the state of a TensorWrapper.
 *
 *  The TensorWrapperPIMPL class is designed to encapsulate as much of the
 *  TensorWrapper state as possible. Full encapsulation is not possible unless
 *  we want to supress the expression templating of the wrapped library. For
 *  TiledArray this "leakage" occurs through the annotate member (and also
 *  somewhat through the ctor).
 *
 *  @tparam FieldType What sort of elements are in the tensor? Assumed to be
 *                    either field::Scalar or field::Tensor.
 */
template<typename FieldType>
class TensorWrapperPIMPL {
private:
    /// The type of this PIMPL
    using my_type = TensorWrapperPIMPL<FieldType>;

    /// Type of the TensorWrapper this is a PIMPL for
    using parent_type = TensorWrapper<FieldType>;

public:
    /// Type used to annotate the tensor (i.e. type of the dummy indices)
    using annotation_type = typename parent_type::annotation_type;

    /// Type of the field the tensor is over
    using field_type = FieldType;

    /// Type which holds type-erased tensor instance
    using buffer_type            = typename parent_type::buffer_type;
    using buffer_pointer         = typename parent_type::buffer_pointer;
    using const_buffer_reference = typename parent_type::const_buffer_reference;
    using buffer_reference       = typename parent_type::buffer_reference;

    /// Type of a read-only reference to an allocator
    using const_allocator_reference =
      typename parent_type::const_allocator_reference;

    /// Type of a type-erased allocator
    using allocator_pointer = typename parent_type::allocator_pointer;

    /// Base type of the Shape
    using shape_type = typename parent_type::shape_type;

    /// Type of a pointer to the shape's base class
    using shape_pointer = typename parent_type::shape_pointer;

    /// Type of a read-only reference to a shape
    using const_shape_reference = typename parent_type::const_shape_reference;

    /// Type used to describe the shape (will be removed in forthcoming PR)
    using extents_type = typename parent_type::extents_type;

    /// Type of a pointer to a PIMPL
    using pimpl_pointer = typename parent_type::pimpl_pointer;

    /// Type used to return ranks
    using rank_type = typename parent_type::rank_type;

    /// Type used for indexing and offsets
    using size_type = typename parent_type::size_type;

    /// Type used for indexing
    using index_type = typename parent_type::index_type;

    /// Type used for initializer lists of sizes
    using il_type = typename parent_type::il_type;

    /// Type used for scalar values in the tensor
    using scalar_value_type = typename parent_type::scalar_value_type;

    /** @brief Creates a new PIMPL which wraps the provided tensor and allocator
     *
     *  @param[in] b A buffer which wraps the tensor
     *  @param[in] s The shape of the tensor
     *  @param[in] p The allocator to use for tiling, distribution, etc.
     */
    TensorWrapperPIMPL(buffer_pointer b, shape_pointer s, allocator_pointer p);

    /** @brief Makes a deep-copy of the current PIMPL
     *
     *  Strictly speaking this calls the clone member of the allocator and the
     *  copy ctor of the variant. Whether that's a deep copy or shallow copy is
     *  defined by those functions.
     *
     *  @return A new PIMPL which is a "deep-copy" of this
     */
    pimpl_pointer clone() const;

    /** @brief Returns the allocator in a read-only state.
     *
     *  This function can be used to retrieve the allocator
     * that the TensorWrapper was initialized with. If the
     * instance does not have an allocator an error will be
     * thrown.
     *
     *  @return The allocator used for the tensor.
     *
     *  @throw std::runtime_error if the instance does not have one.
     */
    const_allocator_reference allocator() const;

    /** @brief Returns the shape in a read-only state.
     *
     *  This function is used to retrieve the shape of the tensor.
     *
     *  @return The shape of the tensor.
     *
     *  @throw std::runtime_error if the instance does not have one.
     */
    const_shape_reference shape() const;

    const_buffer_reference buffer() const;
    buffer_reference buffer();

    /** @brief Returns the shape of the tensor.
     *
     *  The shape of a rank @f$r@f$ tensor, also known as its
     * extents, is a
     *  @f$r@f$ element array such that the @f$i@f$-th element
     * is the length of the @f$i@f-th mode.
     *
     *  @return An array-like object containing the shape of
     * the tensor.
     */
    extents_type extents() const;

    /** @brief Creates an annotation suitable for the wrapped
     * tensor.
     *
     *  For a rank @f$r@f$ tensor this function will create a
     * string containing
     *  @f$r@f$ indices. The @f$i@f$-th 0-based mode's index
     * will be the result of concatentating @p letter with
     * @f$i@f$. For example, using the default value of @p
     * letter this function will generate the annotation
     *  `"i0,i1,i2"` for a rank 3 tensor. If the wrapped tensor
     * is a tensor-of-tensors, this function will insert a
     * semicolon where appropriate.
     *
     *  This function is meant to be used to perform generic
     * operations on the tensors by string replacement. For
     * example:
     *
     *  @code
     *  auto idx0 = t0.make_annotation();
     *  auto idx1 = t1.make_annotation("j");
     *  // To contract mode 1 of t0 with mode 3 of t1 we
     * replace "j3" with "i1" auto new_idx1 =
     * std::regex_replace(idx1, std::regex("j3"), "i1");
     *  // In practice we would work out the resulting
     * annotation too auto mult_op = t0(idx0) * t1(idx1);
     *  @endcode
     *
     *  @param[in] letter The label part of the index. This is
     * what will be concatenated with the mode number to get
     * the final annotation for each mode. Default is `"i"`.
     *
     *  @return A string containing an annotation which is
     * appropriate for the tensor.
     */
    annotation_type make_annotation(const annotation_type& letter) const;

    /** @brief Returns the number of modes in the wrapped
     * tensor.
     *
     *  For a normal, non-hierarchical tensor the rank is
     * simply the number of modes in the tensor. For a
     * hierarchical tensor the rank is still the number of
     * modes in the tensor, but it should be noted that this is
     * the sum of the number of independent and dependent
     * modes.
     *
     *  @return The number of modes in the tensor.
     */
    rank_type rank() const;

    /** @brief Changes the allocator used by the tensor.
     *
     *  This function will change the allocator used by the underlying tensor
     *  to the provided allocator. If the wrapped tensor is not consistent with
     *  the provided allocator it will be reallocated.
     *
     *  @param[in] p The allocator to switch to.
     */
    void reallocate(allocator_pointer p);

    /** @brief Used to view the tensor as if it has a different
     * shape.
     *
     *  This function is mainly used to flatten and un-flatten
     * a tensor. Under the hood this function remaps indices
     * by:
     *  - mapping the original coordinate index to its ordinal
     * index
     *  - mapping the ordinal index to the new coordinate index
     *  The data is then redistributed, if needed.
     *
     *  @param[in] shape The shape of the resulting tensor. The
     * volume of
     *                   @p shape must match the result of
     * `size()`.
     *
     *  @return A copy of the current tensor with the new
     * shape.
     *
     *  @throw std::runtime_error if @p shape does not have the
     * same volume as the wrapped tensor. Strong throw
     * guarantee.
     */
    void reshape(shape_pointer shape);

    /** @brief Returns the norm of the wrapped tensor.
     *
     *  @return The value of the tensor's norm.
     */
    scalar_value_type norm() const;

    /** @brief Returns the sum of the wrapped tensor.
     *
     *  @return The value of the sum of the tensor's elements.
     */
    scalar_value_type sum() const;

    /** @brief Returns the trace of the wrapped tensor.
     *
     *  @return The value of the tensor's trace.
     *
     *  @throw std::runtime_error if the tensor is a tensor of tensors or if the
     *  tensor is not a square matrix.
     */
    scalar_value_type trace() const;

    /** @brief Returns the number of elements in this tensor.
     *
     *  This function returns the total number of elements in
     * the tensor, which is sometimes also known as the volume.
     * The volume is computed as the product of the extents. An
     * empty tensor has a volume of zero.
     *
     *  @return The number of elements in the wrapped tensor.
     */
    size_type size() const;

    /** @brief Returns a slice of the wrapped tensor.
     *
     *  This function can be used to extract a slice of the
     * underlying tensor. The slice is assumed to contiguous
     * along each mode, and have the same rank as the
     * underlying tensor. For mode `i` the slice will contain
     * the elements in the range [`lo[i]`, `hi[i]`).
     *
     *  @param[in] lo The index of the first element to include in the slice.
     *  @param[in] hi The index of the first element, which is just outside the
     *                slice.
     * @param[in] p The allocator to use in the resulting slice.
     *
     *  @return The requested slice.
     */
    pimpl_pointer slice(const il_type& lo, const il_type& hi,
                        allocator_pointer p) const;

    /** @brief Adds a string representation of the wrapped
     * tensor to the provided stream.
     *
     *  @param[in,out] os The stream we adding the string
     * representation of the tensor to. After the call @p os
     * will contain the string representation of the wrapped
     * tensor instance.
     *
     *  @return This function returns @p os to facilitate
     * operator chaining.
     */
    std::ostream& print(std::ostream& os) const;

    /** @brief Determines if two TensorWrapperPIMPLs wrap identical
     *         tensors.
     *
     *  This comparison determines if the two wrapped tensors are identical
     *  elementwise.
     *
     *  @tparam RHSType the type of the variant used by @p rhs.
     *
     *  @param[in] rhs The wrapped tensor we are comparing to.
     *
     *  @return True if the wrapped tensor compares equal to @p rhs and false
     *          otherwise.
     */
    bool operator==(const TensorWrapperPIMPL& rhs) const;

    void update_shape();

private:
    /// Guts of reshape, but doesn't set internal shape to other
    void reshape_(const shape_type& other);

    /// Guts of reallocate, but doesn't set internal allocator to other
    void reallocate_(const_allocator_reference other);

    /// Routine used by reshape_ when the rank has changed
    void shuffle_(const shape_type& other);

    /** @brief Returns the inner rank of the tensor.
     *
     *  For a normal non-hierarchical tensor there are zero
     * inner modes. For a ToT the modes to the right of the
     * semi-colon are inner modes.
     *
     *  @return The number of inner modes.
     */
    rank_type inner_rank_() const;

    /** @brief Returns the outer rank of the tensor.
     *
     *  For a normal non-hierarchical tensor all modes are
     * "outer" modes. For a ToT the modes to the left of the
     * semi-colon are outer modes.
     *
     *  @return The number of outer modes.
     *
     *  @throw No throw guarantee.
     */
    rank_type outer_rank_() const noexcept;

    /// The actual tensor
    buffer_pointer m_buffer_;

    /// The allocator for the tensor, stored in a type-erased state
    allocator_pointer m_allocator_;

    /// The shape of the tensor, stored as pointer to the base class
    shape_pointer m_shape_;
};

extern template class TensorWrapperPIMPL<field::Scalar>;
extern template class TensorWrapperPIMPL<field::Tensor>;

} // namespace tensorwrapper::tensor::detail_
