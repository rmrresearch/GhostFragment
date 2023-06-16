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
#include <map>
#include <utility> // For reference_wrapper

namespace simde {

/** @brief Stores a mapping from mode index to basis set instances.
 *
 *  This class is primarily meant for use with the property types associated
 *  with tensor representations. When we call a module satisfying one of those
 *  property types we must specify the basis sets for each mode of the tensor.
 *  This is conventionally done by positional arguments (0-th basis set passed
 *  in is for mode 0, 1-st is for mode 1, etc.), but that leads to a lot of
 *  APIs (templating doesn't really help because property types/modules require
 *  you to explicitly instantiate a template per permuation of types).
 *
 *  Our solution is to introduce the ModeToBasisMap class. This class acts like
 *  a std::map<int, const BasisSetType&> where the keys are mode indices and
 *  the values are read-only references to BasiSetType instances. Using the
 *  ModeToBasisMap class property types are defined in terms of number of basis
 *  sets (i.e., the rank of the resulting tensor) and a series of
 *  ModeToBasisMap<T> instances, one ModeToBasisMap instance for each basis set
 *  T the module needs to consider.
 *
 *  In practice the ModeToBasisMap class is a thin wrapper around a std::map,
 *  which also worries about ownership. In particular since this class is meant
 *  for use with property types it recognizes that it sometimes must alias the
 *  basis sets and other times own them. The logic for this is encapsulated in
 *  copy vs move; copy deep copies instances whereas move preserves aliasing.
 *
 *  @tparam BasisSetType The type being used to model a basis set.
 */
template<typename BasisSetType>
class ModeToBasisMap {
private:
    /// Reference_wrapper to a const @p T, defined to shorten future typedefs
    template<typename T>
    using const_ref_wrapper = std::reference_wrapper<const T>;

public:
    /// Type used for indexing modes, acts like an unsinged integer type
    using mode_type = unsigned int;

    /// Unqualified type of a basis set instance, typedef of BasisSetType
    using basis_set_type = BasisSetType;

    /// Read-only reference to a basis set, typedef of const BasisSetType&
    using const_basis_set_reference = const_ref_wrapper<BasisSetType>;

    /// A std::map from mode offest to const_basis_set_reference
    using map_type = std::map<mode_type, const_basis_set_reference>;

    /// Read-only reference to a "mode, basis set" pair
    using const_reference = typename map_type::const_reference;

    /** @brief Creates an empty ModeToBasisMap instance.
     *
     *  This ctor creates a ModeToBasisMap instance which contains no elements
     *  yet. Elements can be added by calling emplace.
     *
     *  @throw None No throw guarantee.
     */
    ModeToBasisMap() = default;

    /** @brief Creates a deep copy of @p other.
     *
     *  This function will own deep copies of each basis set in @p other. This
     *  means regardless of whether or not @p other aliased a basis set, the
     *  resulting ModeToBasisMap will own its copy. The basis sets will still
     *  have the same mapping.
     *
     *  @param[in] other The instance being deep-copied.
     *
     *  @throw std::bad_alloc if the copy fails. Strong throw guarantee.
     */
    ModeToBasisMap(const ModeToBasisMap& other);

    /** @brief Creates a new ModeToBasisMap by taking ownership of @p other
     *
     *  This ctor creates a new instance by moving the state from @p other to
     *  the new instance. In particular this means the new instance will still
     *  alias any basis sets @p other aliased, and it will own any basis sets
     *  that @p other owned.
     *
     *  @param[in, out] other The instance whose state is being transferred to
     *                        the newly created ModeToBasisMap instance. After
     *                        the operation @p other is in a valid, but
     *                        otherwise undefined state.
     *
     *  @throw None No throw guarantee.
     */
    ModeToBasisMap(ModeToBasisMap&& other) noexcept;

    /** @brief Makes the current instance a deep copy of @p rhs
     *
     *  This method will overwrite the current instance's state with a deep copy
     *  of the state found in @p rhs. Similar to the copy ctor, the resulting
     *  instance will own deep copies of each basis set regardless of whether or
     *  not @p rhs aliased or owned the basis sets.
     *
     *  @param[in] rhs The instance whose state is being copied.
     *
     *  @return The current instance, after setting its state to a deep copy of
     *          @p rhs 's state.
     *
     *  @throw std::bad_alloc if the copy fails.
     *
     */
    ModeToBasisMap& operator=(const ModeToBasisMap& rhs);

    /** @brief Takes ownership of @p rhs.
     *
     *  This method will release the state currenting held in the present
     *  instance and replace it with the state held in @p rhs. This means that
     *  after this call the present instance will alias the basis sets that
     *  @p rhs aliased and own the basis sets that @p rhs owned.
     *
     *  @param[in,out] rhs The ModeToBasisMap instance we are taking ownership
     *                     of. After this call @p rhs will be in a valid, but
     *                     otherwise undefined state.
     *
     *  @return The current instance, after setting its state to a deep copy of
     *          @p rhs's state.
     *
     *  @throw None No throw guarantee.
     */
    ModeToBasisMap& operator=(ModeToBasisMap&& rhs) noexcept;

    void swap(ModeToBasisMap& other) noexcept;

