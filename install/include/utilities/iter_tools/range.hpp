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
#include "utilities/containers/indexable_container_base.hpp"

namespace utilities {

/** @brief Container that holds a range of integers
 *
 *  This container simulates a container filled with all integers in a given
 *  range. The container does not actually hold the integers, but rather
 *  generates them on-the-fly. This container supports looping over ranges in
 *  increments other than unity and also supports decreasing ranges (ranges for
 *  which the initial value is greater than the ending value).
 *
 *  @tparam ElementType The type of integers stored in this container. Expected
 *                      to be an integral POD type.
 */
template<typename ElementType>
class Range : public IndexableContainerBase<Range<ElementType>> {
private:
    /// Type of this instance
    using my_type = Range<ElementType>;
    /// Type of the base class
    using base_type = IndexableContainerBase<my_type>;

public:
    /// Type of the integers held in this container
    using value_type = ElementType;
    /// Type used for indexing and offsets, is an unsigned integral POD type
    using size_type = typename base_type::size_type;
    /// Type describing the difference in two integers, signed integral POD type
    using difference_type = long int;

    /** @brief Constructs a range that holds the values [0, range_end)
     *
     *  This ctor creates a new Range instance that simulates holding all of the
     *  integer values between 0 and @p range_end. Values are actually computed
     *  on-the-fly.
     *
     *  @param[in] range_end The first integer outside the range.
     *
     *  @throw None No throw guarantee.
     */
    explicit Range(ElementType range_end) noexcept : Range(0, range_end, 1) {}

    /** @brief Constructs a Range that holds the values [range_begin, range_end)
     *         in increments of @p inc.
     *
     *  This ctor creates a new Range instance that simulates holding all of the
     *  integer values between @p range_begin and @p range_end that can be
     *  obtained by incrementing (decrementing) @p range_begin in increments of
     *  @p inc. Values are actually computed on-the-fly.
     *
     *  @warning @p inc is an unsigned quantity,even if
     *           @p range_begin > @p range_end. For example to generate the
     *           range `10, 8, 6, 4, 2, 0` the code is `Range(10, -1, 2)` NOT
     *           `Range(10, -1, -2)`. The latter will likely compile, but will
     *           actually give you a range with one value in it, 10, as the
     *           increment will be set to the maximum unsigned integer value.
     *
     *  @param[in] range_begin The first integer inside the range.
     *  @param[in] range_end The first integer outside the range.
     *  @param[in] inc The absolute value of the difference between elements in
     *                 the range.
     *
     *  @throw None No throw guarantee.
     */
    Range(ElementType range_begin, ElementType range_end,
          size_type inc = 1) noexcept;

private:
    /// Allows IndexableContainerBase to access the implementation functions
    friend base_type;
    /// Implements `size()` for IndexableContainerBase
    size_type size_() const noexcept { return m_size_; }
    /// Implements `operator[]` for IndexableContainerBase
    ElementType at_(size_type i) const noexcept;

    /// The first index in the range
    ElementType m_start_;
    /// The number of indices in the range
    ElementType m_size_;
    /// The quantity to add to m_start_ to get the second index in the range
    difference_type m_inc_;
}; // class Range

// ---------------------------------Implementations-----------------------------

template<typename ElementType>
Range<ElementType>::Range(ElementType range_begin, ElementType range_end,
                          size_type inc) noexcept :
  m_start_(range_begin),
  m_size_([=]() {
      const auto lesser    = std::min(range_begin, range_end);
      const auto higher    = std::max(range_begin, range_end);
      const auto remainder = (higher - lesser) % inc;
      return (higher - lesser - remainder) / inc + (remainder > 0);
  }()),
  m_inc_(range_begin <= range_end ? inc : -1 * inc) {
    static_assert(std::is_integral_v<ElementType>,
                  "T for Range<T> must be an integral type.");
}

template<typename ElementType>
ElementType Range<ElementType>::at_(size_type i) const noexcept {
    return m_start_ + i * m_inc_;
}

} // namespace utilities
