#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "umpire" for configuration "Debug"
set_property(TARGET umpire APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(umpire PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libumpire.dylib"
  IMPORTED_SONAME_DEBUG "/Users/isaacvanorman/nwchemex/GhostFragment/install/lib/libumpire.dylib"
  )

list(APPEND _cmake_import_check_targets umpire )
list(APPEND _cmake_import_check_files_for_umpire "${_IMPORT_PREFIX}/lib/libumpire.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
