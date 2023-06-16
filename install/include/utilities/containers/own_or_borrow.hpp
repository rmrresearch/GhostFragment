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
#include <variant>

namespace utilities {

/** @brief Class that provides a uniform API for accessing data regardless of
 *         whether it owns the data in it or aliases it.
 *
 *  When implementing classes that are meant to appear array-of-structure-like
 *  to users one often actually stores the data in a structure-of-array manner.
 *  The AoS class then returns structures which alias their data. Often we want
 *  the structures to be capable of standing on their own in a non-aliasing
 *  manner. In this case the structures must own their state (as opposed to
 *  aliasing it). Regardless of whether the structures alias or own their state
 *  we want them to behave the same, so we give them the same API. Internally
 *  this leads to a lot of "if I own the state just return it, otherwise return
 *  the aliased state (usually be dereferencing a pointer)". This class wraps
 *  this if-else logic in a light-weight class. In other words at any given time
 *  this class either owns or aliases its state. The user of this class gets the
 *  state the same way regardless of whether it is aliased or owned by the
 *  OwnedOrBorrowed instance.
 *
 *  @note Owing to the possibly borrowing nature of this class the copy ctor
 *        and copy assignment operators are deleted. This forces the user of the
 *        class to decide what should be done in those situations.
 *
 * @tparam T The type of the object that we may own or borrow. Must be default
 *           constructable, move constructable, and comparable via operator==
 */
template<typename T>
class OwnOrBorrow {
public:
    /** @brief Makes a OwnOrBorrow instance that holds a default constructed
     *         object of type @p T.
     *
     *  The default constructor for the OwnOrBorrow class creates a default
     *  constructed instance of an object of type @p T and internally stores
     *  that instance.
     *
     *  @throw none if @p T's default ctor does not throw. No throw guarantee.
     *  @throw ??? Throws if @p T 's default ctor throws. Same throw guarantee
     *             as @p T's default ctor.
     */
    OwnOrBorrow() = default;

    /// Deleted to force user of class to implement copy ctor
    OwnOrBorrow(const OwnOrBorrow<T>&) = delete;

    /** @brief Makes this OwnOrBorrow instance own or alias another instance's
     *         state.
     *
     *  The move ctor will call std::move() on the value/pointer held by @p rhs
     *  and initialize the new OwnOrBorrow instance with the result. This means
     *  that if @p rhs owns its value it will be moved into the new instance
     *  whereas if @p rhs is aliasing the value the new instance will also be
     *  aliasing it.
     *
     *  @param[in] rhs The instance to take the managed value from. The state of
     *             @p rhs after this ctor depends on the move semantics of the
     *             held value. Generally speaking @p rhs will be in a valid, but
     *             otherwise undefined state if it owned the value it managed
     *             and will be in the same state if it was aliasing it.
     *
     *  @throw none if T's move ctor is also no throw guarantee.
     *  @throw ??? if T's move ctor throws. Same throw guarantee.
     */
    OwnOrBorrow(OwnOrBorrow<T>&& rhs) = default;

    /// Deleted to force user of class to implement copy assignment
    OwnOrBorrow<T>& operator=(const OwnOrBorrow<T>&) = delete;

    /** @brief Makes this OwnOrBorrow instance own or alias another instance's
     *         state.
     *
     *  The move assignment operator will call std::move() on the value/pointer
     *  held by @p rhs and initialize the new OwnOrBorrow instance with the
     *  result. This means that if @p rhs owns its value it will be moved into
     *  the new instance whereas if @p rhs is aliasing the value this instance
     *  will also be aliasing it. Any value owned and aliased by this will be
     *  deleted as a result of this operation.
     *
     *  @param[in] rhs The instance to take the managed value from. The state of
     *             @p rhs after this ctor depends on the move semantics of the
     *             held value. Generally speaking @p rhs will be in a valid, but
     *             otherwise undefined state if it owned the value it managed
     *             and will be in the same state if it was aliasing it.
     *  @return The current instance with @p rhs's state.
     *
     *  @throw ??? if T's move assignment operator throws. Same throw guarantee.
     */
    OwnOrBorrow<T>& operator=(OwnOrBorrow<T>&& rhs) = default;

    /** @brief Value ctor
     *
     *  The value ctor will initialize the internal state to the provided value.
     *  The internal state will **not** alias @p data.
     *
     * @param[in] data The initial value for the managed state.
     *
     * @throw ??? if @p T's move ctor throws. Same throw guarantee as @p T's
     *            move ctor.
     */
    explicit OwnOrBorrow(T data) : m_data_(std::move(data)) {}

