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
#include <parallelzone/mpi_helpers/binary_buffer/binary_view.hpp>
#include <parallelzone/mpi_helpers/binary_buffer/detail_/binary_buffer_pimpl.hpp>
#include <parallelzone/mpi_helpers/traits/traits.hpp>
#include <parallelzone/serialization.hpp>

namespace parallelzone::mpi_helpers {

/** @brief Wrapper treating contiguous binary data according to C++17 standard.
 *
 *  The C++17 standard introduces the `std::byte` class for representing a
 *  byte of binary data. Unfortunately, there's some trickery involved when
 *  trying to interface the `std::byte` class with pre-C++17 binary data
 *  representations (notably std::string). This class hides that trickery
 *  from the user making it easier to handle binary data in a manner consistent
 *  with the C++17 (and future) standard.
 *
 *  @note The API of this class exposes raw pointers. This is for API
 *        compatibility with MPI. The memory for those pointers is owned by
 *        *this, meaning users can modify the value pointed at, but should not
 *        otherwise modify the pointer.
 */
class BinaryBuffer {
public:
    /// Typedef of the class declaring the PIMPL's API
    using pimpl_type = detail_::BinaryBufferPIMPLBase;

    /// Ultimately a typedef of detail_::BinaryBufferPIMPLBase::value_type
    using value_type = pimpl_type::value_type;

    /// Ultimately a typedef of detail_::BinaryBufferPIMPLBase::pointer
    using pointer = pimpl_type::pointer;

    /// Ultimately a typedef of detail_::BinaryBufferPIMPLBase::const_pointer
    using const_pointer = pimpl_type::const_pointer;

    /// Type of read/write iterator
    using iterator = pointer;

    /// Type of a read/only iterator
    using const_iterator = const_pointer;

    /// Ultimately a typedef of detail_::BinaryBufferPIMPLBase::size_type
    using size_type = pimpl_type::size_type;

    /// Ultimately a typedef of detail_::BinaryBufferPIMPLBase::pointer_to_base
    using pimpl_pointer = pimpl_type::pointer_to_base;

    /** @brief Creates an empty BinaryBuffer.
     *
     *  Default constructed BinaryBuffer instances do not manage any memory.
     *  Default constructed BinaryBuffer instances are indistinguishable from
     *  BinaryBuffer instances which contain a PIMPL wrapping a buffer of size
     *  0.
     *
     *  @throw None No throw guarantee.
     */
    BinaryBuffer() noexcept = default;

    /** @brief Creates a BinaryBuffer capable of holding @p n bytes.
     *
     *  This ctor initializes *this to an @p n byte buffer. Each byte is set
     *  to 0.
     *
     *  @param[in] n The size of the buffer.
     *
     *  @throw std::bad_alloc if there is a problem allocating the memory.
     */
    BinaryBuffer(size_type n);

    /** @brief Creates a BinaryBuffer with the provided state.
     *
     *  This is the primary ctor, although users should not directly call it.
     *  Users should instead prefer the convenience make_binary_buffer free
     *  functions.
     *
     *  @param[in] p A pointer to the PIMPL which implements *this. The actual
     *               PIMPL is taken as a pointer to the base class so as to
     *               type erase the details of the actual buffer.
     *
     *  @throw None No throw guarantee.
     */
    explicit BinaryBuffer(pimpl_pointer p) noexcept : m_pimpl_(std::move(p)) {}

    /** @brief Initializes *this to a deep copy of @p other.
     *
     *  @param[in] other The binary buffer we are copying.
     *
     */
    BinaryBuffer(const BinaryBuffer& other) {
        if(other.has_pimpl_()) other.m_pimpl_->clone().swap(m_pimpl_);
    }

    /** @brief Overwrites the state in *this with a copy of @p rhs
     *
     *  @param[in] rhs The instance to copy.
     *
     *  @return *this after its state has been replaced with a deep copy of
     *          @p rhs.
     */
    BinaryBuffer& operator=(const BinaryBuffer& rhs) {
        if(&rhs != this) BinaryBuffer(rhs).swap(*this);
        return *this;
    }

    /** @brief Initializes *this with the state contained in @p other.
     *
     *  Standard move ctor. After this operation, all references to the state
     *  in @p other are still valid except that they now point to state in
     *  *this.
     *
     *
     *  @param[in,out] other The buffer to take the state from. After this
     *                       call @p other is in a state undistinguishable from
     *                       default construction.
     *
     *  @throw None No throw guarantee.
     */
    BinaryBuffer(BinaryBuffer&& other) noexcept = default;

