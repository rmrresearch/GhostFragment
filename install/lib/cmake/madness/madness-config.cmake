# - CMAKE Config file for the MADNESS package
#
# Valid COMPONENTS: world tensor misc tensor linalg tinyxml muparser mra chem
# If MADNESS_FIND_COMPONENTS only contains world, will load the subset of targets
# necessary for MADworld
#
# The following variables are defined:
#  MADNESS_FOUND                - System has the MADNESS package
#  MADNESS_INCLUDE_DIRS         - The MADNESS include directory
#  MADNESS_LIBRARIES            - The MADNESS libraries and their dependencies
#  MADNESS_INSTALL_LIBRARY_DIR  - Where MADNESS libraries will be installed (same for CONFIG files imported from the build and install trees)
#  MADNESS_<COMPONENT>_FOUND    - System has the specified MADNESS COMPONENT
#  MADNESS_<COMPONENT>_LIBRARY  - The MADNESS COMPONENT library
#  MADNESS_F77_INTEGER_SIZE     - The default F77 integer size used for BLAS calls
#  MADNESS_ASSUMES_ASLR_DISABLED - Whether MADNESS assumes ASLR to be disabled
#
# Additionally MADNESS exports the following variables from its dependent packages:
# = LAPACK =
#    LAPACK_LIBRARIES           Libraries providing LAPACK and its dependents
#    LAPACK_INCLUDE_DIRS        Include directories where to locate the header files needed to use LAPACK_LIBRARIES
#    LAPACK_COMPILE_DEFINITIONS Compile definitions needed to use the LAPACK header files
#    LAPACK_COMPILE_OPTIONS     Compile options needed to use the LAPACK header files
# = MPI =
#    MPIEXEC_EXECUTABLE         Executable for running MPI programs
#    MPIEXEC_NUMPROC_FLAG       Flag to pass to MPIEXEC_EXECUTABLE before giving
#                               it the number of processors to run on
#    MPIEXEC_PREFLAGS           Flags to pass to MPIEXEC_EXECUTABLE directly
#                               before the executable to run.
#    MPIEXEC_POSTFLAGS          Flags to pass to MPIEXEC_EXECUTABLE after other flags

# Set package version
set(MADNESS_VERSION "0.10.1")


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was madness-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(MADNESS_CMAKE_TOOLCHAIN_FILE "/Users/isaacvanorman/nwchemex/toolchain.cmake")

# ensure that CMAKE_SYSTEM_NAME matches what was used to compile MADNESS
if (NOT CMAKE_SYSTEM_NAME STREQUAL Darwin)
  set (ERROR_MESSAGE "CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}, does not match CMAKE_SYSTEM_NAME=Darwin used to compile MADNESS")
  if (MADNESS_CMAKE_TOOLCHAIN_FILE)
    set (ERROR_MESSAGE "${ERROR_MESSAGE}; make sure to use toolchain /Users/isaacvanorman/nwchemex/toolchain.cmake to compile your code!")
    message (FATAL_ERROR "${ERROR_MESSAGE}")
  endif(MADNESS_CMAKE_TOOLCHAIN_FILE)
endif()

# check for prereqs:
# 1. Threads
if (NOT TARGET Threads::Threads)
  set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
  find_package(Threads REQUIRED)
endif()

# 2. Cereal
set(MADNESS_HAS_CEREAL ON)
if (MADNESS_HAS_CEREAL)
  get_filename_component(cereal_DIR "" DIRECTORY)
  find_package(cereal QUIET CONFIG HINTS "${cereal_DIR}")
  if (NOT TARGET cereal)
    add_library(cereal INTERFACE IMPORTED)
    set_target_properties(cereal PROPERTIES
          INTERFACE_INCLUDE_DIRECTORIES "${cereal_INCLUDE_DIRS}"
          INTERFACE_COMPILE_DEFINITIONS "CEREAL_THREAD_SAFE=1")
  endif(NOT TARGET cereal)
endif(MADNESS_HAS_CEREAL)

