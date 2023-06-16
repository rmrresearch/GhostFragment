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
#include "utilities/iterators/input_iterator_base.hpp"

namespace utilities::iterators {

/** @brief This class is designed to facilitate making your own bidirectional
 *         iterator class.
 *
 *  When making your own iterator there's a lot of boiler plate involved.  This
 *  class factors out as much boiler plate as possible for a bidirectional
 *  iterator, which is an iterator that allows you to access either the next
 *  element or the previous element.
 *
 *  To use this class your derived class needs to implement the functions for
 *  the InputIteratorBase class:
 *  - `ParentType& increment()`
 *  - `const_reference dereference()const`
 *  - `reference dereference()`
 *  - `bool are_equal(const ParentType&) const noexcept`
 *
 *  As well as:
 *  - `ParentType& decrement()` - which should decrement the element pointed at
 *    by one and return `*this`. This function can throw if it wants.
 *
 *  @tparam ParentType The type of iterator that you are making.
 */
template<typename ParentType>
struct BidirectionalIteratorBase : public InputIteratorBase<ParentType> {
    /// The category of iterator that this iterator satisfies
    using iterator_category = std::bidirectional_iterator_tag;

    /** @brief Returns this iterator pointing to the previous element
     *
     *  This operator will make the current iterator point to the previous
     *  element and then return the current instance. This function ultimately
     *  works by calling the derived class's `decrement()` member.
     *
     *  @returns The current iterator after decrementing the element it points
     *           to by one.
     *
     *  @throws ??? This function will throw if `decrement()` throws. Same
     *          throw guarantee as the `decrement()`.
     */
    ParentType& operator--() { return this->downcast_().decrement(); }

    /** @brief Decrements the current iterator after returning the value.
     *
     *  Semantically this operator returns the current iterator, pointing to its
     *  current value and then decrements the value it points to by 1. In
     *  practice this function actually copies the current instance, decrements
     *  the current, non-copy, instance, and returns the copy. This function
     *  ultimately works by calling the derived class's `decrement()` member and
     *  its copy constructor.
     *
     *  @returns A copy of the current iterator before it was decremented.
     *
     *  @throws ??? If either the copy constructor or the derived class's
     *              `decrement()` function throw. Same throw guarantee.
     */
    ParentType operator--(int);
}; // class BidirectionalIteratorBase

// ------------------------------------Implementations--------------------------

template<typename ParentType>
ParentType BidirectionalIteratorBase<ParentType>::operator--(int) {
    ParentType copy_of_me(this->downcast_());
    --(*this);
    return copy_of_me;
}

} // namespace utilities::iterators
