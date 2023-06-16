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
#include <iterator>

namespace utilities::iterators {

/** @brief This class is designed to facilitate making your own input iterator
 *  class.
 *
 *  To use this class to quickly define an input iterator you should publicly
 *  derive from this class and have your class implement the following
 *  functions:
 *
 *  - `ParentType& increment()` - should increment the current iterator and
 *    return `*this`. Implementation should feel free to throw if the
 *    increment can not be done.
 *  - `reference dereference() const` - should dereference the container and
 *    return whatever type the corresponding container uses for a read/write
 *    reference. Iterators to const containers should return const_reference.
 *    Implementation should feel free to throw if the iterator is not in a
 *    dereferencable state.
 *  - `bool are_equal(const ParentType&)const noexcept` - should determine if
 *    two iterators point to the same element. If they do it should return true
 *    and if they do not it should return false.
 *
 *  Your class must also be copy constructable.
 *
 *  @tparam ParentType The type of your derived class. See the class description
 *                     for the criteria it must meet.
 */
template<typename ParentType>
class InputIteratorBase {
private:
    /// Type of this base class
    using my_type = InputIteratorBase<ParentType>;
    /// Type of this base class when it is read-only
    using const_my_type = const InputIteratorBase<ParentType>;

public:
    /// The concept tag this iterator obeys
    using iterator_category = std::input_iterator_tag;

    virtual ~InputIteratorBase() noexcept = default;

    /** @brief Defines the public API for dereferencing the iterator to a
     *         (possibly) read-/write-able reference.
     *
     *  This function is ultimately implemented by calling the derived class's
     *  `dereference()` member. Whether the returned instance is modifiable or
     *  not is determined by the derived class. In particular the derived class
     *  may return a read-only reference if the iterator is iterating over a
     *  read-only container.
     *
     *  @return A (possibly) read-/write-able reference to the element this
     *          iterator currently points to.
     *
     *  @throws ??? if the derived class throws. Same exception guarantee.
     */
    decltype(auto) operator*() { return downcast_().dereference(); }

    /** @brief Defines the public API for dereferencing the iterator to a
     *         read-only reference.
     *
     *  This function is ultimately implemented by calling the derived class's
     *  `dereference() const` member.
     *
     *  @return A read-only reference to the element this iterator currently
     *          points to.
     *
     *  @throws ??? if the derived class throws. Same exception guarantee.
     */
    decltype(auto) operator*() const { return downcast_().dereference(); }

    /** @brief Provides access to an element's member functions directly.
     *
     *  This operator allows you to directly access the member functions of the
     *  pointed to, (possibly) read-/write-able, instance via the syntax
     *  `itr->member_fxn()` as opposed to the slightly messier
     *  `(*itr).member_fxn()` syntax. Ultimately this function is implemented by
     *  calling `dereference()`.
     *
     *  @returns The address of the instance currently being pointed to so that
     *           it can be used with the arrow operator.
     *
     *  @throws ??? if the derived class throws. Same throw guarantee.
     */
    decltype(auto) operator->() { return &(operator*()); }

    /** @brief Provides access to an element's member functions directly.
     *
     *  This operator allows you to directly access the member functions of the
     *  pointed to, read-only, instance via the syntax `itr->member_fxn()` as
     *  opposed to slightly messier `(*itr).member_fxn()` syntax. Ultimately
     *  this function is implemented by calling `dereference() const`.
     *
     *  @returns The address of the instance currently being pointed to so that
     *           it can be used with the arrow operator.
     *
     *  @throws ??? if the derived class throws. Same throw guarantee.
     */
    decltype(auto) operator->() const { return &(operator*()); }

    /** @brief Increments the current iterator and returns it.
     *
     *  This function increments the iterator before returning the iterator.
     *  This is ultimately implemented by calling the derived class's
     *  `increment()` method.
     *
     *  @returns The current iterator after it has been advanced by one.
     *
     *  @throws ??? if the derived class's `increment()` method throws. Same
     *              throw guarantee.
     */
    ParentType& operator++() { return downcast_().increment(); }

    /** @brief Returns the iterator before incrementing it.
     *
     *  Semantically this function returns the iterator and then increments it,
     *  thereby allowing you to use the iterator with its pre-increment value.
     *  This is actually accomplished by copying this instance, incrementing
     *  the non-copied instance via `increment()`, and then returning the copy.
     *
     *  @returns A copy of the current iterator as it was before calling this
     *           function.
     *
     *  @throws ??? if either the copy constructor or `increment()` throws.
     *              Same throw guarantee.
     */
    ParentType operator++(int);

    /** @brief Determines if two iterators point to the same element.
     *
     *  This function ultimately works by calling the derived class's
     *  `are_equal` member.  Hence the definition of equality resides with the
     *  derived class.
     *
     *  @param[in] rhs The iterator to compare to.
     *  @return true if the two iterators are equal and false otherwise.
     *  @throws None. No throw guarantee
     */
    bool operator==(const ParentType& rhs) const noexcept;

    /** @brief Determines if two iterators point to different elements.
     *
     *  This function ultimately works by calling the derived class's
     *  `are_equal` member and negating the result.  Hence the definition of
     *  equality resides with the derived class and the definition of
     *  "different" is "not equal".
     *
     *  @param[in] rhs The iterator to compare to.
     *  @return false if the two iterators are equal and true otherwise.
     *  @throws None. No throw guarantee
     */
    bool operator!=(const ParentType& rhs) const noexcept;

protected:
    /// Downcasts this to a read-/write-able instance of the derived class
    ParentType& downcast_() noexcept { return static_cast<ParentType&>(*this); }

    /// Downcasts this instance to a read-only instance of the derived class
    const ParentType& downcast_() const noexcept;
}; // class InputIteratorBase

// ------------------------------Implementations--------------------------------

template<typename ParentType>
ParentType InputIteratorBase<ParentType>::operator++(int) {
    ParentType copy_of_me(downcast_());
    ++(*this);
    return copy_of_me;
}

template<typename ParentType>
bool InputIteratorBase<ParentType>::operator==(
  const ParentType& rhs) const noexcept {
    return downcast_().are_equal(rhs);
}

template<typename ParentType>
bool InputIteratorBase<ParentType>::operator!=(
  const ParentType& rhs) const noexcept {
    return !((*this) == rhs);
}

template<typename ParentType>
const ParentType& InputIteratorBase<ParentType>::downcast_() const noexcept {
    return static_cast<const ParentType&>(*this);
}

} // namespace utilities::iterators
