# Copyright 2023 GhostFragment
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.14)

# Downloads common CMake modules used throughout NWChemEx Community
include(cmake/get_nwx_cmake.cmake)

# TODO: Uncomment when we have tags
#include(get_version_from_git)
#get_version_from_git(ghostfragment_version "${CMAKE_CURRENT_LIST_DIR}")
set(ghostframent_version "0.0.1")
project(ghostfragment VERSION "${ghostfragment_version}" LANGUAGES CXX)

include(nwx_versions)
include(get_cmaize)

### Options ###
cmaize_option_list(
    BUILD_TESTING OFF "Should we build the tests?"
    BUILD_PYBIND11_PYBINDINGS ON "Use pybind11 to build Python3 bindings?"
    INTEGRATION_TESTING OFF "Should we build integration tests?"
)

# Work out the project paths
set(project_inc_dir "${CMAKE_CURRENT_LIST_DIR}/include")
set(project_src_dir "${CMAKE_CURRENT_LIST_DIR}/src")

include(nwx_cxx_api_docs)
nwx_cxx_api_docs("${project_src_dir}" "${project_inc_dir}")

cmaize_find_or_build_dependency(
    simde
    URL github.com/NWChemEx/SimDE
    BUILD_TARGET simde
    FIND_TARGET nwx::simde
    CMAKE_ARGS BUILD_TESTING=OFF
)

cmaize_add_library(
    ${PROJECT_NAME}
    SOURCE_DIR "${project_src_dir}/${PROJECT_NAME}"
    INCLUDE_DIRS "${project_inc_dir}"
    DEPENDS simde
)

include(nwx_pybind11)
nwx_add_pybind11_module(
    ${PROJECT_NAME}
    SOURCE_DIR "${project_src_dir}/python"
    DEPENDS ${PROJECT_NAME}
)

if("${BUILD_TESTING}")
    set(cxx_tests_dir "${CMAKE_CURRENT_LIST_DIR}/tests/cxx")
    set(python_tests_dir "${CMAKE_CURRENT_LIST_DIR}/tests/python")

    cmaize_find_or_build_dependency(
        Catch2
        VERSION v2.x
        URL github.com/catchorg/Catch2
        BUILD_TARGET Catch2
        VERSION v2.13.8
        FIND_TARGET Catch2::Catch2
    )
    cmaize_add_tests(
        "test_${PROJECT_NAME}"
        SOURCE_DIR "${cxx_tests_dir}/unit_tests/${PROJECT_NAME}"
        INCLUDE_DIRS "${project_src_dir}/${PROJECT_NAME}"
        DEPENDS Catch2::Catch2 ${PROJECT_NAME}
    )
    nwx_pybind11_tests(
        py_ghostfragment
        ${python_tests_dir}/integration_tests/test_ghostfragment.py
        SUBMODULES simde chemist pluginplay parallelzone
    )

    if("${INTEGRATION_TESTING}")
        cmaize_find_or_build_dependency(
            nwchemex
            URL github.com/NWChemEx/NWChemEx
            BUILD_TARGET nwchemex
            FIND_TARGET nwx::nwchemex
            CMAKE_ARGS BUILD_TESTING=OFF
        )
    endif()
endif()
