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

#include <parallelzone/mpi_helpers/commpp/commpp.hpp>
#include <parallelzone/runtime/resource_set.hpp>

namespace parallelzone::runtime {
namespace detail_ {
class RuntimeViewPIMPL;
}

/** @brief A view of the execution environment.
 *
 *  The runtime (environment) is where a program runs. The RuntimeView class
 *  provides an API for querying properties of the runtime. The "view" part of
 *  the name signifies that a RuntimeView instance does not own the state, but
 *  only aliases it.
 *
 *  Users should be aware that a RuntimeView instance may only be a slice of the
 *  actual runtime (either because other programs are running on the computer
 *  or because another part of the program is using resources).
 *
 *  In MPI terms think of RuntimeView as an intra-communicator paralleling
 *  MPI_COMM_WORLD; however, the underlying MPI_Comm need not be MPI_COMM_WORLD.
 *
 *  @note RuntimeView uses RAII (resource acquisition is initialization) to
 *        manage MPI. This means that if you do supply a handle to an
 *        already initialized MPI runtime, then RuntimeView will assume
 *        it is using MPI_COMM_WORLD and will initialize MPI if
 *        necesary. In the event that RuntimeView does initialize MPI,
 *        it is also responsible for tearing-down MPI when the last
 *        reference to MPI goes out of scope. Internally, this is
 *        managed with a shared_ptr. So if you want to ensure that MPI
 *        is not finalized while you're doing something, make sure you hold on
 *        to a RuntimeView.
 */
class RuntimeView {
public:
    /// Unsigned integral type used for counting, offsets, and indexing
    using size_type = std::size_t;

    /// Type Runtime uses for handles to MPI communicators
    using mpi_comm_type = MPI_Comm;

    /// Type used to pass the program's argument count (i.e., "argc")
    using argc_type = int;

    /// Type used to pass the program's arguments (i.e., "argv")
    using argv_type = char**;

    /// Type of a set of resources
    using resource_set_type = ResourceSet;

    /// Type of a read/write reference to a resource_set_type object
    using resource_set_reference = resource_set_type&;

    /// Type of a read-only reference to a resource_set_type object
    using const_resource_set_reference = const resource_set_type&;

    /// Type of a Logger
    using logger_type = Logger;

    /// Type of a read/write reference to a logger_type object
    using logger_reference = logger_type&;

    // TODO: Write an iterator class
    /// Type of an interator over a range of resource_set_type instances
    using const_iterator = int;

    /// Pair of iterators to a read-only range of resource_set_type
    using const_range = std::pair<const_iterator, const_iterator>;

    /// Type of the RAM class, ultimately set by ResourceSet::ram_type
    using ram_type = resource_set_type::ram_type;

    /// Ultimately a typedef of ResourceSet::const_ram_reference
    using const_ram_reference = resource_set_type::const_ram_reference;

    /// Type of the class managing the state of this class
    using pimpl_type = detail_::RuntimeViewPIMPL;

    /// Type of a pointer to the PIMPL
    using pimpl_pointer = std::shared_ptr<pimpl_type>;

    // -------------------------------------------------------------------------
    // -- Ctors, Assignment, Dtor
    // -------------------------------------------------------------------------

    /** @brief Creates a RuntimeView which wraps MPI_COMM_WORLD.
     *
     *  The default ctor is a special case of the argc/argv ctor which assumes
     *  that argc is 0 and argv is a nullptr. See the argc/argv ctor's
     *  description for more details.
     *
     */
    RuntimeView();

    /** @brief Initializes the runtime given the arguments to `main`
     *
     *  In C/C++ the `main` function takes two positional arguments, @p argc
     *  and @p argv. This ctor simply forwards @p argc and @p argv to the
     *  primary ctor (and sets `comm = MPI_COMM_WORLD`). See the primary ctor's
     *  description for more details.
     *
     *  @param[in] argc The number of arguments the program was called with.
     *                  In conventional usage, @p argc is >= 1, but a value of 0
     *                  is allowed if @p argv is a nullptr.
     *  @param[in] argv The argument to the program. In conventional usage
     *                  @p argv is minimally the name of the program. @p argv
     *                  may be a nullptr if @p argc is 0.
     */
    RuntimeView(argc_type argc, argv_type argv);

