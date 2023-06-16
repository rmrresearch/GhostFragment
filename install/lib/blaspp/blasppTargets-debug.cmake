#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "blaspp" for configuration "Debug"
set_property(TARGET blaspp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(blaspp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libblaspp.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libblaspp.dylib"
  )

list(APPEND _cmake_import_check_targets blaspp )
list(APPEND _cmake_import_check_files_for_blaspp "${_IMPORT_PREFIX}/lib/libblaspp.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
