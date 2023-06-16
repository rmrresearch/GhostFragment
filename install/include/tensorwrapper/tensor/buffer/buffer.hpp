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
#include "tensorwrapper/tensor/fields.hpp"
#include "tensorwrapper/tensor/shapes/shape.hpp"
#include <memory>
#include <string>
#include <type_traits>

namespace tensorwrapper::tensor::buffer {
namespace detail_ {
template<typename FieldType>
class BufferPIMPL;

}

/** @brief Wraps a tensor backend.
 *
 *  The Buffer class provides a uniform API for accessing the underlying tensor
 *  library, depending only on whether the underlying tensor has scalar elements
 *  or tensor elements.
 *
 *  @tparam FieldType The type of the field the tensor is over. Expected to be
 *                    either field::Scalar or field::Tensor.
 */
template<typename FieldType>
class Buffer {
private:
    /// Type of the PIMPL
    using pimpl_type = detail_::BufferPIMPL<FieldType>;

    /// Trait for determining if the fields are the same
    template<typename T>
    static constexpr bool same_field_v = std::is_same_v<FieldType, T>;

    /// Enables a function, via SFINAE, if @p T is different than FieldType
    template<typename T, typename U = void>
    using enable_if_diff_field_t = std::enable_if_t<!same_field_v<T>, U>;

    /// The type of this instance
    using my_type = Buffer<FieldType>;

public:
    /// Type used for indices in einstein/index-based operations
    using annotation_type = std::string;

    /// Type of a read-only reference to an annotation
    using const_annotation_reference = const std::string&;

    /// Type of a pointer to the PIMPL
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    /// Type used to model the shape
    using shape_type = Shape<FieldType>;

    /// Type used for returning the extents
    using extents_type = typename shape_type::extents_type;

    /// Type used for returning inner extents
    using inner_extents_type = typename shape_type::inner_extents_type;

    /// Type used for scalar values in the tensor
    using scalar_value_type = double;

    /** @brief Defaulted default ctor.
     *
     *  This ctor creates an uninitialized Buffer instance. The resulting
     *  instance has no PIMPL and can only be used after assigning an
     *  initialized Buffer instance to it.
     *
     *  @throw None No throw guarantee.
     */
    Buffer() noexcept;

    /** @brief PIMPL Ctor.
     *
     *  Generally speaking Buffer instances are created by Allocator instances.
     *  The allocator instances are implemented in the source and have access to
     *  the backend specific PIMPLs (e.g. TABufferPIMPL). Thus what will usually
     *  happen is that the allocator makes a backend specific PIMPL and then
     *  uses that PIMPL to initialize a Buffer instance via this ctor.
     *
     *  @param[in] pimpl An initialized backend specific PIMPL, passed via the
     *                   base class.
     *
     *  @throw None No throw guarantee.
     */

    Buffer(pimpl_pointer pimpl) noexcept;

    /** @brief Initializes this Buffer with a deep copy of another Buffer.
     *
     *  This ctor will initialize the present Buffer to:
     *
     *  - an uninitiailzed state if `other.is_initialized() == false`, or
     *  - a deep copy of @p other otherwise.
     *
     *  @param[in] other The buffer being copied.
     *
     *  @throw std::bad_alloc if there is a problem initializing the Buffer.
     *                        Strong throw guarantee.
     */
    Buffer(const Buffer& other);

    /** @brief Initializes this Buffer by taking ownership of another Buffer's
     *         state.
     *
     *  This function creates a new Buffer instance by taking ownership of the
     *  PIMPL pointer in @p other.
     *
     *  @param[in,out] other The Buffer providing the state to this instance.
     *                       After this call @p other will be in an
     *                       uninitialized state.
     *
     *  @throw None No throw guarantee.
     */
    Buffer(Buffer&& other) noexcept;

