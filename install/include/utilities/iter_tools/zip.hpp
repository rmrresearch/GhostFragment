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
#include <algorithm>
#include <array>

namespace utilities {

/** @brief A container filled with elements resulting from zipping containers
 *         together.
 *
 *  This class simulates a container filled with tuples such that the i-th
 *  tuple is comprised of the i-th element of each container. More concretely,
 *  given three containers `A, B, C`, and a Zip instance `Zip z(A,B,C)`, the
 *  i-th element in `z` is `std::tuple{A[i], B[i], C[i]}`. If the zipped
 *  containers do not have the same size, then this container sores n tuples,
 *  where n is the length of the shortest container. This class does not
 *  actually store all tuples, but rather generates them on-the-fly.
 *
 *  @note It is strongly recommended that you let this class figure out its type
 *        like `Zip(container1, container2)` rather than trying to manually
 *        specify it like `Zip<std::vector<int>, std::set<double>>`. In addition
 *        to the latter being very verbose, it will also result in an
 *        inefficient container (it will copy the containers); the template
 *        deduction rules for this container have been set-up so that it should
 *        do the right thing in each situation.
 *
 *  @tparam Containers The types of the containers. Types should be fully
 *                     cv-qualified references to containers.
 */
template<typename... Containers>
class Zip : public IndexableContainerBase<Zip<Containers...>> {
private:
    /// Type of this instance
    using my_type = Zip<Containers...>;
    /// Type of the base class
    using base_type = IndexableContainerBase<my_type>;

public:
    /// Type of an element in this container
    using value_type =
      std::tuple<typename std::remove_reference_t<Containers>::value_type...>;
    /// Type used for indexing/offsets, is an unsigned integral POD type
    using size_type = typename base_type::size_type;

    /** @brief Constructs a new Zip instance by zipping together the provided
     *         containers.
     *
     *  This ctor will create a new Zip instance which stores a copy of each
     *  container passed by value, a read-/write- reference to each container
     *  passed by reference, and a read-only reference to each constant
     *  container passed by reference. The resulting instance will have n
     *  elements where n is the shortest length among the zipped together
     *  containers.
     *
     * @param[in] containers The containers to zip together.
     *
     * @throw ??? If copying the containers, or calling each container's begin
     *            member throws. Same throw guarantee.
     */
    explicit Zip(Containers... containers);

private:
    /// Ensures IndexableContainerBase can access implementation
    friend base_type;

    /// Helper function for calling begin on an arbitrary number of containers
    template<typename... Args>
    static decltype(auto) call_begin_(Args&&... args) {
        return std::make_tuple(args.begin()...);
    }

    /// Type of a tuple filled with iterators to the containers
    using begin_itr_type =
      decltype(my_type::call_begin_(std::declval<Containers>()...));

    /// Implements size() for IndexableContainerBase
    size_type size_() const noexcept { return m_size_; }
    /// Implements operator[] for IndexableContainerBase
    decltype(auto) at_(size_type i) const;

    /// Tuple containing containers provided to this class
    std::tuple<Containers...> m_values_;
    /// Tuple of iterators such that m_begin_[i] == m_values_[i].begin()
    begin_itr_type m_begin_;
    /// The total number of iterations stored in this container
    size_type m_size_;
}; // class Zip

// ---------------------------Implementations----------------------------------
template<typename... Args>
Zip(Args&&...) -> Zip<Args...>;

template<typename... Containers>
Zip<Containers...>::Zip(Containers... containers) :
  m_values_(containers...),
  m_begin_(std::apply(
    [](auto&&... args) {
        return call_begin_(std::forward<decltype(args)>(args)...);
    },
    m_values_)),
  m_size_([&]() {
      std::array<std::size_t, sizeof...(Containers)> sizes{
        containers.size()...};
      return *std::min_element(sizes.begin(), sizes.end());
  }()) {}

template<typename... Containers>
decltype(auto) Zip<Containers...>::at_(size_type index) const {
    begin_itr_type copy_begin(m_begin_);
    return std::apply(
      [=](auto&&... args) {
          (std::advance(args, index), ...);
          return std::tuple<decltype(*args)...>(*args...);
      },
      copy_begin);
}

} // namespace utilities
