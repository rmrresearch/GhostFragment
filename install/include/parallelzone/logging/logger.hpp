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
#include <ostream>
#include <string>

namespace parallelzone {
namespace detail_ {
/// Logger Implementation Class
class LoggerPIMPL;
} // namespace detail_

/** @brief A class to manage various loggers under a unified API
 *
 *  In our design, developers using ParallelZone determine what records/data to
 *  log by passing them to a logger. The logger then sends the record/data
 *  to a sink, which is responsible for actually logging the record/data.
 *  The Logger class implements the user-facing API for logging records/data.
 *
 *  Developers using ParallelZone can copy/move existing loggers, but in
 *  general they won't be able to make new ones (the exception is a null logger,
 *  which developers can make to prevent logging). This is because it is
 *  ultimately the end-user who determines the logger(s) to use and the choice
 *  is made when setting up RuntimeView and the ResourceSets in it.
 */
class Logger {
public:
    /** @brief How important a particular log message is.
     *
     *  Each log message is assigned a severity which indicates how important
     *  that message is. These severities range from trace (least important)
     *  to critical (most important). It's ultimately up to the person logging
     *  the message to assign the severity, but the general guidance is:
     *
     *  - trace: Over the top verboseness. Logged information is likely only of
     *           interest to developers trying to squash the hardest to find
     *           bugs.
     *  - debug: additional information which is usually only warranted when a
     *           bug occurs.
     *  - info: The base level. Messages used to record provenance and progress.
     *  - warn: Message indicating that the the program is about to do something
     *          outside normal use cases. It's not necessarily wrong, just not
     *          a common request.
     *  - error: Something went wrong, but the program can recover.
     *  - critical: Something went wrong and no recovery is possible, i.e. the
     *              program will now crash.
     */
    enum class severity { trace, debug, info, warn, error, critical };

    /// Type of the object used to implement a Logger instance
    using pimpl_type = detail_::LoggerPIMPL;

    /// Type of a unique_ptr to an object of type pimpl_type
    using pimpl_ptr = std::unique_ptr<pimpl_type>;

    /// Type of a string-based message
    using string_type = std::string;

    /// Type of a read-only reference to a string-based message
    using const_string_reference = const string_type&;

    /// Type of a raw output stream
    using ostream_type = std::ostream;

    /// Type of a read/write reference to an object of type ostream_type
    using ostream_reference = ostream_type&;

    /** @brief Construct a Logger instance without a sink
     *
     *  Loggers created using the default ctor have no sink. Messages logged
     *  to null loggers are lost to time, regardless of the severity level.
     *  Null loggers are primarily used to prevent logging, either because we
     *  only want a certain rank to print or because the user has decided they
     *  do not want logging.
     *
     *  @throw None no throw guarantee
     */
    Logger() noexcept;

    /** @brief Construct a Logger instance from an implementation pointer.
     *
     *  This ctor is used internally when populating the Logger instances
     *  which live in the RuntimeView and ResourceSet classes. Users of
     *  ParallelZone shouldn't (and likely can't without refactoring source
     *  files) call this ctor.
     *
     *  @param[in] p The logger's implementation. @p p is assumed to be set up
     *               prior to calling this ctor.
     *
     *  @throw None no throw guarantee.
     */
    Logger(pimpl_ptr&& p) noexcept;

    /** @brief Deletes the Logger, releasing its state.
     *
     *  Exactly what happens when the Logger is deleted depends on the backend.
     *  Most backends use a reference counted sink. If deleting *this reduces
     *  that count to 0, the sink will usually flush before it itself is
     *  deleted. Again, this behavior is backend specific and its the person
     *  who sets up ParallelZone, at runtime, which gets to make these
     *  decisions.
     *
     *  @throw None no throw guarantee.
     */
    ~Logger() noexcept;

    /** @brief Construct Logger instance via deep copy.
     *
     *  LoggerPIMPL instances expose polymorphic deep copy methods. Exactly what
     *  a deep copy means is implementation dependent. In general, users can
     *  expect a deep copy of a Logger to make deep copies of the meta data
     *  associated with the Logger, but still point to the same sink as the
     *  original Logger.
     *
     *  @param[in] other Logger instance from which to construct *this.
     *
     *  @throw std::bad_alloc if there is a problem allocating the new PIMPL.
     *                        Strong throw guarantee.
     */
    Logger(const Logger& other);

    /** @brief Construct Logger by taking ownership of another's state.
     *
     *  The move ctor simply transfers the ownership of the PIMPL in @p other
     *  to *this.
     *
     * @param[in,out] other Logger instance from which to construct
     *                      this instance. After this operation @p other will
     *                      be equivalent to a null Logger.
     *
     * @throw None No throw guarantee.
     */
    Logger(Logger&& other) noexcept;

    /** @brief Deep copying contents of @p other into *this
     *
     *  This method overwrites the current state of *this with a deep copy of
     *  @p other. The current state of *this is released in the process.
     *  See copy ctor for disclaimers on what constitutes a deep copy.
     *
     *  @param[in] other Logger instance to copy.
     *
     *  @returns   Reference to this instance, after copying @p other.
     *
     *  @throw std::bad_alloc if there is a problem allocating the copy. Strong
     *                        throw guarantee.
     */
    Logger& operator=(const Logger& other);

