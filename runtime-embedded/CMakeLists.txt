cmake_minimum_required(VERSION 3.0.0)
project(viz VERSION 0.1.0)

include(CTest)

add_executable(vrk-tiny runtime_embedded.c types.c functions_rt_embedded.c)
add_library(arch-dep STATIC)
target_link_libraries(vrk-tiny arch-dep)
add_subdirectory(architecture-dependent)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)