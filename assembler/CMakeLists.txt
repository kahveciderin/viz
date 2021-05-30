cmake_minimum_required(VERSION 3.0.0)
project(viz VERSION 0.1.0)

include(CTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(vsm assembler.cpp functions_assembler.cpp switch.cpp)
add_executable(vsm4web assembler.cpp functions_assembler.cpp switch.cpp)
target_compile_definitions(vsm4web PUBLIC VIZ4WEB)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)