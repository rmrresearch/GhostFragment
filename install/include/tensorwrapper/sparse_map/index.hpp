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
#include <algorithm> // lexicographic_compare
#include <iostream>
#include <vector>

namespace tensorwrapper::sparse_map {

namespace detail_ {
/// Type used to disable an overload when @p T is integral
template<typename T>
using disable_if_integral_t = std::enable_if_t<!std::is_integral_v<T>>;
} // namespace detail_

/** @brief Thin wrapper class around a multi-rank index.
 *
 *  This class basically dresses an std::vector of integers in a new type so
 *  that it can be used for strong typing. Users are expected to work directly
 *  with the wrapped vector, which is accessible via the `m_index` member
 */
struct Index {
    /// Type used for sizes
    using size_type = std::size_t;

    /// Type used for the mult-rank index
    using index_type = std::vector<size_type>;

    /// Type used for offsets of the index
    using value_type = size_type;

    /** @brief Creates an empty/rank 0 index.
     *
     *  @throw None no throw guarantee.
     */
    Index() = default;

    /** @brief Takes one or more integers and creates an Index instance with
     *         offsets given by the provided integers.
     *
     *  This ctor is used to create a rank @f$N@f$ index (@f$N > 0@f$).
     *  Providing no indices will trigger the default constructor and result in
     *  a rank 0 index as intended.
     *
     *  @tparam Args The types of second plus
     *
     *  @param[in] i0 The offset of the index along the 0-th mode.
     *  @param[in] args The offset of the index along the remaining modes.
     *
     *  @throw std::bad_alloc if there is insufficient memory to create the
     *                        indice's state. Strong throw guarantee.
     */
    template<typename... Args>
    explicit Index(size_type i0, Args&&... args);

    /** @brief Creates a new instance using the provided initializer list.
     *
     *  @param[in] il An @f$N@f$-element initializer list such that the
     *                @f$i@f$-th element is the instance's offset along the
     *                @f$i@f$-th mode of the tensor.
     *
     *  @throw std::bad_alloc if there is insufficient memory to create the
     *                         indice's state. Strong throw guarantee.
     */
    Index(std::initializer_list<size_type> il) : Index(index_type(il)) {}

    /** @brief Creates a new instance using the provided index_type instance.
     *
     *  This ctor can be used to create a new Index instance by providing an
     *  existing `index_type` instance.
     *
     *  @param[in] i The index_type instance the newly created Index instance
     *               should wrap.
     *
     *  @throw None no throw guarantee.it
     */
    explicit Index(index_type i) : m_index(std::move(i)) {}

    /** @brief Constructs a new Index from the range [b, e)
     *
     *  This ctor can be used to create a new Index instance by providing two
     *  iterators, one which points to the first element to add to the index and
     *  one which points to just past the last element of the index.
     *
     * @tparam BeginItr Type of the iterator pointing to the first element of
     *                  the index.
     * @tparam EndItr Type of the iterator pointing to just past the last
     *                element of the index.
     * @tparam (Anonymous) Used to disable this ctor by means of SFINAE if
     *                     `BeginItr` is an integral type.
     *
     * @param[in] b An iterator pointing to the first element of the index.
     * @param[in] e An iterator pointing to just past the last element of the
     *              index.
     *
     * @throw std::bad_alloc if the index_type's range ctor throws. Strong throw
     *                       guarantee.
     */
    template<typename BeginItr, typename EndItr,
             typename = detail_::disable_if_integral_t<BeginItr>>
    Index(BeginItr&& b, EndItr&& e);

    /** @brief Returns the size/number of modes in this Index instance
     *
     *  At the moment this is just a convenience function for calling
     *  `this->m_index.size()`.
     *
     *  @return The number of elements in
     */
    auto size() const { return m_index.size(); }

    /** @brief Returns the offset along the specified mode.
     *
     *  @param[in] i Which mode's offset do we want
     *
     *  @return The offset along mode @p i.
     *
     *  @throw std::out_of_range if @p i is not in the range [0, size()). Strong
     *                           throw guarantee.
     */
    auto operator[](size_type i) const { return m_index.at(i); }

    /** @brief Returns an iterator pointing to the first component of the index.
     *
     *  @return A bidirectional iterator pointing the first component of the
     *          index.
     */
    auto begin() { return m_index.begin(); }

    /** @brief Returns an iterator pointing to the first component of the index.
     *
     *  @return A bidirectional iterator pointing to the first component
     *          of the index. The index's components are read-only when accessed
     *          through this iterator.
     */
    auto begin() const { return m_index.begin(); }

    /** @brief Returns an iterator pointing to just past the last component of
     *         the index.
     *
     *  @return An iterator pointing to just past the last component of the
     *          index.
     */
    auto end() { return m_index.end(); }

    /** @brief Returns an iterator pointing to just past the last component of
     *         the index.
     *
     *  @return An iterator pointing to just past the last component of the
     *          index.
     */
    auto end() const { return m_index.end(); }

    /** @brief Prints the Index to the provided std::ostream
     *
     *  @param[in, out] os The stream to print this Index instance to. After the
     *                     call a string representation of this instance will
     *                     have been added to @p os.
     *  @return @p os is returned to support chaining.
     */
    std::ostream& print(std::ostream& os) const;

