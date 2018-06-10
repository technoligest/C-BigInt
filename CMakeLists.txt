cmake_minimum_required(VERSION 3.10)
project(BigInt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(BigInt2 main.cpp BigInt.cc BigInt.h )

add_executable(Tests  tests/catch.hpp tests/mainTest.cc tests/testOperations.cc BigInt.cc)
add_executable(Trying trying.cc)