    /** @brief Assigns a deep-copy of @p rhs to this Buffer.
     *
     *  This function will override the state of the current Buffer (and thereby
     *  invalidating all references to the previous state) with: a deep copy of
     *  another instance (if @p rhs is initialized), or an uninitialized PIMPL
     *  if @p rhs is also uninitialized.
     *
     *  @param[in] rhs The Buffer we are assining this instance to.
     *
     *  @return The current Buffer instance, now containing a deep copy of
     *          @p rhs.
     *
     *  @throw std::bad_alloc if there is a problem allocating the new state.
     *                        Strong throw guarantee.
     */
    Buffer& operator=(const Buffer& rhs);

    /** @brief Replaces this instance's state with that of @p rhs.
     *
     *  This function overrides the state of the current Buffer (and thereby
     *  invalidates all references to its previous state) with the state of
     *  @p rhs. The state will be moved, and not copied.
     *
     *  @param[in,out] rhs The Buffer whose state is being taken. After this
     *                 operation @p rhs will be in an uninitialized state.
     *
     *  @return The current Buffer instance, after taking ownership of the state
     *          contained in @p rhs.
     *
     *  @throw None No throw guarantee.
     */
    Buffer& operator=(Buffer&& rhs) noexcept;

    /// Defaulted destructor
    ~Buffer() noexcept;

    pimpl_type* pimpl() noexcept;
    const pimpl_type* pimpl() const noexcept;

    /** @brief Exchanges the state of this Buffer with that of @p other.
     *
     *  This function is used to swap the state of the present Buffer instance
     *  with the state of @p other.
     *
     *  @param[in,out] other The Buffer whose state is being swapped with this
     *                       instance's state. After this call @p other will
     *                       contain the current Buffer's state.
     *
     *  @throw None No throw guarantee.
     */
    void swap(Buffer& other) noexcept;

    /** @brief Used to determine if the Buffer wraps an actual tensor or not.
     *
     *  @return true if the Buffer is currently wrapping a tensor and false
     *          otherwise.
     *
     *  @throw None No throw gurantee.
     */
    bool is_initialized() const noexcept;

    void permute(const_annotation_reference my_idx,
                 const_annotation_reference out_idx, my_type& out) const;

    /** @brief Scales (and optionally permutes) a tensor
     *
     *  This function scales a tensor using einstein notation. This means that
     *  if the indices on the left side of the equation are not in the same
     *  order as those on the right, in addition to scaling the tensor, this
     *  function will permute the modes.
     *
     *  ```.cpp
     *  // To run B("i,j") = 4.2 * A("j,i") run:
     *  A.scale("j,i", "i,j", B, 4.2);
     *  ```
     *
     *  @param[in] my_idx The einstein indices for the current buffer.
     *  @param[in] out_idx The einstein indices for the returned buffer.
     *  @param[in,out] out The buffer to put the result into. If @p out was
     *                     default initialized, this function will default
     *                     initiailze a PIMPL of the same type as the current
     *                     instance before assigning to it.
     *  @param[in] rhs The value to scale this tensor by.
     *
     *  @throws std::runtime_error if the present buffer is not initialized.
     *                             Strong throw guarantee.
     */
    void scale(const_annotation_reference my_idx,
               const_annotation_reference out_idx, my_type& out,
               double rhs) const;

    /** @brief Adds (and optionally permutes) two tensors.
     *
     *  This function adds two tensors together, obtaining a third tensor. The
     *  addition is specified using einstein notation, which also allows one to
     *  permute the modes of the tensor as part of the operation.
     *
     *  ```.cpp
     *  // To run C("i,j") = A("j,i") + B("i,j") run:
     *  A.add("j,i", "i,j", C, "i,j", B);
     *  ```
     *
     *  @param[in] my_idx The einstein indices for the current buffer.
     *  @param[in] out_idx The einstein indices for the output buffer.
     *  @param[in,out] out The buffer to put the answer in. If @p out is default
     *                     initialized, this function will default initialize an
     *                     instance of this buffer's PIMPL before assigning to
     *                     @p out.
     *  @param[in] rhs_idx The einstein indices for the buffer being added to
     *                     this buffer.
     *  @param[in] rhs     The buffer being added to this buffer.
     *
     *  @throw std::runtime_error if the present buffer is not initialized.
     *                            Strong throw guarantee.
     *  @throw std::runtime_error if @p rhs is not initialize. Strong throw
     *                            gurantee.
     */
    void add(const_annotation_reference my_idx,
             const_annotation_reference out_idx, my_type& out,
             const_annotation_reference rhs_idx, const my_type& rhs) const;

