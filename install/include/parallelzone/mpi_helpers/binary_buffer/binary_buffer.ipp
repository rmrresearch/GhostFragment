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

/** @file binary_buffer.ipp
 *
 *  This file contains inline definitions for members of BinaryBuffer and
 *  free functions associated with BinaryBuffer. This file should not be
 *  included from any file other than binary_buffer.hpp
 */

namespace parallelzone::mpi_helpers {

// -----------------------------------------------------------------------------
// -- Inline BinaryBuffer Method Implementations
// -----------------------------------------------------------------------------

inline BinaryBuffer::BinaryBuffer(size_type n) :
  BinaryBuffer([&]() {
      using internal_buffer = std::vector<value_type>;
      using pimpl_type      = detail_::BinaryBufferPIMPL<internal_buffer>;
      internal_buffer buffer(n);
      return std::make_unique<pimpl_type>(std::move(buffer));
  }()) {}

inline bool BinaryBuffer::operator==(const BinaryBuffer& rhs) const noexcept {
    if(size() != rhs.size()) return false;
    if(size() == 0) return true;
    return std::equal(begin(), end(), rhs.begin());
}

// -----------------------------------------------------------------------------
// -- Inline Free Functions
// -----------------------------------------------------------------------------

template<typename T>
BinaryBuffer make_binary_buffer(T&& input) {
    using clean_type = std::decay_t<T>;
    if constexpr(needs_serialized_v<clean_type>) {
        using pimpl_type = detail_::BinaryBufferPIMPL<std::string>;
        // TODO: Put directly into a string
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive ar(ss);
            ar << std::forward<T>(input);
        }
        auto pimpl = std::make_unique<pimpl_type>(ss.str());
        return BinaryBuffer(std::move(pimpl));
    } else {
        using pimpl_type = detail_::BinaryBufferPIMPL<clean_type>;
        auto pimpl       = std::make_unique<pimpl_type>(std::forward<T>(input));
        return BinaryBuffer(std::move(pimpl));
    }
}

template<typename T>
T from_binary_buffer(const BinaryBuffer& view) {
    ConstBinaryView ref(view.data(), view.size());
    return from_binary_view<T>(ref);
}

} // namespace parallelzone::mpi_helpers
