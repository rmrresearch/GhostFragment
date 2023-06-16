#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "blacspp::blacspp" for configuration "Debug"
set_property(TARGET blacspp::blacspp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(blacspp::blacspp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libblacspp.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libblacspp.dylib"
  )

list(APPEND _cmake_import_check_targets blacspp::blacspp )
list(APPEND _cmake_import_check_files_for_blacspp::blacspp "${_IMPORT_PREFIX}/lib/libblacspp.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