    /** @brief Creates a RuntimeView which aliases the provided MPI runtime.
     *
     *  This ctor is primarily meant for initializing a RuntimeView instance
     *  after MPI has already been started. This ctor dispatches to the primary
     *  ctor by passing `argc = 0` and `argv = nullptr`. See the primary ctor
     *  documentation for more details.
     *
     *  @param[in] comm The MPI_Comm this RuntimeView should alias.
     */
    explicit RuntimeView(mpi_comm_type comm);

    /** @brief Primary ctor for creating a new RuntimeView
     *
     *  Most of the other ctors dispatch to this ctor. The ctor first determines
     *  if CommPP has been initialized. If CommPP has not been initialized,
     *  CommPP will be initialized and the resulting RuntimeView instance will
     *  be responsible for tearing down CommPP when it is no longer in use
     *  (as determined by an internal counter). After ensuring CommPP
     *  is initialized, this ctor will collect information about the computer
     *  and initialize the internal ResourceSets with said information.
     *
     *  @param[in] argc The number of arguments the program was called with.
     *                  In conventional usage, @p argc is >= 1, but a value of 0
     *                  is allowed if @p argv is a nullptr.
     *  @param[in] argv The argument to the program. In conventional usage
     *                  @p argv is minimally the name of the program. @p argv
     *                  may be a nullptr if @p argc is 0.
     *  @param[in] comm The MPI_Comm this RuntimeView should alias.
     *
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL. Strong
     *                        throw guarantee (not actually sure this is the
     *                        case if we also initialized MPI).
     */
    RuntimeView(argc_type argc, argv_type argv, mpi_comm_type comm);

    /** @brief Ctor for explicitly setting the state of the RuntimeView.
     *
     *  This ctor is primarily exposed for unit testing purposes. Users of
     *  ParallelZone do not have access to the PIMPL's API and thus can not
     *  actually create a PIMPL instance in order to call this ctor.
     *
     *  @param[in] pimpl The state for the RuntimeView.
     *
     *  @throw None No throw guarantee.
     */
    RuntimeView(pimpl_pointer pimpl) noexcept;

    /** @brief Make a new RuntimeView which aliases the same resources as *this
     *
     *  RuntimeView instances behave a bit like a shared_ptr. The copy ctor is
     *  deep in the sense that the new instance is not an alias of the original
     *  RuntimeView, but shallow in the sense that the new RuntimeView aliases
     *  the same resources as the original.
     *
     *  @param[in] other The RuntimeView we are copying.
     *
     *  @throw None No throw guarantee.
     */
    RuntimeView(const RuntimeView& other) noexcept;

    /** @brief Makes *this alias the same resources as @p rhs
     *
     *  This method will set the internal state so that it aliases the same
     *  resources as @p rhs. This will decrement the reference count to the
     *  resources *this holds before the operation and increase the reference
     *  count to the resources in @p rhs. If the reference count to the
     *  resources in *this reaches 0 as a result of the aforementioned
     *  decrement, they will be released (possibly finalizing MPI).
     *
     *  @param[in] rhs The RuntimeView whose resources we want *this to alias
     *
     *  @return *this after making *this point to the same resources as @p rhs.
     *
     *  @throw None No throw guarantee.
     */
    RuntimeView& operator=(const RuntimeView& rhs) noexcept;

    /** @brief Transfers ownership of state in @p other to *this.
     *
     *  This ctor will initialize *this with the state that is in @p other. The
     *  state will be taken by move semantics.
     *
     *  @param[in,out] other The instance whose state is being taken. After this
     *                 operation @p other will be a state consistent with
     *                 default initialization.
     *
     *  @throw None No throw guarantee.
     */
    RuntimeView(RuntimeView&& other) noexcept;

