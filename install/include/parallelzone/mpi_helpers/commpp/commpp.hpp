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
#include <memory>
#include <mpi.h>
#include <parallelzone/mpi_helpers/binary_buffer/binary_buffer.hpp>
#include <parallelzone/mpi_helpers/binary_buffer/binary_view.hpp>
#include <parallelzone/mpi_helpers/traits/gather.hpp>

namespace parallelzone::mpi_helpers {
namespace detail_ {
class CommPPPIMPL;
}

/** @brief A little wrapper around an MPI communicator to make it more C++
 *         friendly.
 *
 *  This class is meant to provide an object-oriented API to MPI and takes care
 *  of many of the annoying things one may need to do in order to use an
 *  arbitrary C++ object with MPI. Users of parallelzone should consider this
 *  the absolute lowest level API and should not have to ever interact with MPI
 *  directly. The guts of this class are such that they should be able to take
 *  care of every optimization which is possible without the user needing to
 *  break API. That said the underlying implementations are probably not fully
 *  optimized so if you see opportunities for optimization please do so under
 *  the hood instead of breaking API.
 */
class CommPP {
public:
    /// Type of the class implementing *this
    using pimpl_type = detail_::CommPPPIMPL;

    /// Type of a pointer to the PIMPL
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    /// Type of a bare MPI communicator
    using mpi_comm_type = MPI_Comm;

    /// Type used for indexing and offsets
    using size_type = int;

    /// Type of a block of binary data
    using binary_type = BinaryBuffer;

    /// Type of a read/write reference to a block of binary data
    using binary_reference = BinaryView;

    /// Type of a read-only reference to a block of binary data
    using const_binary_reference = ConstBinaryView;

    /// Type returned by the binary version of gather
    using binary_gather_return = gather_return_t<binary_type>;

    /// Type of a buffer and the sizes per rank
    using gatherv_pair = std::pair<binary_type, std::vector<size_type>>;

    /// Type returned by the binary version of gatherv
    using binary_gatherv_return = std::optional<gatherv_pair>;

    // -------------------------------------------------------------------------
    // -- CTors, Assignment, and Dtor
    // -------------------------------------------------------------------------

    /** @brief Creates a null communicator.
     *
     *  The instance resulting from this ctor wraps the MPI_COMM_NULL instance.
     *  The communicator has a size of 0 and the rank of the current process
     *  is MPI_PROC_NULL.
     *
     *  @throw None No throw guarantee.
     */
    CommPP() noexcept;

    /** @brief Creates a communicator which wraps @p comm.
     *
     *  MPI groups processes into communicators. This ctor will initialize *this
     *  so that it wraps the MPI communicator identified by the handle @p comm.
     *
     *  Under the hood this will call MPI_Comm_size and MPI_Comm_rank on the
     *  provided communicator and cache the results. If the user frees the
     *  communicator wrapped by *this and still tries to access state of *this
     *  bad things will happen, but I don't know any way of causing *this to
     *  own a copy of @p comm to prevent that from happening.
     *
     *  @param[in] comm The handle of the MPI communicator to initialize *this
     *                  from.
     */
    explicit CommPP(mpi_comm_type comm);

    /** @brief Creates a new CommPP instance which is a "deep" copy of @p other.
     *
     *  This ctor initializes *this as a deep copy of @p other. In practice this
     *  means that *this will contain a copy of the MPI handle so that changing
     *  the communicator of @p other will not affect *this; however, since the
     *  MPI communicators are just handles actually modifying the underlying
     *  MPI communicator will affect *this.
     *
     *  @param[in] other The communicator we are copying.
     */
    CommPP(const CommPP& other);

    /** @brief Creates a new CommPP by taking ownership of the state in @p other
     *
     *  This ctor initializes *this by taking ownership of the state in
     *  @p other.
     *
     *  @param[in,out] other The object whose state is being taken. After this
     *                       operation @p other is in a state analogous to
     *                       default initialization.
     *
     *  @throw None No throw guarantee.
     */
    CommPP(CommPP&& other) noexcept;

    /** @brief Makes *this a deep copy of @p other.
     *
     *  This operation will replace the contents of *this (freeing the current
     *  state up in the process) with a deep copy of the state in @p other.
     *  See the copy ctor for details pertaining to what a deep copy entails.
     *
     *  @param[in] rhs The object to copy.
     *
     *  @return *this after replacing its state with a copy of @p rhs.
     *
     */
    CommPP& operator=(const CommPP& rhs);

