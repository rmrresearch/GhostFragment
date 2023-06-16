#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MADworld" for configuration "Debug"
set_property(TARGET MADworld APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MADworld PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libMADworld.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libMADworld.dylib"
  )

list(APPEND _cmake_import_check_targets MADworld )
list(APPEND _cmake_import_check_files_for_MADworld "${_IMPORT_PREFIX}/lib/libMADworld.dylib" )

# Import target "madness" for configuration "Debug"
set_property(TARGET madness APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(madness PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libmadness.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libmadness.dylib"
  )

list(APPEND _cmake_import_check_targets madness )
list(APPEND _cmake_import_check_files_for_madness "${_IMPORT_PREFIX}/lib/libmadness.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
