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
#include <parallelzone/mpi_helpers/traits/traits.hpp>
#include <parallelzone/serialization.hpp>
#include <sstream>

/** @file binary_view.ipp
 *
 *  This file contains the inline definitions for members of the BinaryViewBase
 *  class. This file is meant only for inclusion from binary_view.hpp
 */

namespace parallelzone::mpi_helpers {
namespace detail_ {

// -----------------------------------------------------------------------------
// -- BinaryViewBase Methods
// -----------------------------------------------------------------------------

template<bool IsConst>
template<typename T>
BinaryViewBase<IsConst>::BinaryViewBase(T* p, size_type n) :
  m_p_(reinterpret_cast<pointer>(p)), m_n_(sizeof(std::decay_t<T>) * n) {
    if(p == nullptr && n > 0)
        throw std::runtime_error("Nullptr should have a size of 0. So you "
                                 "either meant to pass a non-null pointer, or "
                                 "you computed the size wrong...");
}

template<bool IsConst>
bool BinaryViewBase<IsConst>::operator==(
  const BinaryViewBase& rhs) const noexcept {
    if(size() != rhs.size()) return false;
    if(size() == 0) return true;
    return std::equal(begin(), end(), rhs.begin());
}

template<bool IsConst>
bool BinaryViewBase<IsConst>::operator!=(
  const BinaryViewBase& rhs) const noexcept {
    return !(*this == rhs);
}

} // namespace detail_

// -----------------------------------------------------------------------------
// -- Inline Free Functions
// -----------------------------------------------------------------------------

template<typename T>
T from_binary_view(const ConstBinaryView& view) {
    // I think we will always need to copy out of a view, so there's no
    // reason to allow cv qualifiers or references.

    static_assert(std::is_same_v<T, std::decay_t<T>>);
    if constexpr(needs_serialized_v<T>) {
        using size_type = ConstBinaryView::size_type;
        // TODO: use boost::iostreams to avoid copy into stringstream.
        std::stringstream ss;
        for(size_type i = 0; i < view.size(); ++i)
            ss << *reinterpret_cast<const char*>(view.data() + i);

        T rv;
        {
            cereal::BinaryInputArchive ar(ss);
            ar >> rv;
        }
        return rv;
    } else {
        // Since we didn't need to serialize the T object going in, it must be
        // the case that T is basically a contiguous array of some type U. We
        // assume that U is given by T::value_type and that T has a range ctor
        // which takes two iterators.
        using value_type = typename T::value_type;
        const auto* p    = reinterpret_cast<const value_type*>(view.data());
        auto n           = view.size() / sizeof(value_type);
        return T(p, p + n);
    }
}

} // namespace parallelzone::mpi_helpers
