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
#include "utilities/iterators/bidirectional_iterator_base.hpp"

namespace utilities::iterators {

/** @brief This class is designed to facilitate making your own random access
 *         iterator class.
 *
 *  To use this class your derived class needs to implement the functions for
 *  the InputIteratorBase and BidirectionalIteratorBase classes:
 *  - `ParentType& increment()`
 *  - `const_reference dereference()const`
 *  - `reference dereference()`
 *  - `bool are_equal(const ParentType&) const noexcept`
 *  - `ParentType& decrement()`
 *
 *  As well as:
 *
 *  - `ParentType& advance(difference_type)` - If the argument is positive this
 *    function should increment the current iterator by the specified number of
 *    iterations and return the result. Otherwise, if the argument is negative
 *    this function should decrement the current iterator by the specified
 *    number of iterations and return the result. The implementation is free to
 *    throw if it chooses.
 *  - `difference_type distance_to(const ParentType&) const` - Determines the
 *     number of iterations required to make the current iterator point to the
 *     same element as the argument. A positive value indicates that the current
 *     iterator is behind the argument and a negative value indicates that the
 *     current iterator is ahead of the argument. The user's implementation may
 *     throw if, for example, the argument iterator is unreachable.
 *
 *  @tparam ParentType The type of the derived class, which is implementing this
 *                     RandomAccessIteratorBase instance.
 */
template<typename ParentType>
struct RandomAccessIteratorBase : public BidirectionalIteratorBase<ParentType> {
    /// Indicates that this iterator is a random access iterator for TMP
    using iterator_category = std::random_access_iterator_tag;

    /** @brief Advances the current iterator the specified number of iterations.
     *
     *  This function is used to increment (if @p n is positive) or decrement
     *  (if @p n is negative) the current iterator by the specified number of
     *  iterations. This function ultimately works by calling the derived
     *  class's `advance` member.
     *
     *  @tparam DifferenceType The type of @p n. Assumed to be a signed
     *                         integral POD type such as long int.
     *
     *  @param[in] n The number of iterations to advance by.  If @p n is
     *               negative then the iterator will actually move backward by
     *               @p n.
     *  @returns The iterator incremented or decremented by @p n elements.
     *
     *  @throws ??? If the derived class's `advance()` method throws. Same throw
     *              guarantee.
     */
    template<typename DifferenceType>
    ParentType& operator+=(DifferenceType&& n);

    /** @brief Creates a copy of the current iterator that points to the element
     *         a specified number of iterations away.
     *
     *   This function is used to create a new iterator that has been
     *   incremented (if @p n is positive) or decremented (if @p n is negative)
     *   relative to the current iterator by the specified number of iterations.
     *   This function ultimately works by calling the derived class's copy
     *   constructor and `advance` member.
     *
     *  @tparam DifferenceType The type of @p n. Assumed to be a signed
     *                         integral POD type such as long int.
     *
     *  @param[in] n The number of iterations to move forward by.  If @p n is
     *               negative then the iterator will actually move backward by
     *               @p n.
     *  @returns A copy of the current iterator pointing to the element @p n
     *           iterations away.
     *  @throws ??? If the derived class's copy constructor or `advance()`
     *              member throw. Same throw guarantee.
     */
    template<typename DifferenceType>
    ParentType operator+(DifferenceType n) const;

    /** @brief Retreats the current iterator the specified number of iterations.
     *
     *  This function is used to decrement (if @p n is positive) or increment
     *  (if @p n is negative) the current iterator by the specified number of
     *  iterations. This function ultimately works by calling the derived
     *  class's `advance` member with @p n multiplied by negative 1.
     *
     *  @tparam DifferenceType The type of @p n. Assumed to be a signed
     *                         integral POD type such as long int.
     *
     *  @param[in] n The number of iterations to retreat by.  If @p n is
     *               negative then the iterator will actually advance by @p n.
     *
     *  @returns The iterator incremented or decremented by @p n elements.
     *
     *  @throws ??? If the derived class's `advance()` method throws. Same throw
     *              guarantee.
     */
    template<typename DifferenceType>
    ParentType& operator-=(DifferenceType n) {
        return (*this) += (-n);
    }

    /** @brief Creates a copy of the current iterator that points to the element
     *         a specified number of iterations away.
     *
     *   This function is used to create a new iterator that has been
     *   decremented (if @p n is positive) or incremented (if @p n is negative)
     *   relative to the current iterator by the specified number of iterations.
     *   This function ultimately works by calling the derived class's copy
     *   constructor and `advance` member with @p n multiplied by negative 1.
     *
     *  @tparam DifferenceType The type of @p n. Assumed to be a signed
     *                         integral POD type such as long int.
     *
     *  @param[in] n The number of iterations to move backward by.  If @p n is
     *               negative then the iterator will actually move forward by
     *               @p n.
     *  @returns A copy of the current iterator pointing to the element @p n
     *           iterations away.
     *  @throws ??? If the derived class's copy constructor or `advance()`
     *              member throw. Same throw guarantee.
     */
    template<typename DifferenceType>
    ParentType operator-(DifferenceType n) const;

