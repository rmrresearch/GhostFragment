#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "tiledarray" for configuration "Debug"
set_property(TARGET tiledarray APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(tiledarray PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libtiledarray.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libtiledarray.dylib"
  )

list(APPEND _cmake_import_check_targets tiledarray )
list(APPEND _cmake_import_check_files_for_tiledarray "${_IMPORT_PREFIX}/lib/libtiledarray.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
