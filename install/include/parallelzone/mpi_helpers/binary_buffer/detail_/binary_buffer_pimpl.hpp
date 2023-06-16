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
#include <cstddef>
#include <memory>
#include <string>

namespace parallelzone::mpi_helpers::detail_ {

/** @brief Allows us to interact with buffer in a type-erased manner.
 *
 *  The BinaryBuffer's PIMPL has two layers. The BinaryBufferPIMPLBase class is,
 *  as the name suggests, the base layer. BinaryBufferPIMPLBase defines the
 *  API used by BinaryBuffer to interact with the PIMPL. The public facing
 *  methods all call pure virtual methods which must be overridden in the
 *  derived classes.
 */
class BinaryBufferPIMPLBase {
public:
    /// Type all PIMPL instances have in common
    using base_type = BinaryBufferPIMPLBase;

    /// Type of a read-only reference to the base of the PIMPL
    using const_base_reference = const base_type&;

    /// Type of a managed pointer to the base of the PIMPL
    using pointer_to_base = std::unique_ptr<base_type>;

    /// Type of a single byte in the buffer
    using value_type = std::byte;

    /// Type of a read/write pointer to a byte
    using pointer = value_type*;

    /// Type of a read-only pointer to a byte
    using const_pointer = const value_type*;

    /// Type used to indicate the number of bytes
    using size_type = std::size_t;

    /// Deleted to avoid slicing
    BinaryBufferPIMPLBase(BinaryBufferPIMPLBase&&) = delete;

    /// Deleted to avoid slicing
    BinaryBufferPIMPLBase& operator=(const_base_reference) = delete;

    /// Deleted to avoid slicing
    BinaryBufferPIMPLBase& operator=(BinaryBufferPIMPLBase&&) = delete;

    virtual ~BinaryBufferPIMPLBase() noexcept = default;

    /** @brief Makes a deep polymorphic copy of *this.
     *
     *  When invoked this method will have the most derived class make a deep
     *  copy of itself, including all state under it. The resulting deep copy
     *  is made on the heap, and a pointer to the deep copy's base class is
     *  returned.
     *
     *  Derived classes should override clone_() to implement this method
     *  according to the description provided here.
     *
     *  @return A pointer to a deep copy of *this. The copy is returned via a
     *          pointer to the base.
     *
     *  @throw ??? If allocating the deep copy throws. No throw guarantee.
     */
    pointer_to_base clone() const { return clone_(); }

    /** @brief A read/write pointer to the first byte in the buffer.
     *
     *  This method is the same as the const-version, except that the returned
     *  pointer can be used to modify the data in the buffer. If a user
     *  chooses to write to the buffer through the resulting pointer it is
     *  their responsability to ensure they stay in bounds.
     *
     *  This method is implemented by const-casting data_(). Thus derived
     *  classes do not need to explicitly implement this method.
     *
     *  @return a read/write pointer to the first byte in the buffer. If
     *          size() == 0, then the resulting pointer is nullptr.
     *
     *  @throw None No throw guarantee.
     */
    pointer data() noexcept {
        return const_cast<pointer>(std::as_const(*this).data());
    }

    /** @brief A pointer to the first byte in the buffer.
     *
     *  This method is used to get a pointer to the first byte in the buffer.
     *  N.B. that the resulting pointer is to a byte regardless of how the
     *  derived class actually stores the data. Subsequent bytes of the data
     *  can be accessed via usual pointer arithmetic (hence the underlying
     *  data must be stored contiguously). The returned pointer is only
     *  guaranteed to point to valid memory if size() > 0, in other cases
     *  the resulting pointer is null.
     *
     *  Derived classes should override data_() to implement this method
     *  according to the description provided here.
     *
     *  @return If size() > 0, a read-only pointer to the first byte in the
     *          buffer, otherwise nullptr
     *
     *  @throw None No throw guarantee.
     */
    const_pointer data() const noexcept { return data_(); }

    /** @brief The number of bytes in this buffer.
     *
     *  Derived classes should override size_() to implement this method
     *  according to the description provided here.
     *
     *  @return The number of elements in this buffer. If data() == nullptr
     *          this method will return 0.
     */
    size_type size() const noexcept { return size_(); }

protected:
    /// Used to implement derived class's ctor
    BinaryBufferPIMPLBase() = default;

    /// Protected so derived class can use it in clone, but users can't slice
    BinaryBufferPIMPLBase(const_base_reference other) = default;

private:
    /// Override to implement clone()
    virtual pointer_to_base clone_() const = 0;

    /// Override to implement data()
    virtual const_pointer data_() const noexcept = 0;

    /// Override to implement size()
    virtual size_type size_() const noexcept = 0;
};

/** @brief Implements base's API for type @p InternalBuffer
 *
 *  The BinaryBufferPIMPL class implements BinaryBufferPIMPLBase by wrapping
 *  a contiguous buffer. Any contiguous container which is relatively standards
 *  compliant should work (see description of @p InteranlBuffer for the exact
 *  requirements).
 *
 *  @tparam InternalBuffer The container used to actually store the binary
 *                         data. @p InternalBuffer is assumed to have
 *                         `data()` and `size()` methods as well as a member
 *                         `value_type` which is a typedef describing the
 *                         type of the actual buffer elements.
 */
template<typename InternalBuffer>
class BinaryBufferPIMPL final : public BinaryBufferPIMPLBase {
public:
    /// Type of this class including template type parameter
    using my_type = BinaryBufferPIMPL<InternalBuffer>;

    /// Ultimately a typedef of BinaryBufferPIMPLBase
    using BinaryBufferPIMPLBase::base_type;

    /// Ultimately a typedef of BinaryBufferPIMPLBase::pointer_to_base
    using base_type::pointer_to_base;

    /// Ultimately a typedef of BinaryBufferPIMPLBase::const_pointer
    using base_type::const_pointer;

    /// Ultimately a typedef of BinaryBufferPIMPLBase::size_type
    using base_type::size_type;

    /** @brief Creates *this by taking ownership of @p buffer.
     *
     *  BinaryBuffer owns the binary buffer inside it. This ctor is used to
     *  initialize that buffer. By default this ctor will initialize @p buffer
     *  by copying the argument provided to the ctor. To avoid the copy you
     *  must move the buffer into the ctor.
     *
     *  @param[in] buffer The contiguous buffer this class will wrap.
     *
     *  @throw None No throw guarantee.
     */
    explicit BinaryBufferPIMPL(InternalBuffer buffer) :
      m_buffer_(std::move(buffer)) {}

protected:
    /// Makes a deep copy m_buffer_
    BinaryBufferPIMPL(const my_type& other) = default;

private:
    /// Implements clone()
    pointer_to_base clone_() const override {
        auto p = new my_type(*this);
        return std::unique_ptr<my_type>(p);
    }

    /// Implements data() const
    const_pointer data_() const noexcept override {
        const auto* p = m_buffer_.data();
        return size_() ? reinterpret_cast<const_pointer>(p) : nullptr;
    }

    /// Implements size()
    size_type size_() const noexcept override {
        return m_buffer_.size() * sizeof(typename InternalBuffer::value_type);
    }

    /// The actual binary buffer
    InternalBuffer m_buffer_;
};

} // namespace parallelzone::mpi_helpers::detail_
