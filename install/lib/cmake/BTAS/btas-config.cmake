# - CMAKE Config file for the BTAS package
# This will define the following CMake cache variables
#
#    BTAS_FOUND           - true if BTAS library were found
#    BTAS_VERSION         - the BTAS version
#    BTAS_EXT_VERSION     - the BTAS version including the (optional) buildid, such as beta.3
#
# and the following imported targets
#
#     BTAS::BTAS          - the BTAS library
#

# Set package version
set(BTAS_VERSION "1.0.0")
set(BTAS_EXT_VERSION "1.0.0-alpha.1")


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was btas-config.cmake.in                            ########

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

# import boost components, if any missing
set(Boost_BTAS_DEPS_LIBRARIES serialization)
foreach(_deplib ${Boost_BTAS_DEPS_LIBRARIES})
  if (DEFINED Boost_BTAS_DEPS_LIBRARIES_NOT_FOUND_CHECK)
    list(APPEND Boost_BTAS_DEPS_LIBRARIES_NOT_FOUND_CHECK OR)
  endif()
  list(APPEND Boost_BTAS_DEPS_LIBRARIES_NOT_FOUND_CHECK "NOT;TARGET;Boost::${_deplib}")
endforeach(_deplib)
if (NOT DEFINED Boost_BTAS_DEPS_LIBRARIES_NOT_FOUND_CHECK)
  list(APPEND Boost_BTAS_DEPS_LIBRARIES_NOT_FOUND_CHECK "NOT;TARGET;Boost::boost")
endif (NOT DEFINED Boost_BTAS_DEPS_LIBRARIES_NOT_FOUND_CHECK)

if(${Boost_BTAS_DEPS_LIBRARIES_NOT_FOUND_CHECK})
  set(Boost_USE_CONFIG TRUE)
  # OPTIONAL_COMPONENTS in FindBoost available since 3.11
  cmake_minimum_required(VERSION 3.11.0)
  if (Boost_USE_CONFIG)
    set(Boost_CONFIG /opt/homebrew/lib/cmake/Boost-1.81.0/BoostConfig.cmake)
    if (NOT Boost_CONFIG OR NOT EXISTS ${Boost_CONFIG})
      message(FATAL_ERROR "Expected Boost config file at ${Boost_CONFIG}; directory moved since BTAS configuration?")
    endif()
    get_filename_component(Boost_DIR ${Boost_CONFIG} DIRECTORY)
    find_package(Boost CONFIG QUIET REQUIRED OPTIONAL_COMPONENTS ${Boost_BTAS_DEPS_LIBRARIES} PATHS ${Boost_DIR} NO_DEFAULT_PATH)
  else (Boost_USE_CONFIG)
    set(BOOST_INCLUDEDIR )
    set(BOOST_LIBRARYDIR )
    if (NOT BOOST_LIBRARYDIR OR NOT EXISTS ${BOOST_LIBRARYDIR})
      set(BOOST_LIBRARYDIR )
    endif()
    set(Boost_NO_SYSTEM_PATHS OFF)
    if (BOOST_LIBRARYDIR AND BOOST_INCLUDEDIR)
      if (EXISTS ${BOOST_LIBRARYDIR} AND EXISTS ${BOOST_INCLUDEDIR})
        set(Boost_NO_SYSTEM_PATHS ON)
      endif()
    endif()
    find_package(Boost QUIET REQUIRED OPTIONAL_COMPONENTS ${Boost_BTAS_DEPS_LIBRARIES})
  endif (Boost_USE_CONFIG)
endif(${Boost_BTAS_DEPS_LIBRARIES_NOT_FOUND_CHECK})

# find linalgpp dependencies
if(NOT TARGET blaspp)
  include( CMakeFindDependencyMacro )
  get_filename_component(blaspp_DIR "/Users/isaacvanorman/nwchemex/GhostFragment/install/lib/blaspp/blasppConfig.cmake" DIRECTORY)
  if (NOT DEFINED BLAS_LIBRARIES AND NOT DEFINED blaspp_defs_)
    if (NOT "/opt/homebrew/lib/libscalapack.dylib;MPI::MPI_C;-L/usr/local/opt/openblas/lib;-lblas;-llapack" STREQUAL "")
      set(BLAS_LIBRARIES "/opt/homebrew/lib/libscalapack.dylib;MPI::MPI_C;-L/usr/local/opt/openblas/lib;-lblas;-llapack" CACHE STRING "BLAS_LIBRARIES used during BTAS configuration")
    endif()
    if (NOT "-DBLAS_FORTRAN_ADD_;-DBLAS_COMPLEX_RETURN_ARGUMENT;-DBLAS_HAVE_F2C" STREQUAL "")
      set(blaspp_defs_ "-DBLAS_FORTRAN_ADD_;-DBLAS_COMPLEX_RETURN_ARGUMENT;-DBLAS_HAVE_F2C" CACHE STRING "blaspp_defs_ used during BTAS configuration")
    endif()
  endif()
  find_dependency( blaspp CONFIG REQUIRED HINTS "${blaspp_DIR}" )

  # if need Threads::Threads, load it
  get_target_property(blaspp_LINK_LIBRARIES blaspp INTERFACE_LINK_LIBRARIES)
  if (Threads::Threads IN_LIST blaspp_LINK_LIBRARIES AND NOT TARGET Threads::Threads)
    find_dependency(Threads)
    # Threads::Threads by default is not GLOBAL, so to allow users of LINALG_LIBRARIES to safely use it we need to make it global
    # more discussion here: https://gitlab.kitware.com/cmake/cmake/-/issues/17256
    set_target_properties(Threads::Threads PROPERTIES IMPORTED_GLOBAL TRUE)
  endif()

endif()
if(NOT TARGET lapackpp)
  include( CMakeFindDependencyMacro )
  get_filename_component(lapackpp_DIR "/Users/isaacvanorman/nwchemex/GhostFragment/install/lib/lapackpp/lapackppConfig.cmake" DIRECTORY)
  if (NOT DEFINED LAPACK_LIBRARIES AND NOT DEFINED lapackpp_defs_)
    if (NOT "-L/usr/local/opt/openblas/lib;-lblas;-llapack" STREQUAL "")
      set(LAPACK_LIBRARIES "-L/usr/local/opt/openblas/lib;-lblas;-llapack" CACHE STRING "LAPACK_LIBRARIES used during BTAS configuration")
    endif()
    if (NOT "-DLAPACK_HAVE_LAPACK;-DLAPACK_VERSION=30201" STREQUAL "")
      set(lapackpp_defs_ "-DLAPACK_HAVE_LAPACK;-DLAPACK_VERSION=30201" CACHE STRING "lapackpp_defs_ used during BTAS configuration")
    endif()
  endif()
  find_dependency( lapackpp CONFIG REQUIRED HINTS "${lapackpp_DIR}" )
endif()

# Include library IMPORT targets
if(NOT TARGET blaspp_headers)
  include("${blaspp_DIR}/blaspp_headers-targets.cmake")
  if(NOT TARGET blaspp_headers)
    message(FATAL_ERROR "expected blaspp_headers among imported BTAS targets")
  endif()
endif()
if(NOT TARGET BTAS::BTAS)
  include("${CMAKE_CURRENT_LIST_DIR}/btas-targets.cmake")
  if(NOT TARGET BTAS::BTAS)
    message(FATAL_ERROR "expected BTAS::BTAS among imported BTAS targets")
  endif()
endif()

set(BTAS_FOUND TRUE)
