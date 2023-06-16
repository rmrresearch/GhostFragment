#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "blacspp" for configuration "Debug"
set_property(TARGET blacspp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(blacspp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libblacspp.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libblacspp.dylib"
  )

list(APPEND _cmake_import_check_targets blacspp )
list(APPEND _cmake_import_check_files_for_blacspp "${_IMPORT_PREFIX}/lib/libblacspp.dylib" )

# Import target "scalapackpp" for configuration "Debug"
set_property(TARGET scalapackpp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(scalapackpp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libscalapackpp.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libscalapackpp.dylib"
  )

list(APPEND _cmake_import_check_targets scalapackpp )
list(APPEND _cmake_import_check_files_for_scalapackpp "${_IMPORT_PREFIX}/lib/libscalapackpp.dylib" )

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