    /** @brief Overwrites the state in *this with the state contained in
     *         @p rhs.
     *
     *  @param[in,out] rhs The buffer to take the state from. After this
     *                       call @p rhs is in a state undistinguishable from
     *                       default construction.
     *
     *  @return *this, but now containing the state of @p rhs.
     *
     *  @throw None No throw guarantee.
     */
    BinaryBuffer& operator=(BinaryBuffer&& rhs) noexcept = default;

    /** @brief Exchanges the state of *this with @p other.
     *
     *  This method simply swaps the PIMPL which is in *this with the PIMPL
     *  that is in @p other. After the operations all pointers to state in
     *  *this / @p other remain valid, except that the referenced state now
     *  lives in @p other / *this.
     *
     *  @param[in,out] other The instance to exchange state with. After this
     *                       call @p other will contain the state which was
     *                       previously in *this.
     *
     *  @throw None No throw guarantee.
     */
    void swap(BinaryBuffer& other) noexcept { m_pimpl_.swap(other.m_pimpl_); }

    /** @brief Returns an iterator to the first byte in the buffer.
     *
     *  As long as this buffer is non-empty, the iterator returned by this
     *  method can be used to modify the wrapped buffer. If the buffer is
     *  empty then de-referencing the returned iterator is undefined behavior.
     *
     *  @return If size() > 0, an iterator pointing to the first byte in the
     *          buffer. For size() == 0 this returns end().
     *
     *  @throw None No throw guarantee.
     */
    iterator begin() noexcept { return data(); }

    /** @brief Returns an iterator to the first byte in the buffer.
     *
     *  The iterator resulting from this method is read-only. If the buffer is
     *  empty then de-referencing the returned iterator is  undefined behavior.
     *
     *  @return If size() > 0, an iterator pointing to the first byte in the
     *          buffer. For size() == 0 this returns end().
     *
     *  @throw None No throw guarantee.
     */
    const_iterator begin() const noexcept { return data(); }

    /** @brief Returns an iterator to just past the last byte.
     *
     *  The iterator returned by this method is meant to be used as a
     *  semaphore for stopping iteration. In particular this means that the
     *  iterator should not be de-referenced.
     *
     *  @return An iterator pointing to just past the last byte.
     *
     *  @throw None No throw guarantee.
     */
    iterator end() { return data() + size(); }

    /** @brief Returns an iterator to just past the last byte.
     *
     *  The iterator returned by this method is meant to be used as a
     *  semaphore for stopping iteration. In particular this means that the
     *  iterator should not be de-referenced.
     *
     *  @return An iterator pointing to just past the last byte.
     *
     *  @throw None No throw guarantee.
     */
    const_iterator end() const { return data() + size(); }

    /** @brief Returns a raw pointer to the underlying buffer.
     *
     *  The underlying buffer is guaranteed to be contiguous. This method
     *  can be used to obtain a raw_pointer to the first byte. Subsequent
     *  bytes can then be accessed via pointer arithmetic. The pointer returned
     *  by this method can be used to change the values in the buffer, but
     *  users should not modify the pointer itself.
     *
     *  @return If size() > 0 this will be a pointer to the first byte in the
     *          underlying buffer. If size() == 0 this will be the nullptr.
     *
     *  @throw None No throw guarantee.
     */
    pointer data() noexcept {
        return has_pimpl_() ? m_pimpl_->data() : nullptr;
    }

    /** @brief Returns a raw pointer to the underlying buffer.
     *
     *  The underlying buffer is guaranteed to be contiguous. This method
     *  can be used to obtain a raw_pointer to the first byte. Subsequent
     *  bytes can then be accessed via pointer arithmetic. The pointer returned
     *  by this method.
     *
     *  @return If size() > 0 this will be a pointer to the first byte in the
     *          underlying buffer. If size() == 0 this will be the nullptr.
     *
     *  @throw None No throw guarantee.
     */
    const_pointer data() const noexcept {
        return has_pimpl_() ? m_pimpl_->data() : nullptr;
    }

    /** @brief Returns the number of bytes in this buffer.
     *
     *  This method returns the number of bytes in the buffer. Of note, this
     *  means that if the underlying buffer has elements larger than a byte,
     *  this method will still return the number of elements in bytes. Also
     *  worth mentioning an empty buffer has size() == 0.
     *
     *  @return The number of bytes in the buffer.
     *
     *  @throw None No throw guarantee.
     */
    size_type size() const noexcept {
        return has_pimpl_() ? m_pimpl_->size() : 0;
    }

