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
#include "utilities/iterators/offset_iterator.hpp"
#include <string>
namespace utilities {

/** @brief Code factorization for a container that supports indexing.
 *
 *  When creating new classes it is not uncommon to need classes that are
 *  container-like. This class in particular is useful for when the resulting
 *  class should be an indexable container. By this we mean that it should
 *  satisfy the C++ concept of "container" and users of the container can
 *  retrieve elements by an integral index/offset.
 *
 *  To use this class derive from it and in your derived class implement:
 *  - `size_type size_() const noexcept` - Should return the number of elements
 *    in your container. The implementing function should not throw.
 *  - `reference at_(size_type)` - Should return a (possibly) modifiable
 *    reference to the requested element (the provided argument being the index
 *    of the requested element). Whether the returned reference is actually
 *    modifiable is upt to the implementation (the implementation is free to
 *    return a constant reference if the container should be read-only).
 *  - `const_reference at_(size_type) const` - same as the non-const version
 *    except that it should return the element in a read-only manner.
 *
 *  Additionally your class must define a typedef `value_type` which is the
 *  non-cv-qualified type of the elements in the container.
 *
 *  @tparam DerivedType The type of the container that is being implemented.
 *                      The IndexableContainerBase class works off of the CRTP
 *                      and will use the DerivedType to implement the container
 *                      API.
 */
template<typename DerivedType>
class IndexableContainerBase {
public:
    /// Type used for indexing and offsets, unsigned integral POD type
    using size_type = std::size_t;
    /// Type of a random-access iterator that can modify the container
    using iterator = iterators::OffsetIterator<DerivedType>;
    /// Type of a random-access iterator to a read-only container instance
    using const_iterator = iterators::OffsetIterator<const DerivedType>;

    /** @brief Determines if the container has any elements in it or not.
     *
     *  This function can be used to determine if a container has any elements
     *  in it. This function ultimately works by calling the derived class's
     *  `size_()` member.
     *
     *  @return True if this container has no elements and false otherwise.
     *
     *  @throw None. No throw guarantee.
     */
    bool empty() const noexcept { return cbegin() == cend(); }

    /** @brief Determines the number of elements in the container.
     *
     *  This function is used to get the number of elements in the container.
     *  It ultimately works by calling the derived class's `size_()` member.
     *
     *
     *  @return The number of elements in the container.
     *
     *  @throw None No throw guarantee.
     */
    size_type size() const noexcept { return downcast_().size_(); }

    /** @brief Retrieves an element from the container by index.
     *
     *  This function is used to retrieve an element given its index in the
     *  container. This function ultimately works by calling the derived class's
     *  `size_()` (for the bounds check) and `at_(size_type)` (for the
     *  retrieval) members.
     *
     *  @param[in] index The index of the element to return. Must be in the
     *                   range [0, size()).
     *
     *  @return The requested element as a (possibly) read/write reference.
     *
     *  @throw None No throw guarantee. If @p index is not in the range
     *         [0, size()) this call is undefined behavior.
     */
    decltype(auto) operator[](size_type index) noexcept;

    /** @brief Retrieves an element from the container by index (no bounds
     * check).
     *
     *  This function is used to retrieve an element given its index in the
     *  container. This function ultimately works by calling the derived class's
     *  `size_()` (for the bounds check) and `at_(size_type)const` (for the
     *  retrieval) members.
     *
     *  @param[in] index The index of the element to return. Must be in the
     *                   range [0, size()).
     *
     *  @return The requested element as a read-only reference.
     *
     *  @throw None No throw guarantee. If @p index is not in the range
     *         [0, size()) this call is undefined behavior.
     */
    decltype(auto) operator[](size_type index) const noexcept;

    /** @brief Retrieves an element from the container by index.
     *
     *  This function is used to retrieve an element given its index in the
     *  container. This function ultimately works by calling the derived class's
     *  `size_()` (for the bounds check) and `at_(size_type)` (for the
     *  retrieval) members.
     *
     *  @param[in] index The index of the element to return. Must be in the
     *                   range [0, size()).
     *
     *  @return The requested element as a (possibly) read/write reference.
     *
     *  @throw std::out_of_range if @p index is not in the range [0, size()).
     *         Strong throw guarantee.
     */
    decltype(auto) at(size_type index);