    /** @brief Alias ctor
     *
     *  The alias ctor will initialize the internal state to an alias of the
     *  provided value. The internal state will alias @p data.
     *
     * @param[in] data The initial value for the managed state.
     *
     * @throw none No throw guarantee.
     */
    explicit OwnOrBorrow(T* data) noexcept : m_data_(data) {}

    /** @brief Makes the managed value an alias of the provided value.
     *
     *  This function is used to make the internal managed state of this
     *  instance alias @p data.
     *
     *  @param[in] data A pointer to the value that this instance should alias.
     *
     *  @return The current OwnOrBorrow instance now managing an instance of
     *          @p data.
     *  @throw none No throw guarantee.
     */
    auto& operator=(T* data) noexcept {
        m_data_ = data;
        return *this;
    }

    /** @brief Makes the managed value a copy of the provided value.
     *
     *  This function is used to make the internal managed state of this
     *  instance a copy of @p data.
     *
     *  @param[in] data The value that this instance should manage.
     *
     *  @return The current OwnOrBorrow instance now managing an instance of
     *          @p data.
     *  @throw ??? If @p T's move assignment operator throws. Same throw
     *         guarantee.
     */
    auto& operator=(T data) {
        m_data_ = std::move(data);
        return *this;
    }

    /** @brief Returns the managed value in a (possibly) read/write state.
     *
     *  This function takes care of the if-else logic associated with
     *  dereferencing the alias or returning the value depending on whether we
     *  are storing or aliasing the managed state.
     *
     *  @return The managed state by reference.
     *  @throw none No throw guarantee.
     */
    T& value() noexcept { return is_alias_() ? alias_() : value_(); }

    /** @brief Returns the managed value in a read-only state.
     *
     *  This function takes care of the if-else logic associated with
     *  dereferencing the alias or returning the value depending on whether we
     *  are storing or aliasing the managed state.
     *
     *  @return The managed state as read-only reference.
     *  @throw none No throw guarantee.
     */
    const T& value() const noexcept {
        return is_alias_() ? alias_() : value_();
    }

private:
    /// Wraps checking if we have the alias or the value
    bool is_alias_() const noexcept { return std::get_if<1>(&m_data_); }
    /// Wraps getting the read/write value
    T& value_() noexcept { return std::get<0>(m_data_); }
    /// Wraps getting the read-only value
    const T& value_() const noexcept { return std::get<0>(m_data_); }
    /// Wraps getting the read/write alias
    T& alias_() noexcept { return *std::get<1>(m_data_); }
    /// Wraps getting the read-only alias
    const T& alias_() const noexcept { return *std::get<1>(m_data_); }

    /// The state actually managed by this class
    std::variant<T, T*> m_data_;
}; // class OwnOrBorrow

/** @brief Determines if two OwnOrBorrow instances are managing the same value.
 *
 *  This function compares the managed values using operator== and returns the
 *  result. In particular this means we are not determining if the two instances
 *  are aliasing the same instance, only that the values compare equal.
 *
 * @tparam T The type of the managed value.
 * @param[in] lhs The instance on the left side of the comparison operator.
 * @param[in] rhs The instance @p lhs is being compared to.
 * @return True if T::operator== returns true and false if T::operator== returns
 *         false.
 * @throw ??? if T::operator== throws. Same throw guarantee.
 */
template<typename T>
bool operator==(const OwnOrBorrow<T>& lhs, const OwnOrBorrow<T>& rhs) {
    return lhs.value() == rhs.value();
}

/** @brief Determines if two OwnOrBorrow instances are managing different
 *         values.
 *
 *  This function compares the managed values using operator== and negates the
 *  result. In particular this means we are not determining if the two instances
 *  are aliasing different instances only that the values compare different.
 *
 * @tparam T The type of the managed value.
 * @param[in] lhs The instance on the left side of the comparison operator.
 * @param[in] rhs The instance @p lhs is being compared to.
 * @return False if T::operator== returns true and true if T::operator== returns
 *         false.
 * @throw ??? if T::operator== throws. Same throw guarantee.
 */
template<typename T>
bool operator!=(const OwnOrBorrow<T>& lhs, const OwnOrBorrow<T>& rhs) noexcept {
    return !(lhs == rhs);
}

} // namespace utilities
