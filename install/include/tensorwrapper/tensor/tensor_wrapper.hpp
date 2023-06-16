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
#include <tensorwrapper/tensor/allocator/allocator.hpp>
#include <tensorwrapper/tensor/buffer/buffer.hpp>
#include <tensorwrapper/tensor/expression/labeled_view.hpp>
#include <tensorwrapper/tensor/fields.hpp>
#include <tensorwrapper/tensor/type_traits/nd_initializer_list_traits.hpp>
#include <tiledarray.h>

namespace tensorwrapper::tensor {
namespace detail_ {

template<typename FieldType>
class TensorWrapperPIMPL;

} // namespace detail_

/** @brief Fundamental type for wrapping tensors.
 *
 *  The TensorWrapper class is designed to type-erase many of the details
 *  regarding how the underlying tensor classes actually work.
 *
 *  @tparam FieldType the type of the scalar field used for the tensor's
 *          elements.
 */
template<typename FieldType>
class TensorWrapper {
private:
    /// Type of this instance
    using my_type = TensorWrapper<FieldType>;

    /// Type of the pimpl
    using pimpl_type = detail_::TensorWrapperPIMPL<FieldType>;

    /// Type of a modifiable reference to the PIMPL
    using pimpl_reference = pimpl_type&;

    /// Read-only reference to the PIMPL
    using const_pimpl_reference = const pimpl_type&;

    /** @brief Helper value which determines if @p T  is the same as this
     *         tensor's field.
     *
     *  @tparam T The type we are comparing to this tensor's field type. Assumed
     *            to be a field, but will work with any type @p T.
     *
     */
    template<typename T>
    static constexpr bool same_field_v = std::is_same_v<FieldType, T>;

    /** @brief Type which is used to enable a function via SFINAE if @p T is
     *         a different field than the field associated with this tensor.
     *
     *  If @p T is different than this tensor's field type this typedef will be
     *  an alias of `void`, otherwise the typedef will fail to compile and the
     *  compiler will ignore functions which use this typedef as part of their
     *  API.
     *
     *  @tparam T The type to compare to this tensor's field type.
     */
    template<typename T>
    using eif_diff_fields = std::enable_if_t<!same_field_v<T>>;

    /// True if this class wraps a ToT and false otherwise
    static constexpr bool is_tot = std::is_same_v<FieldType, field::Tensor>;

    template<typename T>
    static constexpr bool is_t_to_tot_v =
      std::is_same_v<T, field::Scalar>&& is_tot;

    template<typename T>
    using eif_t_to_tot_conversion = std::enable_if_t<is_t_to_tot_v<T>>;

    using element_type =
      std::conditional_t<!is_tot, double, TensorWrapper<field::Scalar>>;

public:
    /// Type of a pointer to the pimpl
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    /// Type of the field for the wrapped tensor
    using field_type = FieldType;

    /// Type resulting from annotating this tensor
    using labeled_tensor_type = expression::LabeledView<field_type>;

    using const_labeled_tensor_type = const labeled_tensor_type;

    /// String-like type used to annotate a tensor.
    using annotation_type = typename labeled_tensor_type::label_type;

    /// Type used for indexing and offsets
    using size_type = std::size_t;

    /// Type of an allocator
    using allocator_type = allocator::Allocator<FieldType>;

    using buffer_type = buffer::Buffer<FieldType>;

    using buffer_pointer = std::unique_ptr<buffer_type>;

    using buffer_reference = buffer_type&;

    using const_buffer_reference = const buffer_type&;

    using tile_populator_type = typename allocator_type::tile_populator_type;
    using element_populator_type =
      typename allocator_type::element_populator_type;

    /// Type of a pointer to an allocator
    using allocator_pointer = std::unique_ptr<allocator_type>;

    /// Type of a read-only reference to a type-erased allocator
    using const_allocator_reference = const allocator_type&;

    /// Type used for describing the shape of the tensor
    using shape_type = Shape<FieldType>;

    using index_type = typename shape_type::index_type;

    /// Type of a pointer to a shape
    using shape_pointer = std::unique_ptr<shape_type>;

    /// Type of a pointer to a sparse shape
    using sparse_pointer = std::unique_ptr<SparseShape<FieldType>>;

    /// Type of a read-only reference to a shape
    using const_shape_reference = const shape_type&;

