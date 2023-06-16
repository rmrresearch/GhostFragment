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
#include "tensorwrapper/sparse_map/sparse_map/sparse_map.hpp"

namespace tensorwrapper::sparse_map {

/** @brief Wraps the creation of a sparse map from a pair of independent indices
 *         to the union of the dependent indices.
 *
 *  Given a sparse map @f$L@f$, which goes from @f$i@f$ to @f$a@f$, and a
 *  sparse map @f$M@f$, which goes from @f$i@f$ to @f$i@f$, this function will
 *  make a new sparse map which goes from @f$ij@f$ to @f$a@f$. Only pairs
 *  consistent with @f$M@f$ are made.
 *
 *  This function essentially does a direct product on the independent indices
 *  and a union on the dependent indices, where the direct product is sparse.
 *
 *  @param[in] L_ia The sparse map we are turning into a pair map.
 *  @param[in] L_ij The sparsity relationship among the independent indices of
 *                  @p L_ia.
 *
 *  @return The sparse map resulting from the direct product of the independent
 *          indices in @p L_ia (subject to the sparsity relationship @p L_ij)
 *          and the union of the dependent indices.
 *
 *  @throw std::out_of_range if an independent or dependent index of @p L_ij is
 *                           not in @p L_ia. Strong throw guarantee.
 *  @throw std::runtime_error if the indepdendent (or dependent) indices in
 *                            @p L_ij are not of the same rank as the
 *                            independent indices in @p L_ia. Strong throw
 *                            guarantee.
 *  @throw std::runtime_error if the independent rank of @p L_ia is not 1.
 *                            Strong throw guarantee.
 */
inline auto make_pair_map(const SparseMap& L_ia, const SparseMap& L_ij) {
    if(L_ia.ind_rank() != L_ij.ind_rank()) {
        std::string msg = "Independent rank of L_ia (" +
                          std::to_string(L_ia.ind_rank()) + ") does not match" +
                          " the independent rank of L_ij (" +
                          std::to_string(L_ij.ind_rank()) + ").";
        throw std::runtime_error(msg);
    }

    if(L_ia.ind_rank() != L_ij.dep_rank()) {
        std::string msg = "Independent rank of L_ia (" +
                          std::to_string(L_ia.ind_rank()) + ") does not match" +
                          " the dependent rank of L_ij (" +
                          std::to_string(L_ij.dep_rank()) + ").";
        throw std::runtime_error(msg);
    }

    if(L_ia.ind_rank() != 1)
        throw std::runtime_error("Can only handle rank 1 independent indices");

    SparseMap rv;

    for(const auto& [i, domain_i] : L_ij) {
        for(const auto& j : domain_i) {
            Index ij{i[0], j[0]};
            for(const auto& a : L_ia.at(i)) rv.add_to_domain(ij, a);
            for(const auto& a : L_ia.at(j)) rv.add_to_domain(ij, a);
        }
    }
    return rv;
}

} // namespace tensorwrapper::sparse_map