    /** @brief Transfers the state in @p other to *this.
     *
     *  This operation will move the state in @p other to *this. In the process
     *  the current state of *this will be released.
     *
     *  @param[in,out] other The object whose state is being taken. After this
     *                       operation @p other is in a state analogous to
     *                       default initialization.
     *
     *  @return *this after replacing its state with the state in @p rhs.
     *
     *  @throw None No throw guarantee.
     */
    CommPP& operator=(CommPP&& other) noexcept;

    /// Default dtor
    ~CommPP() noexcept;

    // -------------------------------------------------------------------------
    // -- Accessors
    // -------------------------------------------------------------------------

    /** @brief Returns a handle to the underlying MPI communicator
     *
     *  *this ultimately wraps an MPI communicator. This method will return a
     *  handle to the underlying MPI communicator. If *this has is a null
     *  communicator, either because it was default initialized or initialized
     *  to a null communicator, the result will be MPI_COMM_NULL.
     *
     *  @return A handle to the undelrying MPI communicato or MPI_COMM_NULL if
     *          there is no underlying communicator.
     *
     *  @throw None no throw guarantee.
     */
    mpi_comm_type comm() const noexcept;

    /** @brief Returns the number of ranks manged by comm()
     *
     *  In MPI, processes are grouped into communicators. This method is used
     *  to determine how many processes are associated with the communicator
     *  held by *this. If *this is a null communicator, either because it was
     *  default initialized or because it was initialized to a null
     *  communicator, the size will be 0.
     *
     *  Calling this method is logically the same as calling MPI_Comm_size.
     *  The actual call is only done during construction and the result is
     *  cached in *this.
     *
     *  @return The number of processes associated with the wrapped MPI
     *          communicator.
     *
     *  @throw None No throw guarantee.
     */
    size_type size() const noexcept;

    /** @brief Returns the rank of the current process.
     *
     *  In MPI processes are grouped into communicators. Each process in the
     *  communicator has a unique ID ranging from 0 to the size of the
     *  communicator. This method is used to retrieve the rank of the current
     *  process. If this communicator is null, either because it was default
     *  initialized or because it was set to null, then the result will be
     *  MPI_PROC_NULL.
     *
     *  Calling this method is logically the same as calling MPI_Comm_rank. The
     *  actual call is only done during construction and the result is cached
     *  in *this.
     *
     *  @return The ID of the current process according to the communicator
     *          wrapped by *this.
     *
     *  @throw None No throw guarantee.
     */
    size_type me() const noexcept;

    // -------------------------------------------------------------------------
    // -- Utility
    // -------------------------------------------------------------------------

    /** @brief Exchanges the state in *this with that in @p other.
     *
     *  This method is used to exchange the stat of *this with the state in
     *  another CommPP object. After this operation *this will contain the
     *  state which was originally in @p other and @p other will contain the
     *  state which was originally in *this.
     *
     *  @param[in, out] other The object whose state will be exchanged with
     *                        *this. After the operation @p other will contain
     *                        the state which was in *this before the operation.
     *
     *  @throw None No throw guarantee.
     */
    void swap(CommPP& other) noexcept;

    /** @brief Determines if *this is value equal to @p rhs.
     *
     *  *this is value equal to @p rhs if both *this and @p rhs are null
     *  communicators, either by being default constructed or by being set to
     *  MPI_COMM_NULL, or if both *this and @p rhs wrap handles to the same
     *  MPI communicator (as determined by MPI_Comm_compare).
     *
     *  @param[in] rhs The object being compared to *this.
     *
     *  @return True if *this is value equal to @p rhs and false otherwise.
     *
     *  @throw None No throw guarantee.
     */

    bool operator==(const CommPP& rhs) const noexcept;