    /// Type used for returning the extents
    using extents_type = typename shape_type::extents_type;

    /// Type used for the rank
    using rank_type = unsigned int;

    /// Type used for initializer_lists of sizes
    using il_type = std::initializer_list<size_type>;

    /// Type used for scalar values in the tensor
    using scalar_value_type = double;

    /** @brief Default CTor
     *
     *  The TensorWrapper resulting from this ctor wraps no tensor, and has no
     *  allocator. At the moment the only way to make the resulting tensor into
     *  a useful tensor is by moving or assigning to it.
     *
     *  @throw ??? Throws if the default ctor of any type in variant_type throws
     *             same throw guarantee.
     */
    TensorWrapper();

    explicit TensorWrapper(pimpl_pointer p) noexcept;

    TensorWrapper(const tile_populator_type& fxn, shape_pointer shape,
                  allocator_pointer alloc);
    TensorWrapper(const element_populator_type& fxn, shape_pointer shape,
                  allocator_pointer alloc);

    /** @brief Creates a TensorWrapper which will use the provided allocator to
     *         create its state.
     *
     *  This ctor allows you to set the allocator a TensorWrapper will use. The
     *  resulting TensorWrapper will have not contain an allocated tensor. At
     *  the moment the only way to have the resulting TensorWrapper wrap a
     *  useful tensor is to assign or move to it.
     *
     *  @param[in] p The allocator, passed as a pointer to the base, the tensor
     *               should use.
     *
     *  @throw ??? Throws if the default ctor of any type in the variant_type
     *             throws. Same throw guarantee.
     */
    explicit TensorWrapper(allocator_pointer p);

    /** @brief Creates a TensorWrapper which wraps a tensor of the specified
     *         shape.
     *
     *  This ctor can be used to create a new tensor of the specified size. The
     *  underlying tensor is not yet initialized, and must be initialized before
     *  it is used. Attempting to use the tensor without initializing it, is
     *  likely to cause deadlock.
     *
     *  @param[in] shape An r-element container such that the i-th element is
     *                   the extent of the i-th mode of the resulting rank r
     *                   tensor (r and i are zero based).
     *
     *  @param[in] p A pointer to the allocator the tensor wrapper should use.
     *               By default the result of `default_allocator<variant_type>`
     *               is used.
     *
     *  @throw ??? Throws if allocating the underlying tensor throws. Same throw
     *             guarantee.
     */
    explicit TensorWrapper(
      shape_pointer shape,
      allocator_pointer p = default_allocator<field_type>());

    TensorWrapper(buffer_type buffer, shape_pointer shape,
                  allocator_pointer alloc);

    /** @brief Creates a TensorWrapper which wraps a tensor whose values are
     *  defined by an initializer list.
     *
     *  These ctors can be used to create a new tensor whose contents are
     *  defined by the initializer list input. The rank of the list determines
     *  the rank of the wrapped tensor
     *
     *  @param[in] il The initializer list used to create the underlying tensor.
     *
     *  @throw ??? Throws if allocating the underlying tensor throws. Same throw
     *             guarantee.
     */
    TensorWrapper(n_d_initializer_list_t<element_type, 1> il);
    TensorWrapper(n_d_initializer_list_t<element_type, 2> il);
    TensorWrapper(n_d_initializer_list_t<element_type, 3> il);
    TensorWrapper(n_d_initializer_list_t<element_type, 4> il);

    /** @brief Makes a copy of another TensorWrapper
     *
     *  The exact semantics of the copy ctor are defined by the
     * copy semantics of the wrapped tensor. The allocator
     * however; will be deep-copied.
     *
     *  @param[in] other The instance we are copying.
     *
     */
    TensorWrapper(const TensorWrapper& other);

    /** @brief Takes ownership of another TensorWrapper
     * instance.
     *
     *  The exact semantics of the move ctor are defined by the
     * move semantics of the wrapped tensor. Ownership of the
     * allocator in @p other will be transferred to this
     * instance.
     *
     *  @param[in,out] other The TensorWrapper we are
     * transferring the state from. After this operation the
     * state of @p other will in a valid, but otherwise
     * undefined state.
     */
    TensorWrapper(TensorWrapper&& other);

