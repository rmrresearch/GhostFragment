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

namespace simde {

template<typename OccType, typename VirtType>
DECLARE_TEMPLATED_PROPERTY_TYPE(DoublesResidual, OccType, VirtType);

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_INPUTS(DoublesResidual, OccType, VirtType) {
    using tensor_type = std::decay_t<decltype(std::declval<VirtType>().C())>;

    auto rv = pluginplay::declare_input()
                .add_field<const type::molecule&>("Molecule")
                .template add_field<const OccType&>("occupied space")
                .template add_field<const VirtType&>("virtual space")
                .template add_field<const tensor_type&>("amplitudes");
    return rv;
}

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_RESULTS(DoublesResidual, OccType, VirtType) {
    using tensor_type = std::decay_t<decltype(std::declval<VirtType>().C())>;
    auto rv = pluginplay::declare_result().add_field<tensor_type>("R");
    return rv;
}

} // namespace simde