    /** @brief Retrieves an element from the container by index.
     *
     *  Sames as the non-const version, except that the resulting object is
     *  read-only.
     *
     *  @param[in] index The index of the element to return. Must be in the
     *                   range [0, size()).
     *
     *  @return The requested element as a read-only reference.
     *
     *  @throw std::out_of_range if @p index is not in the range [0, size()).
     *         Strong throw guarantee.
     */
    decltype(auto) at(size_type index) const;

    /** @brief Returns an iterator pointing at the first element in the
     *         container.
     *
     *  This member function is used to create an iterator that points to the
     *  first element in the container. If the container is empty the resulting
     *  iterator will be identical to the iterator returned by `end()`. The
     *  iterator resulting from this function ultimately works by calling the
     *  derived class's `at_(size_type)` member function.
     *
     *  @return An iterator pointing at the first element in the container. The
     *          resulting iterator may be used to modify the container if the
     *          derived class's `at_(size_type)` member function returns
     *          read-/write- references.
     *
     *  @throw none No throw guarantee.
     */
    iterator begin() noexcept { return {0, &(downcast_())}; }

    /** @brief Returns an iterator pointing at the first element in the
     *         container.
     *
     *  This member function is used to create an iterator that points to the
     *  first element in the container. If the container is empty the resulting
     *  iterator will be identical to the iterator returned by `end()`. The
     *  iterator resulting from this function ultimately works by calling the
     *  derived class's `at_(size_type)const` member function.
     *
     *  @return An iterator pointing at the first element in the container. The
     *          resulting iterator can not be used to modify the aliased
     *          elements.
     *
     *  @throw none No throw guarantee.
     */
    const_iterator begin() const noexcept { return {0, &(downcast_())}; }

    /** @brief Returns an iterator pointing at the first element in the
     *         container.
     *
     *  This member function is used to create an iterator that points to the
     *  first element in the container. If the container is empty the resulting
     *  iterator will be identical to the iterator returned by `end()`. The
     *  iterator resulting from this function ultimately works by calling the
     *  derived class's `at_(size_type)const` member function.
     *
     *  @return An iterator pointing at the first element in the container. The
     *          resulting iterator can not be used to modify the aliased
     *          elements.
     *
     *  @throw none No throw guarantee.
     */
    const_iterator cbegin() const noexcept { return begin(); }

    /** @brief Returns an iterator just past the end of the container.
     *
     *  This function is used to return an iterator that points to just past
     *  the end of the container. The resulting iterator is meant to serve as
     *  a semaphore for when iteration should stop; it should not be
     *  dereferenced and doing so is undefined behavior. This function
     *  ultimately works by calling the derived class's `size_()` member.
     *
     *  @return An iterator pointing to just past the end of the container.
     *
     *  @throw None No throw guarantee.
     */
    iterator end() noexcept { return {size(), &(downcast_())}; }

    /** @brief Returns an iterator just past the end of the container.
     *
     *  This function is used to return an iterator that points to just past
     *  the end of the container. The resulting iterator is meant to serve as
     *  a semaphore for when iteration should stop; it should not be
     *  dereferenced and doing so is undefined behavior. This function
     *  ultimately works by calling the derived class's `size_()` member.
     *
     *  @return An iterator pointing to just past the end of the container.
     *
     *  @throw None No throw guarantee.
     */
    const_iterator end() const noexcept { return {size(), &downcast_()}; }

