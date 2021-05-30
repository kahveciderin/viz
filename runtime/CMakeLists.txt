cmake_minimum_required(VERSION 3.0.0)
project(viz VERSION 0.1.0)

include(CTest)

add_executable(vrk runtime.cpp functions_runtime.cpp datatypes.cpp)
add_executable(vizier runtime.cpp functions_runtime.cpp datatypes.cpp)
target_compile_definitions(vizier PUBLIC DEBUG)

add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)