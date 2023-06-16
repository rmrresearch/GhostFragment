# - CMAKE Config file for the TiledArray package
# The following variables are defined:
#  TILEDARRAY_FOUND                - System has the TiledArray package
#  TILEDARRAY_INCLUDE_DIRS         - The TiledArray include directory
#  TILEDARRAY_LIBRARIES            - The TiledArray libraries and their dependencies
#  TILEDARRAY_VERSION              - The TiledArray (core) version; see semver.org
#  TILEDARRAY_EXT_VERSION          - The TiledArray version, includes prerelease id; see semver.org

# Set package version
set(TILEDARRAY_VERSION "1.0.0")
set(TILEDARRAY_EXT_VERSION "1.0.0")


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was tiledarray-config.cmake.in                            ########

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

# Include library IMPORT targets
if (NOT TARGET BTAS::BTAS)
  get_filename_component(BTAS_DIR "/Users/isaacvanorman/nwchemex/GhostFragment/install/lib/cmake/BTAS/btas-config.cmake" DIRECTORY)
  find_package(BTAS 1.0.0 QUIET CONFIG REQUIRED HINTS "${BTAS_DIR}")
endif()
if(NOT TARGET MADworld)
  # if madness installed separately, use the madness install discovered when configuring TA
  set(MADNESS_CONFIG_DIR "")
  # otherwise assume TA built madness
  if (MADNESS_CONFIG_DIR STREQUAL "")
    set(MADNESS_CONFIG_DIR "${CMAKE_CURRENT_LIST_DIR}/../madness")
  endif()
  include( CMakeFindDependencyMacro )
  find_dependency(MADNESS 0.10.1 CONFIG REQUIRED COMPONENTS world PATHS "${MADNESS_CONFIG_DIR}" NO_DEFAULT_PATH)
endif()
if(NOT TARGET tiledarray)
  include("${CMAKE_CURRENT_LIST_DIR}/tiledarray-targets.cmake")
endif()

# if TA is a CUDA-dependent library it needs CUDA to link properly ... unfortunately CMake is not able to do this correctly
# see https://gitlab.kitware.com/cmake/cmake/issues/18614
# so try workarounds
set(TILEDARRAY_HAS_CUDA "")
if(TILEDARRAY_HAS_CUDA)
  cmake_minimum_required(VERSION 3.17)
  if (NOT TARGET CUDA::cublas)
    find_package(CUDAToolkit REQUIRED COMPONENTS cublas nvToolsExt)
  endif(NOT TARGET CUDA::cublas)
  set(CMAKE_CUDA_HOST_COMPILER "")
  # workaround from https://gitlab.kitware.com/cmake/cmake/issues/18614#note_485631
  set(CUDA_LIBRARIES "")
  get_target_property(_ta_interface_libs tiledarray INTERFACE_LINK_LIBRARIES)
  if(_ta_interface_libs)
    list(APPEND _ta_interface_libs ${CUDA_LIBRARIES})
  else()
    set(_ta_interface_libs ${CUDA_LIBRARIES})
  endif()
    string(TOUPPER ${CMAKE_BUILD_TYPE} TA_BUILD_TYPE)
  set_target_properties(tiledarray PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES_${TA_BUILD_TYPE} CXX
    INTERFACE_LINK_LIBRARIES "${_ta_interface_libs}")
endif()

set(TILEDARRAY_HAS_SCALAPACK "ON" )
if(TILEDARRAY_HAS_SCALAPACK)
  include( CMakeFindDependencyMacro )
  get_filename_component(blacspp_DIR "/Users/isaacvanorman/nwchemex/GhostFragment/install/lib/cmake/blacspp/blacspp-config.cmake" DIRECTORY)
  find_dependency( blacspp CONFIG REQUIRED HINTS "${blacspp_DIR}" )
  get_filename_component(scalapackpp_DIR "/Users/isaacvanorman/nwchemex/GhostFragment/install/lib/cmake/scalapackpp/scalapackpp-config.cmake" DIRECTORY)
  find_dependency( scalapackpp CONFIG REQUIRED HINTS "${scalapackpp_DIR}" )
endif()

# Set the tiledarray compiled library target
set(TILEDARRAY_LIBRARIES tiledarray)

set(TILEDARRAY_SOURCE_DIR "")
set(TILEDARRAY_BINARY_DIR "")

set(TILEDARRAY_BUILD_INCLUDE_DIRS "${TILEDARRAY_SOURCE_DIR}/src" "${TILEDARRAY_BINARY_DIR}/src")
set(TILEDARRAY_INSTALL_INCLUDE_DIRS "${PACKAGE_PREFIX_DIR}/include"
      "${PACKAGE_PREFIX_DIR}/include/TiledArray/external")

# define TILEDARRAY_INCLUDE_DIRS according to where we are compiling: TA build tree or outside
# external packages should use TILEDARRAY_BUILD_INCLUDE_DIRS and TILEDARRAY_INSTALL_INCLUDE_DIRS directly
if(CMAKE_CURRENT_LIST_DIR EQUAL TILEDARRAY_BINARY_DIR)
  set(TILEDARRAY_INCLUDE_DIRS "${TILEDARRAY_BUILD_INCLUDE_DIRS}")
else()
  set(TILEDARRAY_INCLUDE_DIRS "${TILEDARRAY_INSTALL_INCLUDE_DIRS}")
endif()

set(TILEDARRAY_CMAKE_TOOLCHAIN_FILE "/Users/isaacvanorman/nwchemex/toolchain.cmake")

# whether TA assumes ASLR to be disabled
set(TA_ASSUMES_ASLR_DISABLED "OFF")

set(TILEDARRAY_FOUND TRUE)