    /** @brief Sums another tensor into this tensor
     *
     *  This function will sum the tensor wrapped inside @p rhs into the tensor
     *  wrapped in the present instance. The present instance's state will be
     *  overriden with the result. The operation is expressed using einstein
     *  notation which allows a permutation to optionally happen as part of the
     *  operation.
     *
     *  ```.cpp
     *  // To run A("i,j") += B("j,i") run:
     *  A.inplace_add("i,j", "j,i", B);
     *  ```
     *
     *  @param[in] my_idx The einstein indices for the current buffer.
     *  @param[in] rhs_idx The einstein indices for the buffer being summed into
     *                     the present buffer.
     *  @param[in] rhs The buffer being summed into this buffer.
     *
     *  @throw std::runtime_error if the present buffer is not initialized.
     *                            Strong throw guarantee.
     *  @throw std::runtime_error if @p rhs is not initialized. Strong throw
     *                            guarantee.
     */
    void inplace_add(const_annotation_reference my_idx,
                     const_annotation_reference rhs_idx, const my_type& rhs);

    /** @brief Subtracts (and optionally permutes) two tensors.
     *
     *  This function subtracts two tensors together, obtaining a third tensor.
     *  The subtraction is specified using einstein notation, which also allows
     *  one to permute the modes of the tensor as part of the operation.
     *
     *  ```.cpp
     *  // To run C("i,j") = A("j,i") - B("i,j") run:
     *  A.subtract("j,i", "i,j", C, "i,j", B);
     *  ```
     *
     *  @param[in] my_idx The einstein indices for the current buffer.
     *  @param[in] out_idx The einstein indices for the output buffer.
     *  @param[in,out] out The buffer to put the answer in. If @p out is default
     *                     initialized, this function will default initialize an
     *                     instance of this buffer's PIMPL before assigning to
     *                     @p out.
     *  @param[in] rhs_idx The einstein indices for the buffer being added to
     *                     this buffer.
     *  @param[in] rhs     The buffer being added to this buffer.
     *
     *  @throw std::runtime_error if the present buffer is not initialized.
     *                            Strong throw guarantee.
     *  @throw std::runtime_error if @p rhs is not initialize. Strong throw
     *                            gurantee.
     */
    void subtract(const_annotation_reference my_idx,
                  const_annotation_reference out_idx, my_type& out,
                  const_annotation_reference rhs_idx, const my_type& rhs) const;

    /** @brief Subtracts another tensor from this tensor
     *
     *  This function will subtract the tensor wrapped inside @p rhs from the
     *  tensor wrapped in the present instance. The present instance's state
     *  will be overriden with the result. The operation is expressed using
     *  einstein notation which allows a permutation to optionally happen as
     *  part of the operation.
     *
     *  ```.cpp
     *  // To run A("i,j") -= B("j,i") run:
     *  A.inplace_subtract("i,j", "j,i", B);
     *  ```
     *
     *  @param[in] my_idx The einstein indices for the current buffer.
     *  @param[in] rhs_idx The einstein indices for the buffer being subtracted
     *                     from the present buffer.
     *  @param[in] rhs The buffer being subtracted from this buffer.
     *
     *  @throw std::runtime_error if the present buffer is not initialized.
     *                            Strong throw guarantee.
     *  @throw std::runtime_error if @p rhs is not initialized. Strong throw
     *                            guarantee.
     */
    void inplace_subtract(const_annotation_reference my_idx,
                          const_annotation_reference rhs_idx,
                          const my_type& rhs);