    /** @brief Returns an iterator just past the end of the container.
     *
     *  This function is used to return an iterator that points to just past
     *  the end of the container. The resulting iterator is meant to serve as
     *  a semaphore for when iteration should stop; it should not be
     *  dereferenced and doing so is undefined behavior. This function
     *  ultimately works by calling the derived class's `size_()` member.
     *
     *  @return An iterator pointing to just past the end of the container.
     *
     *  @throw None No throw guarantee.
     */
    const_iterator cend() const noexcept { return end(); }

private:
    /// Code factorization for ensuring an index is in the range [0, size())
    void check_index_(size_type index) const;
    /// Downcasts this instance to a read-/write-able container
    DerivedType& downcast_() noexcept;
    /// Downcasts this instance to a read-only container
    const DerivedType& downcast_() const noexcept;
}; // class IndexableContainerBase

/** @brief Compares two IndexableContainerBase instances for equality.
 *
 *  @relates IndexableContainerBase
 *
 *  This operator ultimately works by calling the DerivedType's `size_()` and
 *  `const_reference at_(size_type)const` member functions. The containers are
 *  defined as equal if they are the same size and `lhs[i] == rhs[i]` holds for
 *  all `i` in the range [0, lhs.size()).
 *
 *  @tparam DerivedType The type of the container being implemented by the
 *                      IndexableContainerBase class.
 *
 *  @param[in] lhs The instance on the left-side of the operator.
 *  @param[in] rhs The instance on the right-side of the operator.
 *
 *  @return True if the containers contain the same number of elements and the
 *          same elements in the same order; false otherwise.
 *
 *  @throw None No throw guarantee.
 */
template<typename DerivedType>
bool operator==(const IndexableContainerBase<DerivedType>& lhs,
                const IndexableContainerBase<DerivedType>& rhs) noexcept {
    if(lhs.size() != rhs.size()) return false;
    /* Note that here we don't use std::equal because it assumes that the return
     * value of dereferencing an iterator is a true reference. Consequentially,
     * we'll get segfaults if the user's container returns things by temporary
     * copies.
     */
    for(decltype(lhs.size()) counter = 0; counter < lhs.size(); ++counter)
        if(lhs[counter] != rhs[counter]) return false;
    return true;
}

/** @brief Determines if two IndexableContainerBase instances are different.
 *
 *  @relates IndexableContainerBase
 *
 *  This operator ultimately works by calling the DerivedType's `size_()` and
 *  `const_reference at_(size_type)const` member functions. The containers are
 *  defined as equal if they are the same size and `lhs[i] == rhs[i]` holds for
 *  all `i` in the range [0, lhs.size()). "Different" is defined as "not equal".
 *
 *  @tparam DerivedType The type of the container being implemented by the
 *                      IndexableContainerBase class.
 *
 *  @param[in] lhs The instance on the left-side of the operator.
 *  @param[in] rhs The instance on the right-side of the operator.
 *
 *  @return False if the containers contain the same number of elements and the
 *          same elements in the same order; true otherwise.
 *
 *  @throw None No throw guarantee.
 */
template<typename DerivedType>
bool operator!=(const IndexableContainerBase<DerivedType>& lhs,
                const IndexableContainerBase<DerivedType>& rhs) noexcept {
    return !(lhs == rhs);
}

// -----------------------------Implementations---------------------------------

template<typename DerivedType>
decltype(auto) IndexableContainerBase<DerivedType>::operator[](
  size_type index) noexcept {
    return downcast_().at_(index);
}

template<typename DerivedType>
decltype(auto) IndexableContainerBase<DerivedType>::operator[](
  size_type index) const noexcept {
    return downcast_().at_(index);
}

template<typename DerivedType>
decltype(auto) IndexableContainerBase<DerivedType>::at(size_type index) {
    check_index_(index);
    return downcast_().at_(index);
}

template<typename DerivedType>
decltype(auto) IndexableContainerBase<DerivedType>::at(size_type index) const {
    check_index_(index);
    return downcast_().at_(index);
}

template<typename DerivedType>
void IndexableContainerBase<DerivedType>::check_index_(size_type index) const {
    if(index < size()) return;
    std::string msg{"Index: "};
    msg += std::to_string(index) + " is not in the range [0, ";
    msg += std::to_string(size()) + ").";
    throw std::out_of_range(msg);
}

template<typename DerivedType>
DerivedType& IndexableContainerBase<DerivedType>::downcast_() noexcept {
    return static_cast<DerivedType&>(*this);
}

template<typename DerivedType>
const DerivedType& IndexableContainerBase<DerivedType>::downcast_()
  const noexcept {
    return static_cast<const DerivedType&>(*this);
}

} // namespace utilities
