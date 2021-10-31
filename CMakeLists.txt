cmake_minimum_required(VERSION 3.14)
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" VERSION)
project(ghostfragment VERSION "${VERSION}" LANGUAGES CXX)

set(
    CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/cmake"
    CACHE STRING "" FORCE
)

include(get_cpp)
include(nwx_cxx_api_docs)
nwx_cxx_api_docs("${CMAKE_CURRENT_SOURCE_DIR}/src")

### Options ###
option(BUILD_TESTING "Should we build the tests?" OFF)

cpp_find_or_build_dependency(
    simde
    URL github.com/NWChemEx-Project/SimDE
    PRIVATE TRUE
    BUILD_TARGET simde
    FIND_TARGET nwx::simde
    CMAKE_ARGS BUILD_TESTING=OFF
)

cpp_add_library(
    ${CMAKE_PROJECT_NAME}
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src/${CMAKE_PROJECT_NAME}"
    INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include/${CMAKE_PROJECT_NAME}"
    DEPENDS nwx::simde
)

if("${BUILD_TESTING}")
    cpp_find_or_build_dependency(
        Catch2
        VERSION v2.x
        URL github.com/catchorg/Catch2
        BUILD_TARGET Catch2
        VERSION v2.13.3
        FIND_TARGET Catch2::Catch2
    )
    cpp_add_tests(
        "test_${CMAKE_PROJECT_NAME}"
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/tests/${CMAKE_PROJECT_NAME}"
        INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/src/${CMAKE_PROJECT_NAME}"
        DEPENDS Catch2::Catch2 ${CMAKE_PROJECT_NAME}
    )
endif()