#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "binary_io::binary_io" for configuration "Release"
set_property(TARGET binary_io::binary_io APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(binary_io::binary_io PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/binary_io.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS binary_io::binary_io )
list(APPEND _IMPORT_CHECK_FILES_FOR_binary_io::binary_io "${_IMPORT_PREFIX}/lib/binary_io.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
