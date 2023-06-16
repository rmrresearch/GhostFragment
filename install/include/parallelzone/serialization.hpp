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
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/details/traits.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/atomic.hpp>
#include <cereal/types/bitset.hpp>
#include <cereal/types/chrono.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/forward_list.hpp>
#include <cereal/types/functional.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/optional.hpp>
#include <cereal/types/queue.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/stack.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/valarray.hpp>
#include <cereal/types/variant.hpp>
#include <cereal/types/vector.hpp>

namespace parallelzone {
using XMLOutputArchive            = cereal::XMLOutputArchive;
using XMLInputArchive             = cereal::XMLInputArchive;
using JSONOutputArchive           = cereal::JSONOutputArchive;
using JSONInputArchive            = cereal::JSONInputArchive;
using BinaryOutputArchive         = cereal::BinaryOutputArchive;
using BinaryInputArchive          = cereal::BinaryInputArchive;
using PortableBinaryOutputArchive = cereal::PortableBinaryOutputArchive;
using PortableBinaryInputArchive  = cereal::PortableBinaryInputArchive;
template<typename T, typename Archive>
using is_serializable = cereal::traits::is_output_serializable<T, Archive>;
template<typename T, typename Archive>
using is_deserializable = cereal::traits::is_input_serializable<T, Archive>;
using cereal::traits::detail::get_input_from_output;
using cereal::traits::detail::get_output_from_input;
} // namespace parallelzone