    /** @brief Determines if *this is different from @p rhs.
     *
     *  This method simply negates value equality. See the description of
     *  operator== for more information on how value equality is determined.
     *
     *  @param[in] rhs The object being compared to *this.
     *
     *  @return False if *this is value equal to @p rhs and true otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator!=(const CommPP& rhs) const noexcept;

    // -------------------------------------------------------------------------
    // -- Gather
    // -------------------------------------------------------------------------

    /// Type returned by gather (and gatherv) given an object of type @p T
    template<typename T>
    using gather_return_type = gather_return_t<std::decay_t<T>>;

    /// Result type from all gather (and all gatherv) given object of type @p T
    template<typename T>
    using all_gather_return_type = typename gather_return_type<T>::value_type;

    /** @brief Gathers consistently sized, but otherwise arbitrary data to a
     *         MPI process @p root.
     *
     *  In a gather operation involving `N` processes, the data from each
     *  process will be concatenated into an `N` element array such that the
     *  `i`-th piece of data came from the process with rank `i`. It should be
     *  noted that the data sent from each process needs to be a single object,
     *  but that object can contain multiple elements. For example,
     *  `T == std::vector<double>` sends a single `std::vector` instance which
     *  (may) contains multiple `double` values.
     *
     *  This gather call will only collect the result on the process whose rank
     *  is @p root. All other processes send data, but do not end up with the
     *  result. To give every process a copy of the data use an "all gather"
     *  operation (the overload of `gather` which does not take a root process).
     *
     *  This method honors the type traits stated in the (TODO: Add link when
     *  the documentation is done) section.
     *
     *  This call is ultimately equivalent to calling MPI_Gather.
     *
     *  @warning This method is only suitable for use when the size of @p input
     *  (in bytes) is the same on all ranks. If the size is not the same on all
     *  ranks (or you can't guarantee that it is) you need to use gatherv.
     *
     *
     *  @tparam T The qualified type of the data to gather.
     *
     *  @param[in] input This process's contribution to the gather operation.
     *                   The size of input (in bytes) must be the same on all
     *                   ranks for this method to work.
     *
     *  @param[in] root The rank of the process which will get all of the data.
     *
     *  @return A std::optional which has a value on process @p root and no
     *          value on all other processes. If @p T needs serialized the
     *          optional holds a `std::vector<T>`; if @p T does not need
     *          serialized the optional holds an object of type @p T.
     */
    template<typename T>
    gather_return_type<T> gather(T&& input, size_type root) const;

    /** @brief Gathers consistently sized, but otherwise arbitrary data to each
     *         MPI process.
     *
     *  In a gather operation involving `N` processes, the data from each
     *  process will be concatenated into an `N` element array such that the
     *  `i`-th piece of data came from the process with rank `i`. It should be
     *  noted that the data sent from each process needs to be a single object,
     *  but that object can contain multiple elements. For example,
     *  `T == std::vector<double>` sends a single `std::vector` instance which
     *  (may) contains multiple `double` values.
     *
     *  This gather call will provide each process with a copy of the gathered
     *  data. If only one process needs a copy of the data consider the overload
     *  of `gather` which does takes a root process.
     *
     *  This method honors the type traits stated in the (TODO: Add link when
     *  the documentation is done) section.
     *
     *  This call is ultimately equivalent to calling MPI_Allgather.
     *
     *  @warning This method is only suitable for use when the size of @p input
     *  (in bytes) is the same on all ranks. If the size is not the same on all
     *  ranks (or you can't guarantee that it is) you need to use gatherv.
     *
     *  @tparam T The qualified type of the data to gather.
     *
     *  @param[in] input This process's contribution to the gather operation.
     *                   The size of input (in bytes) must be the same on all
     *                   ranks for this method to work..
     *
     *  @return The gathered data. If @p T needs to be serialized the result
     *          is a std::vector<T>, otherwise it's an object of type @p T.
     */
    template<typename T>
    all_gather_return_type<T> gather(T&& input) const;

    /** @brief Gathers arbitrary data to a MPI process @p root.
     *
     *  In a gather operation involving `N` processes, the data from each
     *  process will be concatenated into an `N` element array such that the
     *  `i`-th piece of data came from the process with rank `i`. It should be
     *  noted that the data sent from each process needs to be a single object,
     *  but that object can contain multiple elements. For example,
     *  `T == std::vector<double>` sends a single `std::vector` instance which
     *  (may) contains multiple `double` values.
     *
     *  This gather call will only collect the result on the process whose rank
     *  is @p root. All other processes send data, but do not end up with the
     *  result. To give every process a copy of the data use an "all gatherv"
     *  operation (the overload of `gatherv` which does not take a root
     *  process). Unlike gather, gatherv allows the size of @p input (in bytes)
     *  to be different on different ranks. This has additional communication
     *  overhead relative to the normal gather call, so use gather if you can
     *  guarantee that your data's size is consistent.
     *
     *  This method honors the type traits stated in the (TODO: Add link when
     *  the documentation is done) section.
     *
     *  This call is ultimately equivalent to calling MPI_Gatherv.
     *
     *  @tparam T The qualified type of the data to gather.
     *
     *  @param[in] input This process's contribution to the gather operation.
     *
     *  @param[in] root The rank of the process which will get all of the data.
     *
     *  @return A std::optional which has a value on process @p root and no
     *          value on all other processes. If @p T needs serialized the
     *          optional holds a `std::vector<T>`; if @p T does not need
     *          serialized the optional holds an object of type @p T.
     */
    template<typename T>
    gather_return_type<T> gatherv(T&& input, size_type root) const;

