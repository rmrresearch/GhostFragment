cmake_minimum_required( VERSION 3.15 )

include( CMakeFindDependencyMacro )

find_dependency( blaspp )

# Export variables.
set( lapackpp_defines   "-DLAPACK_HAVE_LAPACK;-DLAPACK_VERSION=30201" )
set( lapackpp_libraries "-L/usr/local/opt/openblas/lib;-lblas;-llapack;blaspp" )

include("${CMAKE_CURRENT_LIST_DIR}/lapackppTargets.cmake")