    /** @brief Overwrites the state in *this with the state in @p rhs.
     *
     *  This method will release the internal state held by *this and replace
     *  it with the state help in @p rhs. Otherwise this method behaves
     *  analogous to the move ctor.
     *
     *  @param[in,out] rhs The instance whose state is being takne. After this
     *                 operation @p rhs will be in a state consistent with
     *                 default initialization.
     *
     *  @return The current instance after *this takes ownwerhsip of the state
     *          in @p rhs.
     *
     *  @throw None No throw guarantee.
     */
    RuntimeView& operator=(RuntimeView&& rhs) noexcept;

    /** @brief Releases the present RuntimeView instance
     *
     *  RuntimeViews behave somewhat like a shared_ptr. Copies of a RuntimeView
     *  increment an internal counter. As long as the inernal counter is
     *  non-zero the resources (i.e., MPI) will not be finalized.
     *  When the counter reaches zero (and assuming the original RuntimeView
     *  actually initialized MPI) MPI will be finalized.
     *
     *  @throw None No throw guarantee.
     */
    ~RuntimeView() noexcept;

    // -------------------------------------------------------------------------
    // -- Getters
    // -------------------------------------------------------------------------

    /** @brief Returns the MPI communicator powering *this
     *
     *  ParallelZone assumes that MPI is powering the runtime. This method is
     *  used to retrieve the MPI communicator which is managing the resources
     *  in this RuntimeView.
     *
     *  @note A view of the null runtime returns `MPI_COMM_NULL`.
     *
     *  @return An object identifying which MPI communicator powers *this.
     *
     *  @throw None No throw guarantee.
     */
    mpi_comm_type mpi_comm() const noexcept;

    /** @brief The number of resource sets in this instance.
     *
     *  The resources available to the runtime are divvied up into resource
     *  sets. This method will return the number of resource sets in the
     *  runtime. It should be noted that resource sets need not be orthogonal.
     *  That is to say, a resource may be shared among more than one set.
     *
     *  @note A view of the null runtime contains 0 resource sets; however, it
     *        is also possible for a non-null runtime to have 0 resource sets
     *        so `size() == 0` is not a sufficient check for null-ness. Use
     *        `null()` instead.
     *
     *  @return The number of resource sets in this view.
     *
     *  @throw None No throw guarantee.
     */
    size_type size() const noexcept;

    /** @brief Determines if *this is a view of the null runtime.
     *
     *  @return True if *this is a view of the null runtime and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool null() const noexcept;

    /** @brief Used to determine if this RuntimeView aliases the resources that
     *         started mpi.
     *
     *  If a RuntimeView starts MPI it's responsible for making sure MPI
     *  is finalized. The finalization happens in the dtor when all references
     *  to the original resources are out of scope. This method can be used to
     *  determine if letting the current RuntimeView go out of scope will
     *  decrement the reference count (if the return is true) or not (if the
     *  return is false).
     *
     *  @note A null runtime did not start MPI and will return false.
     *
     *  @return True if the aliased resources started MPI and false
     *          otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool did_i_start_mpi() const noexcept;

    /** @brief Returns the @p i-th resource set in a read-only state.
     *
     *  This method behaves identical to the non-const version, except that the
     *  resulting resource set is read-only.
     *
     *  @param[in] i The 0-based offset of the desired resource set. @p i is
     *               expected to be in the range [0, size()).
     *
     *  @return A read-only reference to the requested resource set.
     *
     *  @throw std::out_of_range if @p i is not in the range [0, size()).
     *                           Strong throw guarantee.
     */
    const_resource_set_reference at(size_type i) const;

