cmake_minimum_required(VERSION 3.0.0)
project(viz VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(vrk main.cpp functions.cpp datatypes.cpp)
add_executable(viz4web main.cpp functions.cpp datatypes.cpp)
add_executable(vizier main.cpp functions.cpp datatypes.cpp)
target_compile_definitions(viz4web PUBLIC VIZ4WEB)
target_compile_definitions(vizier PUBLIC DEBUG)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)