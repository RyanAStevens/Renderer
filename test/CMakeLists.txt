cmake_minimum_required(VERSION 2.6)
project(test)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++11")

set(SOURCES
    ../src/vector2.cpp
    ../src/vector3.cpp
    ../src/matrix_stack.cpp
   )

set(TEST_SOURCES
    test_main.cpp
    test_src/vector2_test.cpp
    test_src/vector3_test.cpp
   )

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${TEST_SOURCES} ${SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
