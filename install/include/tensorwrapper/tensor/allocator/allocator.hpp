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
#include "tensorwrapper/tensor/allocator/allocator_class.hpp"
#include "tensorwrapper/tensor/allocator/direct_tiled_array.hpp"
#include "tensorwrapper/tensor/allocator/tiled_array.hpp"

namespace tensorwrapper::tensor {

namespace allocator {

template<typename FieldType, typename... Args>
typename Allocator<FieldType>::allocator_ptr ta_allocator(Args&&... args) {
    using alloc_type = TiledArrayAllocator<FieldType>;
    return std::make_unique<alloc_type>(std::forward<Args>(args)...);
}

template<typename FieldType>
typename Allocator<FieldType>::allocator_ptr direct_ta_allocator(
  std::string fxn_id) {
    using alloc_type = DirectTiledArrayAllocator<FieldType>;
    return std::make_unique<alloc_type>(fxn_id);
}

} // namespace allocator

/** @brief Wraps the process of creating a defaulted allocator
 *
 *  As more advanced alloctors are added to the library it will make sense
 * to change the default TensorWrapper allocator. To decouple code from this
 *  choice, classes and functions needing a default_allocator instance are
 *  encouraged to get that allocator from this function.
 *
 *  @tparam FieldType The type of the field the tensor is over. Assumed to
 * be either field::Scalar or field::Tensor.
 *
 *  @return a type-erased, allocator.
 *
 *  @throw std::bad_alloc if allocation fails. Strong throw guarantee.
 */
template<typename FieldType>
typename allocator::Allocator<FieldType>::allocator_ptr default_allocator() {
    //    return
    //    std::make_unique<allocator::TiledArrayAllocator<FieldType>>();
    return allocator::ta_allocator<FieldType>();
}

} // namespace tensorwrapper::tensor