    /// The actual index
    index_type m_index;
}; // class Index

/** @brief Compares two Index instances for equality.
 *
 *  Two index instances are considered equivalent if the index_type instances
 *  they wrap are equivalent.
 *
 *  @param[in] lhs The instance on the LHS of the operator.
 *  @param[in] rhs The instance on the RHS of the operator.
 *
 *  @return True if @p lhs compares equal to @p rhs and false otherwise.
 *
 *  @throw None No throw guarantee.
 */
inline bool operator==(const Index& lhs, const Index& rhs) {
    return lhs.m_index == rhs.m_index;
}

/** @brief Compares two Index instances for inequality.
 *
 *  Two index instances are considered equivalent if the index_type instances
 *  they wrap are equivalent.
 *
 *  @param[in] lhs The instance on the LHS of the operator.
 *  @param[in] rhs The instance on the RHS of the operator.
 *
 *  @return True if @p lhs compares different to @p rhs and false otherwise.
 *
 *  @throw None No throw guarantee.
 */
inline bool operator!=(const Index& lhs, const Index& rhs) {
    return !(lhs == rhs);
}

inline bool operator<(const Index& lhs, const Index& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end());
}

inline bool operator>(const Index& lhs, const Index& rhs) {
    return !(lhs == rhs) and !(lhs < rhs);
}

inline bool operator<=(const Index& lhs, const Index& rhs) {
    return (lhs == rhs) or (lhs < rhs);
}

inline bool operator>=(const Index& lhs, const Index& rhs) {
    return !(lhs < rhs);
}

/** @brief Compares an Index instance to a vector.
 *  @relates Index
 *
 *  This is a convenience function for comparing an Index to an std::vector.
 *  The comparison simply checks if the std::vector internal to the Index
 *  comapres equal.
 *
 *  @tparam T The type of the elements in the vector. Assumed to be integral.
 *
 *  @param[in] i The Index instance on the LHS of the operator.
 *  @param[in] v The std::vector instance on the RHS of the operator.
 *
 *  @return True if the std::vector internal to @p i compares true to @p v and
 *          false otherwise.
 *
 *  @throw None No throw guarantee.
 */
template<typename T>
bool operator==(const Index& i, const std::vector<T>& v) {
    return i.m_index == v;
}

/** @brief Compares an Index instance to a vector.
 *  @relates Index
 *
 *  This is a convenience function for comparing an Index to an std::vector.
 *  The comparison simply checks if the std::vector internal to the Index
 *  comapres equal.
 *
 *  @tparam T The type of the elements in the vector. Assumed to be integral.
 *
 *  @param[in] v The std::vector instance on the LHS of the operator.
 *  @param[in] i The Index instance on the RHS of the operator.
 *
 *  @return True if the std::vector internal to @p i compares true to @p v and
 *          false otherwise.
 *
 *  @throw None No throw guarantee.
 */
template<typename T>
bool operator==(const std::vector<T>& v, const Index& i) {
    return i == v;
}

/** @brief Compares an Index instance to a vector.
 *  @relates Index
 *
 *  This is a convenience function for comparing an Index to an std::vector.
 *  The comparison simply checks if the std::vector internal to the Index
 *  comapres different.
 *
 *  @tparam T The type of the elements in the vector. Assumed to be integral.
 *
 *  @param[in] i The Index instance on the LHS of the operator.
 *  @param[in] v The std::vector instance on the RHS of the operator.
 *
 *  @return True if the std::vector internal to @p i compares different to @p v
 *          and false otherwise.
 *
 *  @throw None No throw guarantee.
 */
template<typename T>
bool operator!=(const Index& i, const std::vector<T>& v) {
    return i.m_index != v;
}

/** @brief Compares an Index instance to a vector.
 *  @relates Index
 *
 *  This is a convenience function for comparing an Index to an std::vector.
 *  The comparison simply checks if the std::vector internal to the Index
 *  comapres different.
 *
 *  @tparam T The type of the elements in the vector. Assumed to be integral.
 *
 *  @param[in] v The std::vector instance on the LHS of the operator.
 *  @param[in] i The Index instance on the RHS of the operator.
 *
 *  @return True if the std::vector internal to @p i compares different to @p v
 *          and false otherwise.
 *
 *  @throw None No throw guarantee.
 */
template<typename T>
bool operator!=(const std::vector<T>& v, const Index& i) {
    return i != v;
}

/** @brief Allows an Index to be printed to an std::ostream.
 *  @relates Index
 *
 *  @param[in,out] os The stream to which @p idx will be printed. After this
 *                    operation @p os will contain the string representation of
 *                    @p idx.
 *  @param[in] idx    The Index instance to print.
 *
 *  @return @p os containing the string representation of @p idx. @p os is
 *          returned in order to support chaining.
 */
inline std::ostream& operator<<(std::ostream& os, const Index& idx) {
    return idx.print(os);
}

//------------------------------------------------------------------------------
//                            Implementations
//------------------------------------------------------------------------------

template<typename... Args>
Index::Index(size_type i0, Args&&... args) :
  Index({i0, size_type(std::forward<Args>(args))...}) {}

template<typename BeginItr, typename EndItr, typename>
Index::Index(BeginItr&& b, EndItr&& e) :
  Index(index_type(std::forward<BeginItr>(b), std::forward<EndItr>(e))) {}

inline std::ostream& Index::print(std::ostream& os) const {
    os << "{";
    for(std::size_t i = 0; i < m_index.size(); ++i) {
        os << m_index[i];
        if(i != m_index.size() - 1) os << ", ";
    }
    return os << "}";
}

} // namespace tensorwrapper::sparse_map
