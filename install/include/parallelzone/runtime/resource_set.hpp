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
#include "parallelzone/hardware/ram/ram.hpp"
#include "parallelzone/logging/logger.hpp"
#include <memory>

namespace parallelzone::runtime {

namespace detail_ {
class ResourceSetPIMPL;
}

/** @brief A set of runtime resources.
 *
 *  We assume that when the program is started it has a finite amount of
 *  resources (CPUs, GPUs, memory, etc.) available to it. Furthermore, we
 *  assume that those resources are somehow partitioned into sets (in most, if
 *  not all, cases this is done by a job scheduler). The ResourceSet class
 *  is a runtime abstraction for interacting with one of these sets of
 *  resources.
 *
 *  In MPI terms, a ResourceSet maps to an MPI rank. In conventional MPI
 *  workflows, one gets the rank of the local process, determines what resources
 *  the local process has, and then interacts with the resources. This class
 *  aims to cut out the middle man, by providing direct access to the locally
 *  accessible resources.
 *
 *  ResourceSet instances can be null. Null instances are affiliated with
 *  MPI_COMM_NULL, have an MPI rank of MPI_PROC_NULL, and contain zero
 *  resources. Null instances are typically used as placeholders and have
 *  little to no utility in an actual parallel computation.
 *
 *  ResourceSet instances can be empty meaning that it has no resources. All
 *  null ResourceSet instances are empty; however, an empty resource set may
 *  be affiliated with a non-null MPI communicator and thus have a non-null
 *  rank. At the moment it is not possible to generate a ResourceSet which is
 *  non-null and empty, but when logical partitioning is implemented this will
 *  change.
 */
class ResourceSet {
public:
    /// Unsigned type used for offsets and indexing
    using size_type = std::size_t;

    /// Type of the object representing RAM
    using ram_type = hardware::RAM;

    /// Type of a read-only reference to the RAM
    using const_ram_reference = const ram_type&;

    /// The type of the class implementing the ResourceSet
    using pimpl_type = detail_::ResourceSetPIMPL;

    /// The type of a pointer to the PIMPL
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    /// Type of a Logger
    using logger_type = Logger;

    /// Type of a read/write reference to a logger_type object
    using logger_reference = logger_type&;

    /** @brief Creates a null ResourceSet.
     *
     *  The ResourceSet created by this ctor has no resources and is affiliated
     *  with the null MPI communicator.The resulting ResourceSet is more or
     *  less a placeholder. Assigning to a null ResourceSet is presently the
     *  only way to make it non-null.
     *
     *  @throw None No throw guarantee.
     */
    ResourceSet() noexcept;

    /** @brief Creates a ResourceSet with the provided state
     *
     *  Initializing ResourceSets is an implementation detail of ParallelZone.
     *  The actual initialization is done in the source files where the
     *  declaration of the PIMPL is visible. The initialization works by
     *  initializing a PIMPL and then using this ctor to build the ResourceSet.
     *
     *  @param[in] pimpl The state for the newly created ResourceSet.
     *
     *  @throw None No throw guarantee.
     */
    ResourceSet(pimpl_pointer pimpl) noexcept;

    /** @brief Makes a new ResourceSet which is a deep copy of @p other
     *
     *  ResourceSets are views of the physical resources. When you deep copy
     *  a ResourceSet you are deep copying the views of those resources. In
     *  other words, if you deep copy *this you're not going to double the
     *  physical memory of your computer, you will however have two interfaces
     *  to that memory which can be used independently of one another.
     *
     *  @param[in] other The ResourceSet we are copying.
     *
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL. Strong
     *                        throw guarantee.
     */
    ResourceSet(const ResourceSet& other);

    /** @brief Creates a new ResourceSet by taking the state from @p other
     *
     *  This ctor creates a new ResourceSet by transferring the state in
     *  @p other to *this.
     *
     *  @param[in,out] other The ResourceSet we are transferring the state from.
     *                       After this operation @p other will be in a state
     *                       consistent with default initialization.
     *
     *  @throw None No throw guarantee
     */
    ResourceSet(ResourceSet&& other) noexcept;

    /** @brief Overrides the state of *this with a copy of the state in @p rhs
     *
     *  This method will release the state held in *this (freeing it and in
     *  turn invalidating all references to it) and replace it with a deep
     *  copy of the state in @p rhs.
     *
     *  @param[in] rhs The instance whose state is being copied.
     *
     *  @return *this with its state set to a copy of the state in @p rhs.
     *
     *  @throw std::bad_alloc if there is a problem allocating the copy. Strong
     *                        throw guarantee.
     */
    ResourceSet& operator=(const ResourceSet& rhs);

