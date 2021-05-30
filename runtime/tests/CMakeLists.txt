cmake_minimum_required(VERSION 3.0.0)
project(viz VERSION 0.1.0)

include(CTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_test(NAME helloworld_runtime COMMAND vrk hello.vsm)
set_tests_properties(helloworld_runtime
PROPERTIES
PASS_REGULAR_EXPRESSION "(Hello World!)"
FAIL_REGULAR_EXPRESSION "(Segmentation Fault|Exception)"
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
TIMEOUT 5
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)