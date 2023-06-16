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
#include <string>
#include <typeindex>

namespace utilities::printing {

/** @brief Class used to demangle RTTI names.
 *
 *  In C++ you can get RTTI of a type using the built-in `typeid` function. You
 *  can then use the resulting class for comparisons. At first the `name`
 *  member of the resulting class seems particularly useful for printing type
 *  information; however, one quickly realizes that the result is the platform-
 *  specific mangled type name. The Demangler class wraps the process of
 *  demangling the name thereby providing much nicer print outs of types.
 *
 *  At the moment this class only knows how to demangle the GNU compilers.
 */
struct Demangler {
    /** @brief Prints the demangled name of the type @p T
     *
     *  This overload is a convenience function for demangling given just the
     *  type. It ultimately will call `typeid` on @p T and defer to the result
     *  to another overload.
     *
     * @tparam T The type of the type we want to print the name of.
     *
     * @return The demangled type (if we know how to demangle it for your
     *         compiler) otherwise the mangled type.
     *
     * @throw std::bad_alloc if there is insufficient memory to copy the name to
     *                       the returned string. Strong throw guarantee.
     */
    template<typename T>
    static std::string demangle();

    /** @brief Prints the demangled name of the type @p t
     *
     *  This overload is a convenience function for demangling given the result
     *  of a call to `typeid`. It ultimately will forward the mangled string
     *  name (as returned by `std::type_info::name`) to another overload.
     *
     * @param[in] t The type ID of the type to print the name of.
     *
     * @return The demangled type (if we know how to demangle it for your
     *         compiler) otherwise the mangled type.
     *
     * @throw std::bad_alloc if there is insufficient memory to copy the name to
     *                       the returned string. Strong throw guarantee.
     */
    static std::string demangle(const std::type_info& t);

    /** @brief Prints the demangled name of the type @p t
     *
     *  This overload is a convenience function for demangling given an
     *  `std::type_index`. It ultimately will forward the mangled string
     *  name (as returned by `std::type_index::name`) to another overload.
     *
     * @param[in] t The type index of the type to print the name of.
     *
     * @return The demangled type (if we know how to demangle it for your
     *         compiler) otherwise the mangled type.
     *
     * @throw std::bad_alloc if there is insufficient memory to copy the name to
     *                       the returned string. Strong throw guarantee.
     */
    static std::string demangle(const std::type_index& t);

    /** @brief Demangles the type inside @p t
     *
     *  The name of the type stored inside @p t is compiler-specific. This
     *  function will call the compiler intrinsic function to demangle it and
     *  return the result. The implementation for the GNU compiler is
     *  shamelessly stolen from https://stackoverflow.com/a/4541470.
     *
     *  @note This overload is the one that does all of the work. The other two
     *        overloads simply defer to this one.
     *
     * @param[in] t The string literal representation of the mangled type.
     *
     * @return The demangled type (if we know how to demangle it for your
     *         compiler) otherwise the mangled type.
     *
     * @throw std::bad_alloc if there is insufficient memory to copy the name to
     *                       the returned string. Strong throw guarantee.
     */
    static std::string demangle(const char* t);
};

//-------------------Implementations--------------------------------------------

template<typename T>
std::string Demangler::demangle() {
    return Demangler::demangle(typeid(T));
}

inline std::string Demangler::demangle(const std::type_info& t) {
    return Demangler::demangle(t.name());
}

inline std::string Demangler::demangle(const std::type_index& t) {
    return Demangler::demangle(t.name());
}

} // namespace utilities::printing
