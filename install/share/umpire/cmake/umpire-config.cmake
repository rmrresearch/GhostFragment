##############################################################################
# Copyright (c) 2016-21, Lawrence Livermore National Security, LLC and Umpire
# project contributors. See the COPYRIGHT file for details.
#
# SPDX-License-Identifier: (MIT)
##############################################################################
get_filename_component(UMPIRE_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(UMPIRE_INCLUDE_DIRS "/Users/isaacvanorman/nwchemex/GhostFragment/install/include")

if (NOT TARGET camp)
  if (NOT DEFINED camp_DIR)
    set(camp_DIR /Users/isaacvanorman/nwchemex/GhostFragment/install/lib/cmake/camp)
  endif ()
  find_package(camp REQUIRED
    NO_DEFAULT_PATH
    PATHS ${camp_DIR}
    ${camp_DIR}/lib/cmake/camp
  )
endif ()

set(Umpire_VERSION_MAJOR  6)
set(Umpire_VERSION_MINOR 0)
set(Umpire_VERSION_PATCH 0)
set(Umpire_VERSION_RC "f9640e0f")

include("${UMPIRE_CMAKE_DIR}/umpire-targets.cmake")
