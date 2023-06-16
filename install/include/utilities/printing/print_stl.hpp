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
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <optional>
#include <ostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/** @file print_stl.hpp
 *
 *  This file overloads the std::ostream& operator<<(std::ostream& os, T) for
 *  types T in the STL. This header file does **NOT** include any of the STL
 *  header files, but rather forward declares them all. It is you responsibility
 *  to include the header files for the classes you use.
 *
 *  When appropriate, containers are printed like their Python analogs.
 */
namespace utilities::printing {

namespace detail_ {

template<typename T>
std::ostream& print_element(std::ostream& os, T&& value);

/** @brief Implements printing of queue-like containers
 *
 *  Queue like containers only allow you to view the elements that are in the
 *  front of the queue or on top of the stack. Hence this function iterates
 *  over the container by getting the first element from a functor (used to
 *  abstract away the fact that different containers have different accessors
 *  for this element), popping that element off, and repeating until the
 *  container is empty. It's consequentially a good idea to use a copy of the
 *  original container.
 *
 * @tparam T The type of the queue-like container we are printing.
 * @tparam Fxn The functor which returns the first element in the queue given
 *             the queue.
 * @param[in] os The stream to print to.
 * @param[in] f The functor to use for retrieving elements
 * @param[in] rhs The container to print. The contents of which will be
 *                destroyed.
 * @return @p os containing @p rhs.
 *
 * @throw ??? if std::ostream<< throws. Same guarantee.
 */
template<typename T, typename Fxn>
std::ostream& print_queue(std::ostream& os, Fxn&& f, T&& rhs);

/** @brief Prints a list-like container.
 *
 *  List like containers only need to print the elements. This should be
 *  contrasted with associative containers, which need to print a key and a
 *  value.
 *
 * @tparam T The type of the container that is being printed.
 *
 * @param[in] os The std::ostream to print the container to.
 * @param[in] rhs The container to print to the stream.
 * @param[in] open_delim The character to use to denote the start of the
 *            container.  Default is `[`.
 * @param[in] close_delim The character to use to denote the end of the
 *            container. Default is `]`.
 * @return @p os containing @p rhs.
 *
 * @throw ??? if std::ostream<< throws. Same guarantee.
 */
template<typename T>
std::ostream& print_list(std::ostream& os, T&& rhs, char odelim = '[',
                         char cdelim = ']');

/** @brief Prints an associative container.
 *
 *  Associative containers need to print key, value pairs. This should be
 *  contrasted with list-like containers, which only need to print the values.
 *
 * @tparam T The type of the container that is being printed.
 *
 * @param[in] os The std::ostream to print the container to.
 * @param[in] rhs The container to print to the stream.
 * @param[in] open_delim The character to use to denote the start of the
 *            container. Default is `{`.
 * @param[in] close_delim The character to use to denote the end of the
 *            container. Default is `}`
 * @return @p os containing @p rhs.
 *
 * @throw ??? if std::ostream<< throws. Same guarantee.
 */
template<typename T>
std::ostream& print_associative(std::ostream& os, T&& rhs, char odelim = '{',
                                char cdelim = '}');

/** @brief Function for printing tuple/pairs
 *
 *  Tuples don't support iteration, consequentially this function works by
 *  recursion. At a recursive depth of @p depth this function adds the @p depth
 *  -th element to stream and then forwards the stream and arguments to the
 *  next recursive call. Recursion stops when we've looped over the entire
 *  tuple.
 *
 * @tparam depth How deep in the recursion stack are we?
 * @tparam T The type of the tuple.
 *
 * @param[in] os The stream to print @p rhs to.
 * @param[in] rhs The tuple to print out. Each element of @p rhs must be
 *                printable.
 * @param[in] odelim The character to use for delimiting the beginning of the
 *                   tuple. Defaults to `(`.
 * @param[in] cdelim The character to use for denoting the end of the tuple.
 *                   Defaults to `)`.
 *
 * @return @p os containing @p rhs.
 *
 * @throw ??? if std::ostream<< throws. Same guarantee.
 */
template<std::size_t depth, typename T>
std::ostream& print_tuple(std::ostream& os, T&& rhs, char odelim = '(',
                          char cdelim = ')');

} // namespace detail_

// Stuff below hwere is just boiler-plate for calling the above functions for
// ever class in the STL

/** @brief Makes std::array printable.
 *
 *  @tparam T The type of the element stored in the array.
 *  @tparam N The number of elements stored in the array.
 *
 *  @param[in] os The std::ostream to print the array to.
 *  @param[in] a The array to print. Elements of the array must be printable.
 *
 *  @return @p os modified to contain @p a.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& a);

/** @brief Makes std::deque printable.
 *
 * @tparam T The type of the element stored in the deque.
 * @tparam Alloc The type of the deque's allocator.
 *
 * @param[in] os The std::ostream to print to.
 * @param[in] d  The deque to print. Elements of the deque must be printable.
 *
 *  @return @p os modified to contain @p a.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& os, const std::deque<T, Alloc>& d);

/** @brief Makes std::forward_list printable.
 *
 * @tparam T The type of the element stored in the forward_list.
 * @tparam Alloc The type of the forward_list's allocator.
 *
 * @param[in] os The std::ostream to print to.
 * @param[in] f  The forward_list to print. Elements of the forward_list must be
 *               printable.
 *
 *  @return @p os modified to contain @p f.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::forward_list<T, Alloc>& f);

/** @brief Makes std::list printable.
 *
 * @tparam T The type of the element stored in the list.
 * @tparam Alloc The type of the list's allocator.
 *
 * @param[in] os The std::ostream to print to.
 * @param[in] l  The list to print. Elements of the list must be printable.
 *
 *  @return @p os modified to contain @p l.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
// template <typename T, typename Alloc>
// std::ostream &operator<<(std::ostream &os, const std::list<T, Alloc> &l) {
//  return utilities::printing::detail_::print_list(os, l);
//}

/** @brief Makes std::map printable.
 *
 *  @tparam Key The type of the keys in the map
 *  @tparam T The type of the value stored in the map.
 *  @tparam Compare The type of the functor used for comparing keys.
 *  @tparam Alloc The type of the map's allocator.
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] m  The map to print. Keys and values of the map must be
 *                printable.
 *
 *  @return @p os modified to contain @p m.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename Key, typename T, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::map<Key, T, Compare, Alloc>& m);

/** @brief Makes std::multimap printable.
 *
 *  @tparam Key The type of the keys in the multimap
 *  @tparam T The type of the value stored in the multimap.
 *  @tparam Compare The type of the functor used for comparing keys.
 *  @tparam Alloc The type of the multimap's allocator.
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] m  The multimap to print. Keys and values of the multimap must be
 *                printable.
 *
 *  @return @p os modified to contain @p m.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename Key, typename T, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::multimap<Key, T, Compare, Alloc>& m);

/** @brief Makes std::multiset printable.
 *
 *  @tparam T The type of the values stored in the multiset
 *  @tparam Compare The functor to use for ordering elements.
 *  @tparam Alloc The allocator for the set
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] s  The multiset to print. Values in the multiset must be
 *                printable.
 *
 *  @return @p os modified to contain @p s.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::multiset<T, Compare, Alloc>& s);

/** @brief Makes std::optional printable
 *
 *  @tparam T The type of the value inside the optional
 *
 *  @param[in] os The stream to print the optional to.
 *  @param[in] o The optional to print. If it holds a value, the value must be
 *               printable; if it does not hold a value "nullopt" will be
 *               printed.
 *
 * @return @p os containing @p o
 *
 * @throw ??? if std::ostream::operator<< throws. Same guarantee.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<T>& o);

/** @brief Makes std::pair printable.
 *
 *  @tparam T1 The type of the first value stored in the pair
 *  @tparam T2 The type of the second value stored in the pair
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] p  The pair to print. Values in the pair must be printable.
 *
 *  @return @p os modified to contain @p p.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p);

/** @brief Makes std::priority_queue printable.
 *
 *  @tparam T The type of the values stored in the priority_queue.
 *  @tparam Container The type of the container the priority_queue is built
 *                    around.
 *  @tparam Compare The functor to use for comparing priorities.
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] q  The priority_queue to print. Values in the priorty_queue must
 *                be printable.
 *
 *  @return @p os modified to contain @p q.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T, typename Container, typename Compare>
std::ostream& operator<<(std::ostream& os,
                         std::priority_queue<T, Container, Compare> q);

/** @brief Makes std::queue printable.
 *
 *  @tparam T The type of the values stored in the queue.
 *  @tparam Container The type of the container the queue is built around
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] q  The queue to print. Values in the queue must be printable.
 *
 *  @return @p os modified to contain @p q.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T, typename Container>
std::ostream& operator<<(std::ostream& os, std::queue<T, Container> q);

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::reference_wrapper<T>& r);

/** @brief Makes std::set printable.
 *
 *  @tparam T The type of the values stored in the set
 *  @tparam Compare The functor to use for ordering elements.
 *  @tparam Alloc The allocator for the set
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] s  The set to print. Values in the set must be printable.
 *
 *  @return @p os modified to contain @p s.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::set<T, Compare, Alloc>& s);

/** @brief Makes std::stack printable.
 *
 *  @tparam T The type of the values stored in the stack.
 *  @tparam Container The type of the container the stack is built around
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] s  The stack to print. Values in the stack must be printable.
 *
 *  @return @p os modified to contain @p s.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T, typename Container>
std::ostream& operator<<(std::ostream& os, std::stack<T, Container> s);

/** @brief Makes std::tuple printable.
 *
 *  @tparam Types The types in the tuple
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] t  The tuple to print. Values in the tuple must be printable.
 *
 *  @return @p os modified to contain @p t.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename... Types>
std::ostream& operator<<(std::ostream& os, const std::tuple<Types...>& t);

/** @brief Makes std::unordered_map printable.
 *
 *  @tparam Key The type of the keys in the unordered_map
 *  @tparam T The type of the value stored in the unordered_map.
 *  @tparam Hash The type of the hash functor
 *  @tparam Pred The type of the functor used for comparing hashes.
 *  @tparam Alloc The type of the unordered_map's allocator.
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] m  The unordered_map to print. Keys and values of the
 *                unordered_map must be printable.
 *
 *  @return @p os modified to contain @p m.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename Key, typename T, typename Hash, typename Pred, typename Alloc>
std::ostream& operator<<(
  std::ostream& os, const std::unordered_map<Key, T, Hash, Pred, Alloc>& m);

/** @brief Makes std::unordered_multimap printable.
 *
 *  @tparam Key The type of the keys in the unordered_multimap
 *  @tparam T The type of the value stored in the unordered_multimap.
 *  @tparam Hash The type of the hash functor
 *  @tparam Pred The type of the functor used for comparing hashes.
 *  @tparam Alloc The type of the unordered_multimap's allocator.
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] m  The unordered_multimap to print. Keys and values of the
 *                unordered_multimap must be printable.
 *
 *  @return @p os modified to contain @p m.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename Key, typename T, typename Hash, typename Pred, typename Alloc>
std::ostream& operator<<(
  std::ostream& os,
  const std::unordered_multimap<Key, T, Hash, Pred, Alloc>& m);

/** @brief Makes std::unordered_multiset printable.
 *
 *  @tparam Key The type of the elements in the unordered_multiset
 *  @tparam Hash The type of the hash functor
 *  @tparam Pred The type of the functor used for comparing hashes.
 *  @tparam Alloc The type of the allocator.
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] s  The unordered_multiset to print. Keys of the
 *                unordered_multiset must be printable.
 *
 *  @return @p os modified to contain @p s.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename Key, typename Hash, typename Pred, typename Alloc>
std::ostream& operator<<(
  std::ostream& os, const std::unordered_multiset<Key, Hash, Pred, Alloc>& s);

/** @brief Makes std::unordered_set printable.
 *
 *  @tparam Key The type of the elements in the unordered_set
 *  @tparam Hash The type of the hash functor
 *  @tparam Pred The type of the functor used for comparing hashes.
 *  @tparam Alloc The type of the allocator.
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] s  The unordered_set to print. Keys of the unordered_set must be
 *                printable.
 *
 *  @return @p os modified to contain @p s.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename Key, typename Hash, typename Pred, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::unordered_set<Key, Hash, Pred, Alloc>& s);

/** @brief Makes std::vector printable.
 *
 *  @tparam T The type of the elments in the vector
 *  @tparam Alloc The type of the allocator.
 *
 *  @param[in] os The std::ostream to print to.
 *  @param[in] v  The vector to print. Elements of the vector must be
 *                printable.
 *
 *  @return @p os modified to contain @p v.
 *
 *  @throw ??? if the ostream's operator<< throws. Same exception guarantee.
 */
template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& os, const std::vector<T, Alloc>& v);

} // namespace utilities::printing

#include "utilities/printing/print_stl.ipp"
