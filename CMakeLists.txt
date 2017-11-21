set(CMAKE_CXX_COMPILER /usr/bin/g++)
cmake_minimum_required(VERSION 3.5)
project(turbo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(SUB_DIR ${PROJECT_SOURCE_DIR}/submissions)

# Library core.
add_subdirectory(${LIB_DIR}/geometry)
add_subdirectory(${LIB_DIR}/structures)

# Submissions.
add_subdirectory(${SUB_DIR}/codeforces)
add_subdirectory(${SUB_DIR}/kattis)
add_subdirectory(${SUB_DIR}/spoj)

# Google Test.
enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Unit tests.
add_subdirectory(${TEST_DIR}/geometry)
add_subdirectory(${TEST_DIR}/structures)