    /** @brief Transfers ownership of @p rhs's resources to *this
     *
     *  This method will override the state of *this (releasing it and
     *  invalidating all references to it) and then transfer ownership of
     *  @p rhs's state to *this.
     *
     *  @param[in,out] rhs The ResourceSet we are taking the resources from.
     *                     After this operation @p rhs will be in a state
     *                     consistent with default initialization.
     *
     *  @return *this, after assigning @p rhs's state to *this.
     *
     *  @throw None No throw guarantee.
     */
    ResourceSet& operator=(ResourceSet&& rhs) noexcept;

    /// Default no-throw dtor
    ~ResourceSet() noexcept;

    // -------------------------------------------------------------------------
    // -- Getters
    // -------------------------------------------------------------------------

    /** @brief The MPI rank of the process who owns *this
     *
     *  ResourceSets contain the resources available to a process. In MPI
     *  processes are identified by their ranks. This method will return the
     *  MPI rank of the process which owns *this. The rank ordering is
     *  determined by the MPI communicator in the RuntimeView which owns *this.
     *
     *  If this is a null resource set, the resulting rank is MPI_PROC_NULL.
     *
     *  @return The rank of the process who owns *this.
     *
     *  @throw None No throw guarantee.
     */
    size_type mpi_rank() const noexcept;

    /** @brief Determines if the resource set is owned by the current process
     *
     *  Each ResourceSet is associated with a processes. This method can
     *  be used to determine if the current process owns *this.
     *
     *  @return True if the current process owns *this and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool is_mine() const noexcept;

    /** @brief Does this ResourceSet have RAM?
     *
     *  This method is used to determine if *this has RAM associated with it.
     *  As a caveat, this method indicates whether calling `ram()` will throw
     *  or not (it will throw if *this has no RAM instance); this method
     *  returning true does not guarantee that the RAM instance returned by
     *  `ram()` is non-empty.
     *
     *  @return True if this ResourceSet has RAM and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool has_ram() const noexcept;

    /** @brief Retrieves the RAM for this resource set.
     *
     *  From the perspective of the user of this class all of the RAM accessible
     *  to it is local, so there's only one RAM object. If under the hood this
     *  is not the case (e.g., we're treating RAM spread across nodes as a
     *  single entity) it's up to the RAM class to make that work with the
     *  specified API.
     *
     *  @return A read-only reference to the RAM.
     *
     *  @throw std::out_of_range if the instance does not have RAM. Strong
     *                           throw guarantee.
     */
    const_ram_reference ram() const;

    /** @brief Gets the process-local logger for this ResourceSet
     *
     * This logger can be used to print process-local messages. In general,
     * process-local messages are messages whose content varies from process
     * to process. For example, printing the local part of a distributed
     * object.
     *
     * @returns Logger instance to use for logging process-local data.
     */
    logger_reference logger() const;

    // -------------------------------------------------------------------------
    // -- Utility methods
    // -------------------------------------------------------------------------

    /** @brief True if *this is a null ResourceSet
     *
     *  A null ResourceSet is affiliated with a null MPI communicator and has
     *  no resources.
     *
     *  @return True if this ResourceSet is null and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool null() const noexcept;

    /** @brief True if *this contains no resources
     *
     *  An empty ResourceSet has no resources and may or may not be affiliated
     *  with an MPI communicator. All null ResourceSet instances are empty,
     *  but not all empty ResourceSets are null.
     *
     *  @return True if this ResourceSet is empty (has no resources) and false
     *          otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool empty() const noexcept;

    /** @brief Exchanges the state of two ResourceSet objects
     *
     *  This method will put the state of *this in @p other and take the state
     *  of @p other and put it in *this.
     *
     *  @param[in,out] other The ResourceSet we are swapping state with. After
     *                       this call @p other will contain the state which
     *                       was previously in *this.
     *
     *  @throw None No throw guarantee.
     */
    void swap(ResourceSet& other) noexcept;

    /** @brief Determines if *this is value equal to @p rhs.
     *
     *  Two ResourceSets are value equal if they contain the same resources
     *  and belong to the same process.
     *
     *  @return True if *this is value equal to @p rhs, and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const ResourceSet& rhs) const noexcept;

    /** @brief Determines if *this is different from @p rhs
     *
     *  This function simply negates a value equality comparison. See the
     *  documentation for operator== for the definition of value equality.
     *
     *  @return False if *this is value equal to @p rhs, and true otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator!=(const ResourceSet& rhs) const noexcept;

private:
    /// True if this instance has a PIMPL, and false otherwise
    bool has_pimpl_() const noexcept;

    /// Factorization for asserting the instance has a PIMPL
    void assert_pimpl_() const;

    /// The object actually implementing the ResourceSet
    pimpl_pointer m_pimpl_;
};

} // namespace parallelzone::runtime
