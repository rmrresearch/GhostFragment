#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "spdlog::spdlog" for configuration "Debug"
set_property(TARGET spdlog::spdlog APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(spdlog::spdlog PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libspdlogd.1.11.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libspdlogd.1.11.dylib"
  )

list(APPEND _cmake_import_check_targets spdlog::spdlog )
list(APPEND _cmake_import_check_files_for_spdlog::spdlog "${_IMPORT_PREFIX}/lib/libspdlogd.1.11.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