# determine if only looking for MADworld ... this is a common scenario that loads a subset of targets
set(MADNESS_FIND_WORLD_ONLY FALSE)
list(LENGTH MADNESS_FIND_COMPONENTS MADNESS_FIND_NUM_COMPONENTS)
list(FIND MADNESS_FIND_COMPONENTS world MADNESS_FIND_COMPONENTS_world_idx)
if (MADNESS_FIND_NUM_COMPONENTS EQUAL 1 AND MADNESS_FIND_COMPONENTS_world_idx GREATER -1)
  set(MADNESS_FIND_WORLD_ONLY TRUE)
endif()

# Include library IMPORT targets
if(NOT TARGET MADworld)
  include("${CMAKE_CURRENT_LIST_DIR}/madness-targets.cmake")
endif(NOT TARGET MADworld)
if(NOT MADNESS_FIND_WORLD_ONLY)
  set(MADNESS_TOP_TARGET_LIBRARY madness)
  set(MADNESS_TARGET_COMPONENT madness)
else(NOT MADNESS_FIND_WORLD_ONLY)
  set(MADNESS_TOP_TARGET_LIBRARY MADworld)
  set(MADNESS_TARGET_COMPONENT world)
endif(NOT MADNESS_FIND_WORLD_ONLY)

# Set the madness libraries target
set(MADNESS_LIBRARIES ${MADNESS_TOP_TARGET_LIBRARY})

set(MADNESS_SOURCE_DIR "/Users/isaacvanorman/nwchemex/GhostFragment/build/_deps/madness-src")
set(MADNESS_BINARY_DIR "/Users/isaacvanorman/nwchemex/GhostFragment/build/_deps/madness-build")

# Set Elemental variables
set(MADNESS_HAS_ELEMENTAL 0)
set(MADNESS_HAS_ELEMENTAL_EMBEDDED )

set(MADNESS_INSTALL_LIBRARY_DIR "${PACKAGE_PREFIX_DIR}/lib")
set(MADNESS_BUILD_INCLUDE_DIRS "${MADNESS_SOURCE_DIR}/src" "${MADNESS_BINARY_DIR}/src")
set(MADNESS_INSTALL_INCLUDE_DIRS "${PACKAGE_PREFIX_DIR}/include"
      "${PACKAGE_PREFIX_DIR}/include/madness/external")

if (MADNESS_HAS_ELEMENTAL)
  if(MADNESS_HAS_ELEMENTAL_EMBEDDED)
    set(Elemental_SOURCE_DIR "")
    set(Elemental_BINARY_DIR "")
    list(APPEND MADNESS_BUILD_INCLUDE_DIRS
        "${Elemental_SOURCE_DIR}/include" "${Elemental_BINARY_DIR}/include"
        "${Elemental_SOURCE_DIR}/external/pmrrr/include"
        "${Elemental_BINARY_DIR}/external/pmrrr/include")
  else(MADNESS_HAS_ELEMENTAL_EMBEDDED)
    set(Elemental_SOURCE_DIR "")
    set(Elemental_BINARY_DIR "")
    # elemental package and component name depends on version
    set(ELEMENTAL_PACKAGE_NAME )
    set(ELEMENTAL_CONFIGURE_NAME )
    # where to look for elemental cmake config file
    if(CMAKE_CURRENT_LIST_DIR EQUAL MADNESS_BINARY_DIR)
      set(Elemental_DIR "${Elemental_BINARY_DIR}")
    else()
      set(Elemental_DIR "${PACKAGE_PREFIX_DIR}/CMake/elemental")
    endif()
    find_package(${ELEMENTAL_CONFIGURE_NAME} REQUIRED
                 COMPONENTS REQUIRED ${ELEMENTAL_PACKAGE_NAME})
    list(APPEND MADNESS_BUILD_INCLUDE_DIRS
        "${Elemental_SOURCE_DIR}/include" "${Elemental_BINARY_DIR}/include"
        "${Elemental_SOURCE_DIR}/external/pmrrr/include"
        "${Elemental_BINARY_DIR}/external/pmrrr/include"
        "${Elemental_SOURCE_DIR}/external/pmrrr/suite_sparse"
        "${Elemental_BINARY_DIR}/external/pmrrr/suite_sparse"
        )
  endif(MADNESS_HAS_ELEMENTAL_EMBEDDED)