    /** @brief Gathers arbitrary data to each MPI process.
     *
     *  In a gather operation involving `N` processes, the data from each
     *  process will be concatenated into an `N` element array such that the
     *  `i`-th piece of data came from the process with rank `i`. It should be
     *  noted that the data sent from each process needs to be a single object,
     *  but that object can contain multiple elements. For example,
     *  `T == std::vector<double>` sends a single `std::vector` instance which
     *  (may) contains multiple `double` values.
     *
     *  This gather call will provide each process with a copy of the gathered
     *  data. If only one process needs a copy of the data consider the overload
     *  of `gather` which does takes a root process. Unlike gather, gatherv
     *  allows the size of @p input (in bytes) to be different on different
     *  ranks. This has additional communication overhead relative to the normal
     *  gather call, so use gather if you can guarantee that your data's size
     *  is consistent.
     *
     *  This method honors the type traits stated in the (TODO: Add link when
     *  the documentation is done) section.
     *
     *  This call is ultimately equivalent to calling MPI_Allgatherv.
     *
     *  @tparam T The qualified type of the data to gather.
     *
     *  @param[in] input This process's contribution to the gather operation.
     *                   The size of input (in bytes) can vary from rank to
     *                   rank.
     *
     *  @return The gathered data. If @p T needs to be serialized the result
     *          is a std::vector<T>, otherwise it's an object of type @p T.
     */
    template<typename T>
    all_gather_return_type<T> gatherv(T&& input) const;

    // -------------------------------------------------------------------------
    // -- Reduce
    // -------------------------------------------------------------------------

    /// Type returned by rooted reduce
    template<typename T>
    using reduce_return_type = std::optional<std::decay_t<T>>;

    /// Type returned by all reduce
    template<typename T>
    using all_reduce_return_type = typename reduce_return_type<T>::value_type;

    /** @brief Reduces an array, and collects the result on a root process
     *
     *  In a reduction operation involving @f$P@f$ processes, process @f$i@f$
     *  starts with an @f$N@f$-element array @f$A_i@f$. The result, @f$R@f$, is
     *  also an @f$N@f$-element array. The @f$j@f$-th element or @f$R@f$ is
     *  given by:
     *
     *  @f[
     *    R[j] = \bigotimes_{i=1}^P A_i[j],
     *  @f]
     *
     *  where @f$\bigotimes@f$ is a stand in for whatever reduction operation
     *  was specified, *e.g.*, if the reduction operation was summation, @f$R@f$
     *  is given by:
     *
     *  @f[
     *    R[j] = \sum_{i=1}^P A_i[j],
     *  @f]
     *
     *  Note that the reduction occurs across the process index and NOT across
     *  the element index. If the goal is to, for example, sum all of the
     *  @f$N@f$ elements in the @f$P@f$ arrays to get a single element, then one
     *  must either sum the @f$N@f$ elements together prior to the reduction or
     *  one must sum the resulting @f$N@f$ elements together after the
     *  reduction.
     *
     *  This overload of reduce will only collect the result to process @p root.
     *  See the other overload of reduce if you want all processes to have a
     *  copy.
     *
     *  @tparam T The qualified type of the array being reduced. @p T is assumed
     *            to possibly be a cv-qualified and/or reference to an object of
     *            type U. U is assumed to be a contiguous container whose
     *            elements map to a known MPI data type. If the elements are not
     *            a known MPI data type, or if @p U needs to be serialized, a
     *            static assert will be tripped.
     *
     *  @tparam Fxn The qualified type of the reduction functor. @p Fxn is
     *              assumed to possibly be a cv-qualified and/or reference to a
     *              functor. The functor is assumed to be an instantiation of
     *              a functor in the C++ standard library that maps to a known
     *              MPI operation, *e.g.*, std::plus. A static assert will be
     *              raised if the functor does not map to a known MPI operation.
     *
     *  @param[in] input The array we are reducing.
     *  @param[in] fxn   The functor to use for the reduction.
     *  @param[in] root  The zero-based rank of the process to collect the
     *                   result on.
     *
     *  @return On the root process the result will be a std::optional which
     *          holds an array whose elements are obtained by applying @p fxn
     *          across the process index (see description). On all other
     *          processes the resulting std::optional will be empty.
     */
    template<typename T, typename Fxn>
    reduce_return_type<T> reduce(T&& input, Fxn&& fxn, size_type root) const;

