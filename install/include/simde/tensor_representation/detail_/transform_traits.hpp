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
#include "simde/tensor_representation/detail_/tensor_rep_traits.hpp"

namespace simde::detail_ {

template<typename... Args>
struct TransformTraits {
private:
    template<typename T>
    using traits = TensorRepTraits<T>;

public:
    static constexpr bool has_derived = (traits<Args>::is_derived || ...);

    static constexpr bool has_tots = (traits<Args>::is_tot_derived || ...);
};

} // namespace simde::detail_
