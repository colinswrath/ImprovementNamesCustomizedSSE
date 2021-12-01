#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "binary_io::binary_io" for configuration "Debug"
set_property(TARGET binary_io::binary_io APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(binary_io::binary_io PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/binary_iod.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS binary_io::binary_io )
list(APPEND _IMPORT_CHECK_FILES_FOR_binary_io::binary_io "${_IMPORT_PREFIX}/debug/lib/binary_iod.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