    /** @brief Determines if *this is value equal to @p rhs.
     *
     *  For the purposes of BinaryBuffer, value equal means that *this and
     *  @p rhs both hold the same number of bytes (as determined by size())
     *  and that byte-by-byte *this compares equal to @p rhs. In particular
     *  this means *this and @p rhs may use different underlying buffers and
     *  that this->data() need not equal rhs.data().
     *
     *  @param[in] rhs The instance we are comparing to.
     *
     *  @return True if *this is value equal to @p rhs and false otherwise.
     *
     *  @throw None No throw gurantee.
     */
    bool operator==(const BinaryBuffer& rhs) const noexcept;

    /** @brief Determines if *this is different than @p rhs.
     *
     *  This method defines "different" as not value equal. See the description
     *  of operator== for the definition of value equal.
     *
     *  @param[in] rhs The instance we are comparing to.
     *
     *  @return False if *this is value equal to @p rhs and true otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator!=(const BinaryBuffer& rhs) const noexcept {
        return !(*this == rhs);
    }

    /** @brief Allows implicit conversion to BinaryView
     *
     *  BinaryView objects are used as read/write references to BinaryBuffer
     *  instances. This method allows BinaryView instances to be implicitly
     *  constructed from BinaryBuffer objects, analogous to how references are
     *  implicitly constructed for normal types.
     *
     *  @return A BinaryView instance aliasing the binary buffer in *this.
     *
     *  @throw None No throw guarantee.
     */
    operator BinaryView() noexcept { return BinaryView(data(), size()); }

    /** @brief Allows implicit conversion to ConstBinaryView
     *
     *  ConstBinaryView objects are used as read-only references to BinaryBuffer
     *  instances. This method allows ConstBinaryView instances to be implicitly
     *  constructed from BinaryBuffer objects, analogous to how const references
     *  are implicitly constructed for normal types.
     *
     *  @return A ConstBinaryView instance aliasing the binary buffer in *this.
     *
     *  @throw None No throw guarantee.
     */
    operator ConstBinaryView() const noexcept {
        return ConstBinaryView(data(), size());
    }

private:
    /// Code factorization for determining if m_pimpl_ holds a value
    bool has_pimpl_() const noexcept { return static_cast<bool>(m_pimpl_); }

    /// The actual state of *this
    pimpl_pointer m_pimpl_;
};

/** @brief Wraps the process of creating a binary view of an object of type @p T
 *
 *  @relates BinaryBuffer
 *
 *  This function will create a BinaryView of @p input in an intelligent manner.
 *  By intelligent we mean that it will try to avoid serializing @p input if
 *  at all possible. Whether @p input needs to be serialized is controlled by
 *  the trait `NeedsSerialized`. If @p input needs to be serialized the
 *  resulting BinaryView will be responsible for managing the lifetime of the
 *  buffer @p input is serialized into, if @p input does not need to be
 *  serialized the user is responsible for ensuring @p input remains in the
 *  same state until the resulting BinaryView is destroyed.
 *
 *  @note In practice this function is usually called and the result consumed
 *        immediately. This greatly simplifies lifetime management.
 *
 *  @tparam T The type of @p input is std::decay_t<T>. The type @p T captures
 *          the semantics of how @p input was passed to make_binary_view (
 *          *i.e.*, is it cv-qualified, was it passed by reference?, etc.).
 *          @p T is an implicit template parameter and does not need to be
 *          specified by the user.
 *
 * @param[in] input The object we want a binary view of.
 *
 * @return A BinaryView of @p input.
 *
 */
template<typename T>
BinaryBuffer make_binary_buffer(T&& input);

/** @brief Wraps the process of going from a BinaryBuffer back to an object.
 *
 *  @relates BinaryBuffer
 *
 *  This function is a convenience function for creating an object from an array
 *  of contiguous binary data. The BinaryBuffer is assumed to contain the
 *  serialized form of an object of type @p T if NeedsSerialized<T>::value
 *  is true. Otherwise it is assumed that @p T can be created by copying the
 *  data out of @p buffer.
 *
 *  @tparam T The type we want to convert the binary data to. @p T is an
 *          explicit template type parameter and must be specified by the
 *          user. @p T should be an unqualified type (*i.e.*, no const,
 *          references, or the like). If needs_serialized<T> is false we assume
 *          that T has a range ctor that can be used to fill in a new @p T
 *          instance.
 *
 *  @param[in] buffer The contiguous binary buffer we are making the object
 * from.
 *
 *  @return An instance of type @p T initialized from the binary data in
 *          @p buffer.
 *
 */
template<typename T>
T from_binary_buffer(const BinaryBuffer& buffer);

} // namespace parallelzone::mpi_helpers

#include "binary_buffer.ipp"
