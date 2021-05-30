cmake_minimum_required(VERSION 3.0.0)
project(viz VERSION 0.1.0)

include(CTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,-modernize-use-trailing-return-type,-llvm-header-guard,-fuchsia-default-arguments-calls,-fuchsia-statically-constructed-objects,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-*-magic-numbers,-cppcoreguidelines-pro-bounds-constant-array-index,-hicpp-signed-bitwise;-header-filter=.")
enable_testing()

add_subdirectory(assembler)
add_subdirectory(runtime)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)