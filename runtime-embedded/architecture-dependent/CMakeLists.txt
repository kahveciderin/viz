cmake_minimum_required(VERSION 3.0.0)
project(viz VERSION 0.1.0)

include(CTest)

#Add other implementations here
set(ARCH_TARGET_INTERFACE "default-pc" CACHE STRING "Architecture-dependent interface type")
set_property(CACHE ARCH_TARGET_INTERFACE PROPERTY STRINGS "default-pc")
message(STATUS "Building with interface '${ARCH_TARGET_INTERFACE}'")

add_subdirectory($CACHE{ARCH_TARGET_INTERFACE})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)