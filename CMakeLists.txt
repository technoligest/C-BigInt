cmake_minimum_required(VERSION 3.10)
project(BigInt2)

set(CMAKE_CXX_STANDARD 17)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
file(GLOB safeCPP "${PROJECT_SOURCE_DIR}/safeCPP/*.cpp" "${PROJECT_SOURCE_DIR}/safeCPP/*.hpp")
set(BigInt ${safeCPP} lib/BigInt.cc lib/BigInt.h)

file(GLOB Testings "${PROJECT_SOURCE_DIR}/tests/*.hpp" "${PROJECT_SOURCE_DIR}/tests/*.cc")
#set(Testings tests/catch.hpp tests/mainTest.cc tests/testOperations.cc)

add_executable(BigInt2 lib/main.cpp ${BigInt} lib/Exception.cc lib/Exception.h)
add_executable(Tests ${Testings} ${BigInt} lib/Exception.cc lib/Exception.h)

target_compile_options(Tests PUBLIC "-Dprivate=public")