endif(MADNESS_HAS_ELEMENTAL)

# define MADNESS_INCLUDE_DIRS according to where we are compiling: MADNESS build tree or outside
# external packages should use MADNESS_BUILD_INCLUDE_DIRS and MADNESS_INSTALL_INCLUDE_DIRS directly
if(CMAKE_CURRENT_LIST_DIR EQUAL MADNESS_BINARY_DIR)
  set(MADNESS_INCLUDE_DIRS "${MADNESS_BUILD_INCLUDE_DIRS}")
else()
  set(MADNESS_INCLUDE_DIRS "${MADNESS_INSTALL_INCLUDE_DIRS}")
endif()

# Set component variables
foreach(_comp ${MADNESS_FIND_COMPONENTS})
  if(TARGET MAD${_comp})
    set(MADNESS_${_comp}_FOUND TRUE)
    set(MADNESS_${_comp}_LIBRARY MAD${_comp})
  else()
    set(MADNESS_${_comp}_FOUND FALSE)
    set(MADNESS_${_comp}_LIBRARY "MADNESS_${_comp}_LIBRARY-NOTFOUND")
  endif()
endforeach()

# Set the Fortran 77 integer size (4 or 8)
set(MADNESS_F77_INTEGER_SIZE 4)

# whether MADNESS assumes ASLR to be disabled
set(MADNESS_ASSUMES_ASLR_DISABLED "OFF")

check_required_components(${MADNESS_TARGET_COMPONENT})

set(MADNESS_FOUND TRUE)

########### LAPACK ############
# this is formatted to be added to CMAKE_REQUIRED_LIBRARIES
set(LAPACK_LIBRARIES "")
set(LAPACK_INCLUDE_DIRS "/usr/local/opt/openblas/include")
set(LAPACK_COMPILE_DEFINITIONS "")
set(LAPACK_COMPILE_OPTIONS "")

########### MPI ############
set(MPIEXEC_EXECUTABLE "/Users/isaacvanorman/opt/anaconda3/bin/mpiexec" CACHE FILEPATH "Executable for running MPI programs")
set(MPIEXEC_NUMPROC_FLAG "-n" CACHE STRING "Maximum number of processors available to run MPI applications")
set(MPIEXEC_PREFLAGS "" CACHE STRING "Flag used by MPI to specify the number of processes for mpiexec")
set(MPIEXEC_POSTFLAGS "" CACHE STRING "These flags will be placed after all flags passed to mpiexec")

########### PaRSEC ############
# if MADworld depends on PaRSEC, enable C language and load MPI_C
get_target_property(_madworld_link_libraries MADworld INTERFACE_LINK_LIBRARIES)
cmake_policy(SET CMP0057 NEW)  # treat IN_LIST as operator
if (MPI::MPI_CXX IN_LIST _madworld_link_libraries)
    set(_mpi_languages CXX)
    if (PaRSEC::parsec IN_LIST _madworld_link_libraries)
        enable_language(C)
        list(APPEND _mpi_languages C)
        if (NOT TARGET PaRSEC::parsec)
           include( CMakeFindDependencyMacro )
           get_filename_component(_parsec_config_dir "" DIRECTORY)
           find_dependency(PaRSEC CONFIG REQUIRED COMPONENTS parsec PATHS "${_parsec_config_dir}" NO_DEFAULT_PATH)
        endif()
    endif()
    find_package(MPI REQUIRED COMPONENTS "${_mpi_languages}")
endif()

########### TBB ############
if (TBB::tbb IN_LIST _madworld_link_libraries)
   if (NOT TARGET TBB::tbb)
       include( CMakeFindDependencyMacro )
       if ("")
           get_filename_component(_tbb_config_dir "" DIRECTORY)
           find_dependency(TBB CONFIG REQUIRED COMPONENTS tbb PATHS "${_tbb_config_dir}" NO_DEFAULT_PATH)
       else()
           get_filename_component(_tbb_root_dir "/.." DIRECTORY)
           find_dependency(TBB MODULE REQUIRED COMPONENTS tbb PATHS "${_tbb_root_dir}" NO_DEFAULT_PATH)
       endif()
   endif()
endif()