    /** @brief Multiplies (and optionally permutes) two tensors.
     *
     *  This function multiplies two tensors together, obtaining a third tensor.
     *  The multiplication is specified using einstein notation, which also
     *  allows one to perform contractions and/or permute the modes of the
     *  tensor as part of the operation.
     *
     *  ```.cpp
     *  // To run C("i,j") = A("j,i") * B("i,j") run:
     *  A.times("j,i", "i,j", C, "i,j", B);
     *  ```
     *
     *  @param[in] my_idx The einstein indices for the current buffer.
     *  @param[in] out_idx The einstein indices for the output buffer.
     *  @param[in,out] out The buffer to put the answer in. If @p out is default
     *                     initialized, this function will default initialize an
     *                     instance of this buffer's PIMPL before assigning to
     *                     @p out.
     *  @param[in] rhs_idx The einstein indices for the buffer being added to
     *                     this buffer.
     *  @param[in] rhs     The buffer being added to this buffer.
     *
     *  @throw std::runtime_error if the present buffer is not initialized.
     *                            Strong throw guarantee.
     *  @throw std::runtime_error if @p rhs is not initialize. Strong throw
     *                            gurantee.
     */
    void times(const_annotation_reference my_idx,
               const_annotation_reference out_idx, my_type& out,
               const_annotation_reference rhs_idx, const my_type& rhs) const;

    /** @brief Computes the dot product of the current buffer with @p rhs.
     *
     *  @throw std::runtime_error if the present buffer is not initialized.
     *                            Strong throw guarantee.
     *  @throw std::runtime_error if @p rhs is not initialized. Strong throw
     *                            guarantee.
     */
    scalar_value_type dot(const_annotation_reference my_idx,
                          const_annotation_reference rhs_idx,
                          const my_type& rhs) const;

    /** @brief Computes the norm of the underlying tensor
     *
     *  NRM = sqrt(T(:) * T(:))
     *
     *  @returns norm of underlying tensor
     *  @throw std::runtime_error if @p rhs is not initialize. Strong throw
     *                            gurantee.
     */
    scalar_value_type norm() const;

    /** @brief Computes the element sum of the underlying tensor
     *
     *  Recurses into ToT structure if needed
     *
     *  SUM = \sum_{ijk...} A(i,j,k,...)
     *
     *  @returns element sum of underlying tensor
     *  @throw std::runtime_error if @p rhs is not initialize. Strong throw
     *                            gurantee.
     */
    scalar_value_type sum() const;

    /** @brief Computes the trace of the underlying tensor
     *
     *  Invalid for anything but square matrices (rank-2 scalar tensors)
     *
     *  TRACE = \sum_i A(i,i)
     *
     *  @returns element sum of underlying tensor
     *  @throw std::runtime_error if @p rhs is not initialized or underlying
     * tensor is non-scalar or with rank != 2. Strong throw gurantee.
     */
    scalar_value_type trace() const;

    /** @brief Returns the extents of the wrapped tensor
     *
     *  @returns A list of extents per rank of wrapped tensor
     *  @throw std::runtime_error if @p rhs is not initialized.
     */
    extents_type make_extents() const;

    /** @brief Returns the inner extents of the wrapped tensor
     *
     *  @returns If @p FieldType is Scalar, the return value is simply 1. If
     *           @p FieldType is Tensor, the return is a map of element
     *           coordinates to their corresponding Shapes.
     *  @throw std::runtime_error if @p rhs is not initialized.
     */
    inner_extents_type make_inner_extents() const;

    /** @brief Compares two Buffers for value equality.
     *
     *  Two Buffers are considered equal if they:
     *
     *  - are over the same field (i.e., have the same template type parameter),
     *  - have the same backend implementation, and
     *  - if the backend implementations compare equal by value.
     *
     *  N.B. slight differences occurring from floating point arithmetic will
     *  result in this function returning inequality. Hence, in practice this
     *  function is primarily used in unit testing situations where the state of
     *  the Buffer is tightly controlled. Algorithms depending on tensor
     *  equality typically want to use allclose (TODO: ensure there's a cross
     *  link).
     *
     *  This overload is selected when @p rhs has the same field as the present
     *  instance.
     *
     *  @param[in] rhs The buffer being compared to.
     */
    bool operator==(const Buffer& rhs) const noexcept;

