#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "lapackpp" for configuration "Debug"
set_property(TARGET lapackpp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(lapackpp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/liblapackpp.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/liblapackpp.dylib"
  )

list(APPEND _cmake_import_check_targets lapackpp )
list(APPEND _cmake_import_check_files_for_lapackpp "${_IMPORT_PREFIX}/lib/liblapackpp.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