    /** @brief Used to determine if the current process is part of *this
     *
     *  Each RuntimeView is meant to be treated as the "full" set of resources
     *  available. In practice, it need not actually be the full set, hence the
     *  quotes. After partitioning a RuntimeView into sub-views, each process
     *  can only directly see the resources in the sub-view it was assigned to.
     *  This method is used to determine if the current process was assigned to
     *  *this.
     *
     *  In MPI terms, if *this is wrapping MPI_COMM_WORLD than the current
     *  process is always part of *this. However, for MPI intra-comms which are
     *  proper subsets of MPI_COMM_WORLD, a particular process need not be in
     *  the intra-comm (and by definition at least one is not). This method
     *  tells you if the current process is in the wrapped MPI_Comm or not.
     *
     *  @return True if the current process is in the communicator and false
     *          otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool has_me() const noexcept;

    /** @brief Finds the resource set for the current process.
     *
     *  Typically a process can only directly access some of the total resources
     *  available. This method returns the resource set the current process has
     *  direct access to.
     *
     *  @return The resource set the current process has direct access to.
     *
     *  @throw std::out_of_range if the current process is not part of *this.
     *                           Strong throw guarantee.
     */
    const_resource_set_reference my_resource_set() const;

    /** @brief Determines the number of ResourceSets a specific RAM instance
     *         belongs to.
     *
     *  ResourceSet instances need not be disjoint. In turn RAM may be locally
     *  accessible to more than one ResourceSet. This method allows you to
     *  determine how many of the ResourceSets in *this have access to the
     *  specified RAM instance.
     *
     *  @param[in] ram The chunk of RAM we are looking for. @p ram may be local
     *                 or remote relative to my_resource_set().
     *
     *  @throw std::bad_alloc Looking for the RAM instance requires us to check
     *                        each ResourceSet. At the moment this requires us
     *                        to create ResourceSets for each rank. An exception
     *                        may be raised if the creation of a ResourceSet
     *                        fails. Strong throw guarantee.
     */
    size_type count(const_ram_reference ram) const;

    /** @brief Returns the program-wide logger
     *
     *  The program-wide logger is used for logging replicated data and state
     *  that all processes in *this agree on. To log process-local data use
     *  the logger provided by the ResourceSet objects.
     *
     *  @return A read/write reference to the program-wide logger.
     *
     *  @throw std::runtime_error if *this does not have a PIMPL. Strong throw
     *                            guarantee.
     */
    logger_reference logger() const;

    // -------------------------------------------------------------------------
    // -- MPI all-to-all methods
    // -------------------------------------------------------------------------

    /** @brief Performs an all gather on the provided data.
     *
     *  In a gather operation involving `N` processes, the data from each
     *  process will be concatenated into an `N` element array such that the
     *  `i`-th piece of data came from the process with rank `i`. It should be
     *  noted that the data sent from each process needs to be a single object,
     *  but that object can contain multiple elements. For example,
     *  `T == std::vector<double>` sends a single `std::vector` instance which
     *  (may) contains multiple `double` values.
     *
     *  N.B. To use this method each process must send the same number of bytes
     *  (not just objects). If you can not guarantee that use gatherv, which
     *  will work properly when each process may send a different amount of
     *  data.
     *
     *  This call is ultimately equivalent to calling MPI_Allgather.
     *
     *  @tparam T The qualified (cv and/or reference) type of @p input. @p T
     *            will be deduced by the compiler and need not be specified.
     *
     *  @param[in] input The data local to the current ResourceSet.
     *
     *  @return A local copy of the gathered data.
     */
    template<typename T>
    auto gather(T&& input) const {
        return comm_().gather(std::forward<T>(input));
    }

    /** @brief Performs an all gatherv on the provided data.
     *
     *  This method behaves identically to gather except that each process may
     *  send a different number of bytes. There is a slight overhead
     *  associated with gatherv vs. gather, so if you can guarantee that each
     *  process sends the same number of bytes use gather.
     *
     *  This call is ultimately equivalent to calling MPI_Allgatherv
     *
     *  @tparam T The qualified (cv and/or reference) type of @p input. @p T
     *            will be deduced by the compiler and need not be specified.
     *
     *  @param[in] input The local data being sent by the current process.
     *
     *  @return A local copy of the gathered data.
     */
    template<typename T>
    auto gatherv(T&& input) const {
        return comm_().gatherv(std::forward<T>(input));
    }

