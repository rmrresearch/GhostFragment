#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "scalapackpp::scalapackpp" for configuration "Debug"
set_property(TARGET scalapackpp::scalapackpp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(scalapackpp::scalapackpp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libscalapackpp.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libscalapackpp.dylib"
  )

list(APPEND _cmake_import_check_targets scalapackpp::scalapackpp )
list(APPEND _cmake_import_check_files_for_scalapackpp::scalapackpp "${_IMPORT_PREFIX}/lib/libscalapackpp.dylib" )

# Import target "scalapackpp::blacspp" for configuration "Debug"
set_property(TARGET scalapackpp::blacspp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(scalapackpp::blacspp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libblacspp.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libblacspp.dylib"
  )

list(APPEND _cmake_import_check_targets scalapackpp::blacspp )
list(APPEND _cmake_import_check_files_for_scalapackpp::blacspp "${_IMPORT_PREFIX}/lib/libblacspp.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
