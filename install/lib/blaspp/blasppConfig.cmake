cmake_minimum_required( VERSION 3.15 )

set( blaspp_use_openmp "true" )
set( blaspp_use_cuda   "false" )
set( blaspp_use_hip    "false" )

include( CMakeFindDependencyMacro )
if (blaspp_use_openmp)
    find_dependency( OpenMP )
endif()

if (blaspp_use_hip)
    find_dependency( rocblas )
endif()

# Export private variables used in LAPACK++.
set( blaspp_defines         "-DBLAS_FORTRAN_ADD_;-DBLAS_COMPLEX_RETURN_ARGUMENT;-DBLAS_HAVE_F2C" )
set( blaspp_libraries       "/opt/homebrew/lib/libscalapack.dylib;MPI::MPI_C;-L/usr/local/opt/openblas/lib;-lblas;-llapack;OpenMP::OpenMP_CXX" )

set( blaspp_cblas_found     "" )
set( blaspp_cblas_include   "" )
set( blaspp_cblas_libraries "" )

include( "${CMAKE_CURRENT_LIST_DIR}/blasppTargets.cmake" )