    /** @brief Performs an all reduce on the data.
     *
     * In a reduction operation involving @f$P@f$ processes, process
     * @f$i@f$ starts with an @f$N@f$-element array @f$A_i@f$. The result,
     * @f$R@f$, is also an @f$N@f$-element array. The @f$j@f$-th element or
     * @f$R@f$ is given by:
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
     *  N.B. This method assumes that each process sends the same number of
     *  bytes.
     *
     *  This method is equivalent to MPI_Allreduce.
     *
     *  @param[in] input The data local to the current ResourceSet.
     *  @param[in] op    The functor being used to reduce the data.
     *
     *  @return A local copy of the result of the reduction.
     *
     */
    template<typename T, typename Fxn>
    auto reduce(T&& input, Fxn&& op) const {
        return comm_().reduce(std::forward<T>(input), std::forward<Fxn>(op));
    }

    // -------------------------------------------------------------------------
    // -- Utility methods
    // -------------------------------------------------------------------------

    /** @brief Swaps the state of *this with @p other.
     *
     *  This method simply swaps the pointers of the PIMPLs. As such all
     *  references, etc. to state in *this will remain valid, except that after
     *  this call the references now refer to state in @p other.
     *
     *  @param[in] other The instance to swap *this's state with.
     *
     *  @throw None No throw guarantee.
     */
    void swap(RuntimeView& other) noexcept;

    /** @brief Determines if @p rhs is value equal to *this.
     *
     *  Two RuntimeView instances are value equal if they wrap the same
     *  MPI_Comm and have the same resources.
     *
     *  @param[in] rhs The RuntimeView we are comparing to.
     *
     *  @return True if *this is value equal to @p rhs and false otherwise.
     *
     *  @throw None No Throw guarantee.
     */
    bool operator==(const RuntimeView& rhs) const;

private:
    /// Returns the MPI communicator as our internal CommPP object
    mpi_helpers::CommPP comm_() const;

    /** @brief Code factorization for ensuring *this is not null.
     *
     *  @throw std::runtime_error if *this is a view of the null runtime. Strong
     *         throw guarantee.
     */
    void not_null_() const;

    /** @brief Code factorization for ensuring @p i is in the range [0, size())
     *
     *  @param[in] i The index to bounds check.
     *
     *  @throw std::out_of_range if @p i is not in the range [0, size()).
     */
    void bounds_check_(size_type i) const;

    /// Type of a modifiable reference to the PIMPL
    using pimpl_reference = pimpl_type&;

    /// Type of a read-only reference to the PIMPL
    using const_pimpl_reference = const pimpl_type&;

    /** @brief Calls not_null_() and returns the PIMPL.
     *
     *  @return A modifiable reference to the PIMPL.
     *
     *  @throw std::runtime_error if *this is a view of the null runtime.
     *         Strong throw guarantee.
     */
    pimpl_reference pimpl_();

    /** @brief Calls not_null_() and returns the PIMPL.
     *
     *  @return A read-only reference to the PIMPL implementing *this.
     *
     *  @throw std::runtime_error if *this is a view of the null runtime.
     *         Strong throw guarantee.
     */
    const_pimpl_reference pimpl_() const;

    /// Holds the actual state of the Runtime
    pimpl_pointer m_pimpl_;
};

/** @brief Determines if two RuntimeView instances are different.
 *  @relates RuntimeView
 *
 *  Two RuntimeView instances are different if they are not value equal. See
 *  operator== for the definition of value equal.
 *
 *  @param[in] lhs The RuntimeView instance on the left of the operator.
 *  @param[in] rhs The RuntimeView instance on the right of the operator.
 *
 *  @return False if @p lhs is value equal to @p rhs and true otherwise.
 *
 *  @throw None No throw guarantee.
 */
inline bool operator!=(const RuntimeView& lhs, const RuntimeView& rhs) {
    return !(lhs == rhs);
}

} // namespace parallelzone::runtime
