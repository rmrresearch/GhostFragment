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
#include "utilities/printing/print_stl.hpp"

#include "utilities/type_traits/is_printable.hpp"

/** @file print_stl.ipp
 *
 *  The new operator<< functions need to be declared before
 *  type_traits::is_printable is checked. The implementation of those functions
 *  is then handled here.
 *
 */
namespace utilities::printing {

namespace detail_ {

template<typename T>
std::ostream& print_element(std::ostream& os, T&& value) {
    using clean_T = std::decay_t<T>;
    if constexpr(type_traits::is_printable_v<clean_T>) {
        return os << std::forward<T>(value);
    } else {
        return os << "<" << typeid(clean_T).name() << " " << &value << ">";
    }
}

template<typename T, typename Fxn>
std::ostream& print_queue(std::ostream& os, Fxn&& f, T&& rhs) {
    os << '[';
    bool printed = false;
    while(!rhs.empty()) {
        if(printed) os << ", ";
        print_element(os, f(rhs));
        rhs.pop();
        printed = true;
    }
    return os << ']';
}

template<typename T>
std::ostream& print_list(std::ostream& os, T&& rhs, char odelim, char cdelim) {
    os << odelim;
    bool printed = false;
    for(const auto& x : rhs) {
        using x_type = decltype(x);
        if(printed) os << ", ";
        print_element(os, x);
        printed = true;
    }
    return os << cdelim;
}

template<typename T>
std::ostream& print_associative(std::ostream& os, T&& rhs, char odelim,
                                char cdelim) {
    os << odelim;
    bool printed = false;
    for(const auto& x : rhs) {
        using x_type = decltype(x);
        if(printed) os << ", ";
        os << "(";
        print_element(os, x.first) << " : ";
        print_element(os, x.second) << ")";
        printed = true;
    }
    return os << cdelim;
}

template<std::size_t depth, typename T>
std::ostream& print_tuple(std::ostream& os, T&& rhs, char odelim, char cdelim) {
    constexpr auto max_depth = std::tuple_size_v<std::decay_t<T>>;
    if constexpr(depth == max_depth && depth == 0) {
        return os << odelim << cdelim;
    } else if constexpr(depth == max_depth) {
        return os << cdelim;
    } else if constexpr(depth == 0) {
        os << odelim;
        print_element(os, std::get<0>(rhs));
        return print_tuple<depth + 1>(os, std::forward<T>(rhs), odelim, cdelim);
    } else {
        os << ", ";
        print_element(os, std::get<depth>(rhs));
        return print_tuple<depth + 1>(os, std::forward<T>(rhs), odelim, cdelim);
    }
}

} // namespace detail_

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& a) {
    return utilities::printing::detail_::print_list(os, a);
}

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& os, const std::deque<T, Alloc>& d) {
    return utilities::printing::detail_::print_list(os, d);
}

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::forward_list<T, Alloc>& f) {
    return utilities::printing::detail_::print_list(os, f);
}

template<typename Key, typename T, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::map<Key, T, Compare, Alloc>& m) {
    return utilities::printing::detail_::print_associative(os, m);
}

template<typename Key, typename T, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::multimap<Key, T, Compare, Alloc>& m) {
    return utilities::printing::detail_::print_associative(os, m);
}

template<typename T, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::multiset<T, Compare, Alloc>& s) {
    return utilities::printing::detail_::print_list(os, s, '{', '}');
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<T>& o) {
    if(o.has_value())
        utilities::printing::detail_::print_element(os, o.value());
    else
        os << "nullopt";
    return os;
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    return utilities::printing::detail_::print_tuple<0>(os, p);
}

template<typename T, typename Container, typename Compare>
std::ostream& operator<<(std::ostream& os,
                         std::priority_queue<T, Container, Compare> q) {
    auto l = [](const decltype(q)& q) { return q.top(); };
    return utilities::printing::detail_::print_queue(os, l, std::move(q));
}

template<typename T, typename Container>
std::ostream& operator<<(std::ostream& os, std::queue<T, Container> q) {
    auto l = [](const decltype(q)& q) { return q.front(); };
    return utilities::printing::detail_::print_queue(os, l, std::move(q));
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::reference_wrapper<T>& r) {
    return utilities::printing::detail_::print_element(os, r.get());
}

template<typename T, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::set<T, Compare, Alloc>& s) {
    return utilities::printing::detail_::print_list(os, s, '{', '}');
}

template<typename T, typename Container>
std::ostream& operator<<(std::ostream& os, std::stack<T, Container> s) {
    auto l = [](const decltype(s)& s) { return s.top(); };
    return utilities::printing::detail_::print_queue(os, l, std::move(s));
}

template<typename... Types>
std::ostream& operator<<(std::ostream& os, const std::tuple<Types...>& t) {
    return utilities::printing::detail_::print_tuple<0>(os, t);
}

template<typename Key, typename T, typename Hash, typename Pred, typename Alloc>
std::ostream& operator<<(
  std::ostream& os, const std::unordered_map<Key, T, Hash, Pred, Alloc>& m) {
    return utilities::printing::detail_::print_associative(os, m);
}

template<typename Key, typename T, typename Hash, typename Pred, typename Alloc>
std::ostream& operator<<(
  std::ostream& os,
  const std::unordered_multimap<Key, T, Hash, Pred, Alloc>& m) {
    return utilities::printing::detail_::print_associative(os, m);
}

template<typename Key, typename Hash, typename Pred, typename Alloc>
std::ostream& operator<<(
  std::ostream& os, const std::unordered_multiset<Key, Hash, Pred, Alloc>& s) {
    return utilities::printing::detail_::print_list(os, s, '{', '}');
}

template<typename Key, typename Hash, typename Pred, typename Alloc>
std::ostream& operator<<(std::ostream& os,
                         const std::unordered_set<Key, Hash, Pred, Alloc>& s) {
    return utilities::printing::detail_::print_list(os, s, '{', '}');
}

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& os, const std::vector<T, Alloc>& v) {
    return utilities::printing::detail_::print_list(os, v);
}

} // namespace utilities::printing
