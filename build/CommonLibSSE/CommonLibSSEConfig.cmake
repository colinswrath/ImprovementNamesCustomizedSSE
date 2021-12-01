include("${CMAKE_CURRENT_LIST_DIR}/CommonLibSSE-targets.cmake")
include(CMakeFindDependencyMacro)

find_dependency(binary_io CONFIG)
find_dependency(Boost MODULE)
find_dependency(spdlog CONFIG)
