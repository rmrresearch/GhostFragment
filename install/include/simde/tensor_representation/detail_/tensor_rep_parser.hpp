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

/** @brief Helper class for sorting the arguments given to tensor_representation
 *
 *  The arguments to tensor_representation are an operator and a series of
 *  basis sets. Those basis sets need to be sorted based on type. Sorting those
 *  basis sets, while keeping track of their position, is the responsibility of
 *  this class. After construction the user can check the various members to
 *  get the set of spaces they want.
 *
 *  N.B. This class is really meant as an implementation detail of
 *       tensor_representation. There are more-or-less no API restrictions in
 *       place which makes it easy to maliciously mess up the state of an
 *       instance. If there is a need for this class somewhere else besides for
 *       in tensor_representation it should be made into a proper class.
 */
struct TensorRepParser {
private:
    /// Shorter type name for the map_type in TensorRepTraits
    template<typename T>
    using trt_map_t = typename TensorRepTraits<T>::map_type;

public:
    /** @brief Creates a TensorRepParser instance by sorting the elements of
     *         @p args into the appropriate member function.
     *
     *  @tparam Args The types of the spaces. Assumed to be read-only references
     *               to known orbital space types.
     *
     *  @param[in] args A tuple containing the spaces that need to be sorted.
     *
     */
    template<typename... Args>
    TensorRepParser(const std::tuple<Args...>& args) {
        parse<0>(args);
    }

    /// Type of the member holding the AO spaces
    using ao_map_t = trt_map_t<type::ao_space>;
    /// Type of the member holding derived spaces
    using derived_space_map_t = trt_map_t<type::derived_space>;

    /// Type of the member holding derived spaces containing ToTs
    using tot_space_map_t = trt_map_t<type::tot_derived_space>;

    /// Type of the member holding the independent spaces
    // using ind_derived_space_map_t = trt_map_t<type::independent_space>;

    /// The AO spaces added to this parser
    ao_map_t m_ao_spaces;

    /// The derived spaces added to this parser
    derived_space_map_t m_derived_spaces;

    /// The derived ToT spaces added to this parser
    tot_space_map_t m_tot_spaces;

    /// The independent spaces added to this parser
    // ind_derived_space_map_t m_ind_spaces;

private:
    /** @brief Implements the ctor via recursion.
     *
     *  The parse function loops over the provied tuple (loop actually occurring
     *  with recursion) adding each space to the appropriate member. This
     *  function relies on add_space to dispatch correctly.
     *
     *  @tparam N The index of the element currently being processed. @p N is
     *            assumed to be in the range [0, sizeof...(Args)).
     *  @tparam Args The types of the spaces in the tuple.
     *
     *  @param[in] args The spaces we need to parse.
     */
    template<std::size_t N, typename... Args>
    void parse(const std::tuple<Args...>& args);

    /**
     *  @name add_space overloads
     *
     *  @brief These member functions use standard overloading to figure out
     *         which member to put the space in.
     *
     *  @param[in] N The mode to associate with @p space.
     *  @param[in] space The space being added to a map.
     */
    ///@{
    void add_space(std::size_t N, const type::ao_space& space);
    void add_space(std::size_t N, const type::derived_space& space);
    void add_space(std::size_t N, const type::tot_derived_space& space);
    // void add_space(std::size_t N, const type::independent_space& space);
    ///@}
};

// -----------------------------------------------------------------------------
// ------------------- Out-of-line inline Implementations ----------------------
// -----------------------------------------------------------------------------

template<std::size_t N, typename... Args>
void TensorRepParser::parse(const std::tuple<Args...>& args) {
    constexpr auto n_args = sizeof...(Args);
    if constexpr(N < n_args) {
        add_space(N, std::get<N>(args));
        parse<N + 1>(args);
    }
}

inline void TensorRepParser::add_space(std::size_t N,
                                       const type::ao_space& space) {
    m_ao_spaces.emplace(N, std::cref(space));
}

inline void TensorRepParser::add_space(std::size_t N,
                                       const type::derived_space& space) {
    m_derived_spaces.emplace(N, std::cref(space));
}

inline void TensorRepParser::add_space(std::size_t N,
                                       const type::tot_derived_space& space) {
    m_tot_spaces.emplace(N, std::cref(space));
}

// inline void TensorRepParser::add_space(std::size_t N,
//                                       const type::independent_space& space) {
//    m_ind_spaces.emplace(N, std::cref(space));
//}

} // namespace simde::detail_