    /** @brief Provides random access to any element in the container relative
     *         to the element currently pointed to by this iterator.
     *
     *  This function will return the element that is @p n iterations away from
     *  the element current being pointed at. The current iterator will still
     *  point to the same element after this function has been called. This
     *  function ultimately works by calling the derived class's copy
     *  constructor and the `advance()` member.
     *
     *  @tparam DifferenceType The type of @p n. Assumed to be a signed
     *                         integral POD type such as long int.
     *  @param[in] n The index, relative to the currently pointed to element, of
     *               the desired element.
     *  @return The element that is @p n iterations away. The returned element
     *          will be of whatever type is returned by the non-const
     *          `dereference()`.
     *
     *  @throws ??? If the derived class's copy constructor of `advance` member
     *              throw strong throw guarantee.
     */
    template<typename DifferenceType>
    decltype(auto) operator[](DifferenceType n) const {
        return *((*this) + n);
    }

    /** @brief Compares two iterators and returns true if the current iterator
     *         points to an element appearing earlier in the container
     *
     *  This function ultimately calls derived class's `distance_to` member and
     *  then uses the fact that a positive distance means that @p rhs points to
     *  an element further in the sequence.
     *
     *  @param[in] rhs The iterator to compare to.
     *  @returns True if the current iterator points to an element indexed
     *           earlier than the element pointed to by @p rhs and false
     *           otherwise.
     *  @throws ??? If the derived class's `distance_to` member throws. Same
     *              throw guarante..
     */
    bool operator<(const ParentType& rhs) const;

    /** @brief Compares two iterators and returns true if the current iterator
     *         points to an element appearing earlier in the container or if the
     *         two iterators point to the same element.
     *
     *  This function ultimately works by calling the derived class's
     *  `distance_to` member and using the fact that if @p rhs is not less than
     *  this instance, than this instance must be equal to or greater to @p rhs.
     *
     *  @param[in] rhs The iterator to compare to.
     *  @returns True if the current iterator points to the same index as @p rhs
     *                or an early index.
     *  @throws ??? If the derived class's `distance_to` member throws. Same
     *              throw guarantee.
     */
    bool operator<=(const ParentType& rhs) const;

    /** @brief Compares two iterators and returns true if this iterator points
     *         to an element later in the container than the rhs iterator.
     *
     *  This function ultimately calls the derived class's `distance_to` member
     *  and uses the fact that if @p rhs is less than this instance, than this
     *  instance must be greater than @p rhs.
     *
     *  @param[in] rhs The iterator to compare to.
     *
     *  @returns True if the current element is indexed after that of @p rhs and
     *           false otherwise.
     *
     *  @throws ??? If the derived class's `distance_to` member throws. Same
     *              throw guarantee.
     */
    bool operator>(const ParentType& rhs) const;

    /** @brief Compares two iterators and returns true if they point to the
     *         same element, or if the element pointed to by this iterator
     *         occurs later in the sequence than that of the rhs iterator.
     *
     *  This function ultimately calls `distance_to` and relies on the fact that
     *  if this instance is not less than @p rhs, than it must be greater than
     *  or equal to @p rhs.
     *
     *  @param[in] rhs The iterator to compare to.
     *  @returns true if the current iterator points to the same element or an
     *           element later in the sequence than the one pointed to by
     *           @p rhs and false otherwise.
     *
     *  @throws ??? If `distance_to` throws. Same throw guarantee.
     */
    bool operator>=(const ParentType& rhs) const;

    /** @brief Returns the distance between this iterator and another iterator.
     *
     *  This function will return the number of iterations required to make
     *  @p rhs equal this iterator. If the returned value is positive it means
     *  that @p rhs is behind this iterator, whereas a negative value means that
     *  @p rhs is ahead of this iterator (a value of zero means they point to
     *  the same element). This function ultimately works by calling the derived
     *  class's `distance_to` member.
     *
     *  @param[in] rhs The iterator to compare to.
     *  @returns A signed integral POD type containing the distance between this
     *           iterator and @p rhs.
     *  @throws ??? If `distance_to` throws. Same throw guarantee.
     */
    decltype(auto) operator-(const ParentType& rhs) const;

}; // class RandomAccessIteratorBase

// ---------------------------------Implementations-----------------------------
template<typename ParentType>
template<typename DifferenceType>
ParentType& RandomAccessIteratorBase<ParentType>::operator+=(
  DifferenceType&& n) {
    return this->downcast_().advance(std::forward<DifferenceType>(n));
}

template<typename ParentType>
template<typename DifferenceType>
ParentType RandomAccessIteratorBase<ParentType>::operator+(
  DifferenceType n) const {
    ParentType copy_of_me(this->downcast_());
    return copy_of_me += n;
}

template<typename ParentType>
template<typename DifferenceType>
ParentType RandomAccessIteratorBase<ParentType>::operator-(
  DifferenceType n) const {
    ParentType copy_of_me(this->downcast_());
    return copy_of_me -= n;
}

template<typename ParentType>
bool RandomAccessIteratorBase<ParentType>::operator<(
  const ParentType& rhs) const {
    return this->downcast_().distance_to(rhs) > 0;
}

template<typename ParentType>
bool RandomAccessIteratorBase<ParentType>::operator>(
  const ParentType& rhs) const {
    return rhs < this->downcast_();
}

template<typename ParentType>
bool RandomAccessIteratorBase<ParentType>::operator<=(
  const ParentType& rhs) const {
    return !(rhs < this->downcast_());
}

template<typename ParentType>
bool RandomAccessIteratorBase<ParentType>::operator>=(
  const ParentType& rhs) const {
    return !(this->downcast_() < rhs);
}

template<typename ParentType>
decltype(auto) RandomAccessIteratorBase<ParentType>::operator-(
  const ParentType& rhs) const {
    return rhs.distance_to(this->downcast_());
}

} // namespace utilities::iterators