    /** @brief Move contents of @p other into *this
     *
     *  This method overwrites the current state of *this with the state in
     *  @p other. The current state of *this is released in the process.
     *
     *  @param[in,out] other Logger instance from which to take the state.
     *                       After this operation @p other is in a state
     *                       equivalent to a null logger.
     *
     *  @returns Reference to this instance, after taking the state in @p other.
     *
     *  @throw None No throw guarantee.
     */
    Logger& operator=(Logger&& other) noexcept;

    /** @brief Toggles the severity threshold for logging.
     *
     *  Severities increase in level from trace to critical. This method is
     *  used to set the minimum severity which gets logged. The provided value
     *  is used inclusively, e.g., passing `severity::trace` means all messages
     *  are logged, whereas passing `severity::warn` means only messages
     *  tagged as being `severity::warn`, `severity::error`, or
     *  `severity::critical` are logged.
     *
     *  This method can not be used to disable logging of critical messages. If
     *  you really want to disable all logging use a null logger (default
     *  constructed).
     *
     *  @throw ??? Can throw if the backend throws. Most backends implement this
     *             in a manner which is no-throw guarantee though.
     */
    void set_severity(severity s);

    /** @brief Aliases for calling `log` with the namesake severity.
     *
     *  These methods are convenience functions for calling `log` with the
     *  same severity level as the method. For example calling `trace` is
     *  the same as calling `log` and passing `severity:trace` as the severity
     *  argument. See `log(severity, const_string_reference)` for more
     *  information on using these methods.
     *
     *  @param[in] msg The message to log.
     *
     *  @return *this, after logging @p msg.
     *
     *  @throw ??? Throws if the implementation throws. Same throw guarantee.
     */
    ///@{
    Logger& trace(const_string_reference msg);
    Logger& debug(const_string_reference msg);
    Logger& info(const_string_reference msg);
    Logger& warn(const_string_reference msg);
    Logger& error(const_string_reference msg);
    Logger& critical(const_string_reference msg);
    ///@}

    /** @brief Logs a message to log with the default severity (i.e., info)
     *
     *  This method is equivalent to calling `log(severity::info, msg)`. See
     *  `log(severity, const_string_reference)` for more information.
     *
     *  @param[in] msg Message to log.
     *
     *  @returns Reference to *this, after logging @p msg.
     *
     *  @throws ??? Throws if the implementation throws. Same throw guarantee.
     */
    Logger& log(const_string_reference msg);

    /** @brief Logs a message with the provided severity.
     *
     *  This method is main API for logging. All other logging APIs redirect to
     *  this method. This method will forward the provided severity and
     *  message to the backend. In general the backend will log the message as
     *  long as the current logger's internal threshold for logging is set at
     *  or below @p s. Whether @p msg is logged right away, or queued is
     *  implementation dependent.
     *
     *  If *this is a null logger this method is a no-op.
     *
     *  @param[in] s How important is this message? See the documentation
     *               for the severity enum for more information.
     *
     *  @param[in] msg The message to log.
     *
     *  @return *this after logging @p msg.
     *
     *  @throws ??? Throws if the implementation throws. Same throw guarantee.
     */
    Logger& log(severity s, const_string_reference msg);

    /** @brief Logs a message with info severity, but streaming semantics.
     *
     *  For convenience we allow users to stream log messages. At present
     *  there is no way to change the severity of these messages and they
     *  will always be logged as `severity::info`. Thus this method is
     *  equivalent to `log(severity::info, msg)`. See
     * `log(severity, const_string_reference)` for more detail on using this
     *  method.
     *
     *  @param[in] msg Message to log.
     *
     *  @return *this after logging @p msg.
     *
     *  @throw ??? Throws if the implementation throws. Same throw guarantee.
     */
    Logger& operator<<(const_string_reference msg);

    /** @brief Exchanges the state of two Logger instances.
     *
     *  This method exchanges the state of *this with that in @p other.
     *
     *  @param[in,out] other The instance to exchange state with. After this
     *                       call @p other will contain the state which was
     *                       previously in *this.
     *
     *  @throw None No throw guarantee.
     */
    void swap(Logger& other) noexcept;

    /** @brief Determines if @p rhs is value equal to *this.
     *
     *  This method determines if @p rhs is value equal to *this. Two Logger
     *  objects are value equal if they both are null loggers or if they
     *  contain the same internal state. Value equality for internal state
     *  is implementation dependent, but in general it involves comparing the
     *  meta-data and determining if both loggers have the same sink. If two
     *  loggers compare equal than logging to either of them should have the
     *  same result.
     *
     *  @param[in] rhs The object to compare to *this.
     *
     *  @return True if @p rhs is value equal to *this and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const Logger& rhs) const noexcept;

    /** @brief Determines if @p rhs is different from *this.
     *
     *  We define different as not equal. Thus this method simply negates
     *  operator==. See operator== for the definition of value equal.
     *
     *  @param[in] rhs The object to compare to *this.
     *
     *  @return False if @p rhs is value equal to *this and true otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator!=(const Logger& rhs) const noexcept;

private:
    /// Internal code factorization for checking for a null PIMPL pointer
    bool has_pimpl_() const noexcept;

    /// Pointer to implementation details
    pimpl_ptr m_pimpl_;
};

} // namespace parallelzone
