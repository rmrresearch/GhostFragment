cmake_minimum_required(VERSION 3.14)
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" VERSION)
project(ghostfragment VERSION "${VERSION}" LANGUAGES CXX)

set(
    CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/cmake"
    CACHE STRING "" FORCE
)

include(get_cpp)
include(nwx_cxx_api_docs)
nwx_cxx_api_docs("${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include")

### Options ###
option(BUILD_TESTING "Should we build the tests?" OFF)
option(BUILD_PYBINDINGS "Should we build Python3 bindings?" ON)

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

if("${BUILD_PYBINDINGS}")
    include(nwx_python_mods)
    cppyy_make_python_package(
        PACKAGE ghostfragment
        NAMESPACES ghostfragment
        DEPPACKAGES simde
    )
endif()

set(BUILD_INTEGRATION_TESTS ON)
set(TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/tests")

if("${BUILD_TESTING}")
    cpp_find_or_build_dependency(
        Catch2
        VERSION v2.x
        URL github.com/catchorg/Catch2
        BUILD_TARGET Catch2
        VERSION v2.13.8
        FIND_TARGET Catch2::Catch2
    )

    cpp_add_tests(
        "test_${CMAKE_PROJECT_NAME}"
        SOURCE_DIR "${TEST_DIR}/unit/${CMAKE_PROJECT_NAME}"
        INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/src/${CMAKE_PROJECT_NAME}"
        DEPENDS Catch2::Catch2 ${CMAKE_PROJECT_NAME}
    )



    if(FALSE)
        find_package(Python3 REQUIRED COMPONENTS Interpreter)
        cpp_find_or_build_dependency(
            FriendZone
            URL github.com/NWChemEx-Project/FriendZone
            PRIVATE TRUE
            BUILD_TARGET friendzone
            FIND_TARGET nwx::friendzone
            CMAKE_ARGS BUILD_TESTING=OFF
        )
        add_test(
            NAME integration_tests
            COMMAND ${Python3_Executable} "-m" "unittest"
            WORKING_DIR "${TEST_DIR}/integration/${CMAKE_PROJECT_NAME}"
        )
        set_property(
            TEST integration_tests
            PROPERTY ENVIRONMENT
                "PYTHONPATH=${CMAKE_BINARY_DIR}/Python"
        )
    endif()

endif()
