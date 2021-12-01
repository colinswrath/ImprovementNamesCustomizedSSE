#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CommonLibSSE::CommonLibSSE" for configuration "Release"
set_property(TARGET CommonLibSSE::CommonLibSSE APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(CommonLibSSE::CommonLibSSE PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/CommonLibSSE.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS CommonLibSSE::CommonLibSSE )
list(APPEND _IMPORT_CHECK_FILES_FOR_CommonLibSSE::CommonLibSSE "${_IMPORT_PREFIX}/lib/CommonLibSSE.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