    /** @brief Compares two buffers with different fields.
     *
     *  This overload only participates in overload resolution when @p T is a
     *  different type than @p FieldType. This oveload always returns false
     *  because buffers over different fields are never equal.
     *
     *  @tparam T The field for @p rhs. This function only participates in
     *            overload resolution if @p T is different than FieldType.
     *  @tparam <anonymous> Template parameter used to disable this function,
     *                      via SFINAE, when @p T is the same as FieldType.
     *
     *  @param[in] rhs The buffer to compare to.
     *
     *  @return False buffers are always different if they use different fields.
     *
     *  @throw None No throw guarantee.
     */
    template<typename T, typename = enable_if_diff_field_t<T>>
    bool operator==(const Buffer<T>& rhs) const noexcept {
        return false;
    }

    /** @brief Prints a buffer to the provided ostream.
     *
     *  This function adds a text representation of the current tensor to the
     *  provided stream. The exact representation depends on the backend that
     *  is implementing the buffer. Generally speaking, the representation is
     *  only suitable for debugging purposes and should not be used as a long
     *  term means of storing the tensor or for data analysis.
     *
     *  @param[in,out] os The stream we are printing the buffer to. After this
     *                    call @p os will contain a text representation of this
     *                    buffer.
     *
     *  @return @p os after adding this buffer to it.
     *
     *  @throw std::ios_base::failure if adding the current Buffer instance to
     *                                to the stream fails. After the throw the
     *                                Buffer will be in the same state, but the
     *                                stream may be a different (albeit valid)
     *                                state.
     */
    std::ostream& print(std::ostream& os) const;

private:
    /// Asserts the PIMPL is initialized, throwing std::runtime_error if not
    void assert_initialized_() const;

    /// Initializes @p other 's PIMPL with a default version of this's PIMPL
    void default_initialize_(Buffer& other) const;

    /// Actually stores the state and implements the tensor.
    pimpl_pointer m_pimpl_;
};

/** @brief Determines if two buffers are different.
 *
 *  @relates Buffer
 *
 *  This function simply negates operator== and thus relies on its definition of
 *  equality.
 *
 *  @tparam T The field type for the buffer to the left of operator!=
 *  @tparam U The field type for the buffer to the right of operator!=
 *
 *  @param[in] lhs The buffer on the left
 *  @param[in] rhs The buffer on the right.
 *
 *  @return False if @p lhs is equal to @p rhs and true otherwise.
 *
 *  @throw None No throw guarantee.
 */
template<typename T, typename U>
bool operator!=(const Buffer<T>& lhs, const Buffer<U>& rhs) {
    return !(lhs == rhs);
}

/** @brief Prints a buffer to the provided ostream.
 *
 *  @relates Buffer
 *
 *  This function simply calls the print `member` of the Buffer class and exists
 *  so that Buffer instances can be printed via stream insertion operator (i.e.,
 *  the usual C++ way).
 *
 *  @tparam T The field type for the buffer. Expected to be either field::Scalar
 *            or field::Tensor.
 *
 *  @param[in,out] os The stream we are printing the buffer to. After this call
 *                    @p os will contain a text representation of @p rhs.
 *  @param[in] rhs The buffer we are printing.
 *
 *  @return @p os after adding @p rhs to it.
 *
 *  @throw std::ios_base::failure if adding the current Buffer instance to
 *                                to the stream fails. After the throw the
 *                                Buffer will be in the same state, but the
 *                                stream may be a different (albeit valid)
 *                                state.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, const Buffer<T>& rhs) {
    return rhs.print(os);
}

extern template class Buffer<field::Scalar>;
extern template class Buffer<field::Tensor>;

} // namespace tensorwrapper::tensor::buffer
