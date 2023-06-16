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

// This file meant only for inclusion from mode_to_basis_map.hpp

namespace simde {

#define TPARAMS template<typename BasisSetType>
#define MODE_TO_BASIS_MAP ModeToBasisMap<BasisSetType>

TPARAMS
MODE_TO_BASIS_MAP::ModeToBasisMap(const ModeToBasisMap& other) {
    // N.B. We get away with one loop b/c std::map guarantees references don't
    //      change between insertions
    // XXX: this is going to store multiple copies of the same basis set.
    //      std::set would be better, but orbital spaces don't have operator<
    for(const auto& [k, v] : other.m_aliased_bs_) {
        auto [itr, _] = m_owned_bs_.emplace(k, v.get());
        m_aliased_bs_.emplace(k, std::cref(itr->second));
    }
}

TPARAMS
MODE_TO_BASIS_MAP::ModeToBasisMap(ModeToBasisMap&& other) noexcept :
  m_aliased_bs_(std::move(other.m_aliased_bs_)),
  m_owned_bs_(std::move(other.m_owned_bs_)) {}

TPARAMS
MODE_TO_BASIS_MAP& MODE_TO_BASIS_MAP::operator=(const ModeToBasisMap& rhs) {
    if(&rhs != this) ModeToBasisMap(rhs).swap(*this);
    return *this;
}

TPARAMS
MODE_TO_BASIS_MAP& MODE_TO_BASIS_MAP::operator=(ModeToBasisMap&& rhs) noexcept {
    if(&rhs != this) ModeToBasisMap(std::move(rhs)).swap(*this);
    return *this;
}

TPARAMS
void MODE_TO_BASIS_MAP::swap(ModeToBasisMap& other) noexcept {
    m_aliased_bs_.swap(other.m_aliased_bs_);
    m_owned_bs_.swap(other.m_owned_bs_);
}

TPARAMS
void MODE_TO_BASIS_MAP::emplace(mode_type i, const_basis_set_reference bs) {
    m_aliased_bs_.emplace(i, bs);
}

TPARAMS
typename MODE_TO_BASIS_MAP::const_basis_set_reference MODE_TO_BASIS_MAP::at(
  mode_type i) const {
    // N.B. We verify it exists before calling .at so we can give a better error
    //      message than the one .at returns by default.
    if(m_aliased_bs_.count(i)) return m_aliased_bs_.at(i);

    throw std::out_of_range("ModeToBasisMap does not include a mapping for "
                            "mode " +
                            std::to_string(i) + ".");
}

TPARAMS
bool MODE_TO_BASIS_MAP::operator==(const ModeToBasisMap& rhs) const noexcept {
    if(size() != rhs.size()) return false;
    for(const auto& [k, v] : m_aliased_bs_) {
        if(!rhs.m_aliased_bs_.count(k)) return false;
        if(v.get() != m_aliased_bs_.at(k).get()) return false;
    }
    return true;
}

TPARAMS
bool MODE_TO_BASIS_MAP::operator!=(const ModeToBasisMap& rhs) const noexcept {
    return !(*this == rhs);
}

#undef MODE_TO_BASIS_MAP
#undef TPARAMS

} // namespace simde
