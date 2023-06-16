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
#include <parallelzone/logging/logger.hpp>

namespace parallelzone {

class LoggerFactory {
public:
    /// Type used for passing MPI ranks
    using mpi_rank_type = std::size_t;

    /// Type used for logger objects
    using logger_type = Logger;

    /** @brief Creates the default program-wide logger for a specific process
     *
     *  This method wraps the process of creating the default global logger.
     *  In general the state of the global logger is process-specific (for
     *  example only the root process may log). Users who want to stay
     *  synchronized with whatever ParallelZone's default global logger is,
     *  should use this method to get the global logger. If you instead want
     *  to always have a specific logger, use a different construction method.
     *
     *  @param[in] rank The process rank we are creating the program-wide
     *                  logger for. @p rank need not be the current process's
     *                  rank, i.e., it's okay to build a different rank's
     *                  logger locally.
     *
     *  @note Although we allow building a logger for a rank other than the
     *        current process, the resulting logger is not guaranteed to be
     *        usable from the current process. That said, it should work,
     *        but again no guarantees...
     *
     *  @return The logger for the requested MPI rank.
     */
    static logger_type default_global_logger(mpi_rank_type rank);
};

} // namespace parallelzone