    /** @brief Assigns a copy of another TensorWrapper to this
     * instance.
     *
     *  This operation will overwrite the current
     * TensorWrapper's state with a copy of @p rhs 's state.
     * The exact semantics of the copy will depend on copy
     * assignment operator of the wrapped tensor in @p rhs. The
     * allocator in @p rhs will be deep copied.
     *
     *  @param[in] rhs The TensorWrapper instance we are
     * copying the state from.
     *
     *  @return The current TensorWrapper instance after
     * overwriting its state with a copy of @p rhs's state.
     */
    TensorWrapper& operator=(const TensorWrapper& rhs);

    /** @brief Takes ownership of another TensorWrapper
     * instance's state.
     *
     *  This operation will overwrite the current TensorWrapper
     * instance's state with the state of @p rhs. The exact
     * semantics of the move assignment will depend on the move
     * assignment semantics of the wrapped tensor. The
     *  ownership of the allocator in @p rhs will be
     * transferred to this instance.
     *
     *  @param[in,out] rhs The TensorWrapper instance we are
     * transferring the state from. After this operation @p rhs
     * will be in a valid, but otherwise undefined state.
     *
     * @return The current TensorWrapper instance after
     * overwriting its state with @p rhs's state.
     */
    TensorWrapper& operator=(TensorWrapper&& rhs);

    /// Default nothrow dtor
    ~TensorWrapper() noexcept;

    void swap(TensorWrapper& other) noexcept;

    /** @brief Returns the allocator in a read-only state.
     *
     *  This function can be used to retrieve the allocator
     * that the TensorWrapper was initialized with. If the
     * instance does not have an allocator an error will be
     * thrown.
     *
     *  @return The allocator used for the tensor.
     *
     *  @throw std::runtime_error if the instance does not
     */
    const_allocator_reference allocator() const;

    /** @brief Changes the allocator, reallocating the tensor
     * (in place) if needed.
     *
     *  Under most circumstances users of the TensorWrapper
     * class shouldn't have to call this function. This
     * function is mainly used under the hood when a
     * reallocation needs to happen to make tensors compatible.
     * It has public scope because it's useful for unit testing
     * the effect different allocation strategies have. This
     * operation is in place, and may mutate the underlying
     * data (e.g., smaller tiles may result in small elements
     *  being set to hard zero) in addition to moving the data
     * around in memory.
     *
     *  @param[in] p The new allocator for the tensor.
     */
    void reallocate(allocator_pointer p);

    /** @brief Annotates the modes of the wrapped index with
     * the provided labels.
     *
     *  The domain-specific language of tensor operations is
     * written in terms of Einstein notation. This requires us
     * to assign dummy indices to each mode of the tensor. This
     * function pairs @p annotation with the wrapped tensor to
     * provide a labeled tensor. The resulting labeled tensor
     * can be used in tensor expressions.
     *
     *  @param[in] annotation The dummy indices we are
     * annotating the underlying tensor with.
     *
     *  @return A labeled read/write tensor.
     */
    labeled_tensor_type operator()(const annotation_type& annotation);

    /** @brief Annotates the modes of the wrapped index with
     * the provided labels.
     *
     *  The domain-specific language of tensor operations is
     * written in terms of Einstein notation. This requires us
     * to assign dummy indices to each mode of the tensor. This
     * function pairs @p annotation with the wrapped tensor to
     * provide a labeled tensor. The resulting labeled tensor
     * can be used in tensor expressions.
     *
     *  @param[in] annotation The dummy indices we are
     * annotating the underlying tensor with.
     *
     *  @return A labeled read-only tensor.
     */
    const_labeled_tensor_type operator()(
      const annotation_type& annotation) const;

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
    annotation_type make_annotation(const annotation_type& letter = "i") const;

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

    /** @brief Returns a read-only reference to the tensor's shape.
     *
     *  @return A read-only reference to the base class of the shape held by
     *          the tensor.
     */
    const_shape_reference shape() const;

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
     *  @param[in] lo The index of the first element to include
     * in the slice.
     *  @param[in] hi The index of the first element, which is
     * just outside the slice.
     * @param[in] p The allocator to use for the resulting slice. Default value
     *              is the allocator returned by default_allocator().
     *
     *  @return The requested slice.
     */
    TensorWrapper slice(
      const il_type& lo, const il_type& hi,
      allocator_pointer p = default_allocator<field_type>()) const;

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
    TensorWrapper reshape(shape_pointer shape) const;

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