    /** @brief Returns the number of mode-to-basis-set mappings.
     *
     *  ModeToBasisMap instances are essentially maps from mode offsets to the
     *  basis set for that mode. This function will return the number of such
     *  mappings contained within the current instance.
     *
     *  It should be noted that for a mode `i`, `i < size()` does not guarantee
     *  that `i` is a valid key nor does `i >= size()` guarantee that `i` is an
     *  invalid key. For example,
     *
     *  ```
     *  auto O_imnj = tensor_representation(i, mu, O, nu, j);
     *  ```
     *
     *  will result in two maps (assuming "i" and "j" are DerivedSpace objects
     *  and "mu" and "nu" are AOSpace objects):
     *
     *  - ModeToBasis<DerivedSpace>{{0, i}, {3, j}} (size 2)
     *  - ModeToBasis<AOSpace>{{1, mu}, {2, nu}} (size 2)
     *
     *  Mode 0 is an invalid input for the second map (despite being less
     *  than `size()`) and mode 3 is a valid input for first map (despite being
     *  more than `size()`).
     *
     *  @return The number of mode-to-basis-set mappings in the instance.
     *
     *  @throw None No throw guarantee.
     */
    auto size() const noexcept { return m_aliased_bs_.size(); }

    /** @brief Returns the number of times a mode offset appears in the map.
     *
     *  This method will count the number of pairs which have a mode offset of
     *  @p i. Since at most only one pair can have such an offset this function
     *  always return 0 or 1.
     *
     *  @param[in] i The offset we are looking for.
     *
     *  @return True (1) if the instance contains @p i and false (0) otherwise.
     *
     *  @throw None No throw guarantee.
     */
    auto count(mode_type i) const noexcept { return m_aliased_bs_.count(i); }

    /** @brief Adds the specified "mode offset, basis set" pair to the map.
     *
     *  This method is used to associate the @p i -th mode of the tensor with
     *  basis set @p bs. If this instance already has a mapping for mode offset
     *  @p i then this is a no-op.
     *
     *  @note the don't overwrite behavior is consistent with emplace on
     *        std::map.
     *
     *  @param[in] i The tensor mode to associate @p bs with.
     *  @param[in] bs The basis set to associate with the @p i -th  mode of the
     *                tensor.
     *
     *  @throw std::bad_alloc if there is a problem storing the pair. Strong
     *                        throw guarantee.
     */
    void emplace(mode_type i, const_basis_set_reference bs);

    /** @brief Returns the basis set for the i-th mode of the tensor.
     *
     *  This method is used to look up registered mode to basis set mappings.
     *  Given mode offset @p i, this method will return the basis set `bs` that
     *  was inserted as if by calling `emplace(i, bs)`.
     *
     *  @param[in] i The tensor mode we are retrieving the basis set for.
     *
     *  @return A read-only reference to the basis set for the @p i -th mode.
     *
     *  @throw std::out_of_range if @p i is not associated with a basis set in
     *                           this instance. Strong throw guarantee.
     */
    const_basis_set_reference at(mode_type i) const;

    /** @brief Returns an iterator to the first "mode, basis set" pair
     *
     *  This method returns an iterator which points to the first "mode, basis
     *  set" pair. In particular note this iterator runs over more than just the
     *  keys of the map. The actual instance pointed to behaves like
     *  `std::pair<mode_type, const_basis_set_reference>`.
     *
     *  N.B. If `size()==0` the iterator returned by this method is the same as
     *       the one returned by `end()` and should NOT be dereferenced.
     *
     *  @return An iterator pointing to the first mode-bs pair.
     *
     *  @throw None No throw guarantee.
     */
    auto begin() const noexcept { return m_aliased_bs_.begin(); }

    /** @brief Returns an iterator to just past the last mode-basis set pair.
     *
     *  This method is used to retrieve an iterator that points to just past
     *  the last "mode offset, basis set" pair. The iterator should be
     *  considered a semaphore and should NOT be dereferenced.
     *
     *  @return An iterator which points to just past the last mode-basis set
     *          pair. This iterator should not be dereferenced.
     *
     *  @throw None No throw guarantee.
     */
    auto end() const noexcept { return m_aliased_bs_.end(); }

    /** @brief Compares two ModeToBasisMap instances for value equality.
     *
     *  This method is used to determine if two ModeToBasisMap instances map
     *  the same modes to the same basis sets. In particular we compare the
     *  values of the basis sets, not the addresses. In other words, if `x` and
     *  `y` are two basis set instances such that `x == y`, but `&x != &y` then
     *  a mapping from mode `i` to an alias of `x` in one ModeToBasisMap
     *  instance will compare equal to a mapping from mode `i` to an alias of
     *  `y` in another ModeToBasisMap instance. Whether the ModeToBasisMap
     *  instances own or alias their values is not considered in the comparison.
     *
     *  @param[in] rhs The instance we are comparing to.
     *
     *  @return True if this instance compares equal to @p rhs and false
     *          otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const ModeToBasisMap& rhs) const noexcept;

    /** @brief Determines if two ModeToBasisMap instances are different.
     *
     *  This method negates operator==. See operator== for a definition of
     *  equality.
     *
     *  @param[in] rhs The instance we are comparing to.
     *
     *  @return False if this compares equal to @p rhs and true otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator!=(const ModeToBasisMap& rhs) const noexcept;

private:
    /// Holds the basis sets we are aliasing (even owned ones are aliased here)
    map_type m_aliased_bs_;

    // Holds the basis sets we own the memory for
    std::map<mode_type, BasisSetType> m_owned_bs_;
};

} // namespace simde

#include "mode_to_basis_map.ipp"