    /** @brief Reduces an array, and collects the result on each process.
     *
     *  In a reduction operation involving @f$P@f$ processes, process @f$i@f$
     *  starts with an @f$N@f$-element array @f$A_i@f$. The result, @f$R@f$, is
     *  also an @f$N@f$-element array. The @f$j@f$-th element or @f$R@f$ is
     *  given by:
     *
     *  @f[
     *    R[j] = \bigotimes_{i=1}^P A_i[j],
     *  @f]
     *
     *  where @f$\bigotimes@f$ is a stand in for whatever reduction operation
     *  was specified, *e.g.*, if the reduction operation was summation, @f$R@f$
     *  is given by:
     *
     *  @f[
     *    R[j] = \sum_{i=1}^P A_i[j],
     *  @f]
     *
     *  Note that the reduction occurs across the process index and NOT across
     *  the element index. If the goal is to, for example, sum all of the
     *  @f$N@f$ elements in the @f$P@f$ arrays to get a single element, then one
     *  must either sum the @f$N@f$ elements together prior to the reduction or
     *  one must sum the resulting @f$N@f$ elements together after the
     *  reduction.
     *
     *  This overload of reduce will collect the result to every process. See
     *  the other overload of reduce if you only need the result on one process.
     *
     *  @tparam T The qualified type of the array being reduced. @p T is assumed
     *            to possibly be a cv-qualified and/or reference to an object of
     *            type U. U is assumed to be a contiguous container whose
     *            elements map to a known MPI data type. If the elements are not
     *            a known MPI data type, or if @p U needs to be serialized, a
     *            static assert will be tripped.
     *
     *  @tparam Fxn The qualified type of the reduction functor. @p Fxn is
     *              assumed to possibly be a cv-qualified and/or reference to a
     *              functor. The functor is assumed to be an instantiation of
     *              a functor in the C++ standard library that maps to a known
     *              MPI operation, *e.g.*, std::plus. A static assert will be
     *              raised if the functor does not map to a known MPI operation.
     *
     *  @param[in] input The array we are reducing.
     *  @param[in] fxn   The functor to use for the reduction.
     *
     *  @return On all processes the result will be an array whose elements are
     *          obtained by applying @p fxn across the process index (see
     *          description).
     */
    template<typename T, typename Fxn>
    all_reduce_return_type<T> reduce(T&& input, Fxn&& fxn) const;

private:
    /// Code factorization for determining if m_pimpl_ is not null
    bool has_pimpl_() const noexcept;

    /// if has_pimpl_() then returns the PIMPL, otherwise throws.
    const pimpl_type& pimpl_() const;

    /// Type used to make passing the root parameter optional
    using opt_root_t = std::optional<size_type>;

    /** @brief Code factorization for the two public templated gather methods.
     *
     * The "_t_" prevents this from getting called recursively when it tries to
     * call  the binary versions.
     *
     * @tparam T The type we are gathering.
     *
     * @param[in] input The object being sent from this process.
     * @param[in] r     An optional optionally containing the rank of the root
     *                  process. @p r should be set for normal gather calls and
     *                  unset for all gather calls.
     */
    template<typename T>
    gather_return_type<T> gather_t_(T&& input, opt_root_t r) const;

    /// Code factorization for the two public templated gatherv methods.
    template<typename T>
    gather_return_type<T> gatherv_t_(T&& input, opt_root_t r) const;

    /// Code factorization for the two public template reduce methods
    template<typename T, typename Fxn>
    reduce_return_type<T> reduce_t_(T&& input, Fxn&& fxn,
                                    opt_root_t root) const;

    // -------------------------------------------------------------------------
    // -- Binary-Based MPI Operations
    // -------------------------------------------------------------------------

    /// Wraps a call to m_pimpl_->gather(data, root)
    binary_gather_return gather_(const_binary_reference data,
                                 opt_root_t root) const;

    /// Wraps a call to m_pimpl_->gather(in_data, out_buffer, root)
    void gather_(const_binary_reference in_data, binary_reference out_buffer,
                 opt_root_t root) const;

    /// Wraps a call to m_pimpl_->gatherv(in_data, root);
    binary_gatherv_return gatherv_(const_binary_reference data,
                                   opt_root_t root) const;

    /// The object actually implementing *this
    pimpl_pointer m_pimpl_;
};

} // namespace parallelzone::mpi_helpers

#include "commpp.ipp"