    /** @brief Determines if two TensorWrappers wrap identical
     * tensors.
     *
     *  This comparison determines if the two wrapped tensors are identical
     *  elementwise. This overload is used when the TensorWrappers are
     *  associated with the same field.
     *
     *  @tparam RHSType the type of the variant used by @p rhs.
     *
     *  @param[in] rhs The wrapped tensor we are comparing to.
     *
     *  @return True if the wrapped tensor compares equal to @p rhs and false
     *          otherwise.
     */
    bool operator==(const TensorWrapper& rhs) const;

    /** @brief Determines if two TensorWrappers wrap identical tensors.
     *
     *  This overload is only enabled when the other TensorWrapper is over a
     *  different field. This overloaded is hard-coded to false, since if the
     *  tensors have different fields they can't be the same.
     *
     *  @tparam RHSField The type of the field associated with @p rhs.
     *                   Assumed to be one of the fields recognized by the
     *                   TensorWrapepr subcomponent.
     *  @tparam <anonymous> Type used to selectively enable this overload via
     *                      SFINAE when @p RHSField is not the same field as
     *                      this tensor.
     *
     */
    template<typename RHSField, typename = eif_diff_fields<RHSField>>
    bool operator==(const TensorWrapper<RHSField>& rhs) const {
        return false;
    }

    buffer_reference buffer();
    const_buffer_reference buffer() const;

    pimpl_reference pimpl();
    inline const_pimpl_reference pimpl() const { return pimpl_(); }

protected:
    /// Allows tensors over other fields to interact with this tensor
    template<typename OtherField>
    friend class TensorWrapper;

    void update_shape_();

    /** @brief Returns the wrapped variant.
     *
     *  This function is used by LabeledViewWrapper to get
     * the variant. In general users of the TensorWrapper class
     * shouldn't be working with the variant, which is why the
     * function is not part of the public API.
     *
     *  @return A modifiable reference to the wrapped variant.
     *
     *  @throw None No throw guarantee.
     */
    pimpl_reference pimpl_();

    /** @brief Returns the wrapped variant.
     *
     *  This function is used by LabeledViewWrapper to get
     * the variant. In general users of the TensorWrapper class
     * shouldn't be working with the variant, which is why the
     * function is not part of the public API.
     *
     *  @return A read-only reference to the wrapped variant.
     *
     *  @throw None No throw guarantee.
     */
    const_pimpl_reference pimpl_() const;

private:
    /// The object actually holding the Tensor's state
    pimpl_pointer m_pimpl_;
};

/** @brief Prints the wrapped tensor to the provided output stream.
 *
 *  @relates TensorWrapper
 *
 *  This function is a convenience function for calling TensorWrapper::print so
 *  that the wrapped tensor can be printed in the usual C++ manner.
 *
 *  @param[in,out] os The stream we adding the string representation of the
 *                    tensor to. After the call @p os will contain the
 *                    string representation of the wrapped tensor instance.
 *  @param[in] t The tensor to print to @p os.
 *
 *  @return This function returns @p os to facilitate operator chaining.
 */
template<typename VType>
std::ostream& operator<<(std::ostream& os, const TensorWrapper<VType>& t) {
    return t.print(os);
}

/** @brief Determiens if the wrapped tensor instances are different.
 *
 *  @relates TensorWrapper
 *
 *  @tparam LHSType The type of the variant in the left tensor wrapper.
 *  @tparam RHSType The type of the variant in the right tensor wrapper.
 *
 *  @param[in] lhs The wrapped tensor on the left of the not equal operator.
 *  @param[in] rhs The wrapped tensor on the right of the not equal operator.
 *
 *  @return False if @p lhs is equal to @p rhs and true otherwise.
 */
template<typename LHSType, typename RHSType>
bool operator!=(const TensorWrapper<LHSType>& lhs,
                const TensorWrapper<RHSType>& rhs) {
    return !(lhs == rhs);
}

/// A tensor whose associated field is filled with scalars
using ScalarTensorWrapper = TensorWrapper<field::Scalar>;

/// A tensor whose associated field is other tensors
using TensorOfTensorsWrapper = TensorWrapper<field::Tensor>;

//------------------------------------------------------------------------------
//               Forward Declaration of Explicit Instantiations
//------------------------------------------------------------------------------

extern template class TensorWrapper<field::Scalar>;
extern template class TensorWrapper<field::Tensor>;

} // namespace tensorwrapper::tensor
