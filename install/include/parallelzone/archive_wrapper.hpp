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
#include "parallelzone/serialization.hpp"
#include <variant>

namespace parallelzone {
using variant_output = std::variant<parallelzone::BinaryOutputArchive*,
                                    parallelzone::PortableBinaryOutputArchive*,
                                    parallelzone::JSONOutputArchive*,
                                    parallelzone::XMLOutputArchive*>;
using variant_input =
  std::variant<parallelzone::BinaryInputArchive*,
               parallelzone::PortableBinaryInputArchive*,
               parallelzone::JSONInputArchive*, parallelzone::XMLInputArchive*>;

/** @brief ArchiveWrapper class enables serialization and deserialization of
 * objects using various types of archives supported by Cereal.
 *
 *  This class wraps Cereal API for different output archive types.
 * Required for serialization of Any.
 */
template<typename VariantArchive>
class ArchiveWrapper {
public:
    template<typename Archive>
    ArchiveWrapper(Archive& ar) : m_ar_(&ar) {}

    template<typename T>
    ArchiveWrapper& operator()(T&& obj) {
        std::visit([&](auto&& ar) { (*ar) & std::forward<T>(obj); }, m_ar_);
        return *this;
    }

    template<typename T>
    ArchiveWrapper& operator<<(T&& obj) {
        std::visit([&](auto&& ar) { (*ar) << std::forward<T>(obj); }, m_ar_);
        return *this;
    }

    template<typename T>
    ArchiveWrapper& operator>>(T&& obj) {
        std::visit([&](auto&& ar) { (*ar) >> std::forward<T>(obj); }, m_ar_);
        return *this;
    }

private:
    VariantArchive m_ar_;
};

using Serializer   = ArchiveWrapper<variant_output>;
using Deserializer = ArchiveWrapper<variant_input>;
} // namespace parallelzone