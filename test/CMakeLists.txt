cmake_minimum_required(VERSION 2.6)
project(test)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} test_include ../include/)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(GRAPHICS_LIB_SOURCE_DIR "../src/")

set(SOURCES
    ${GRAPHICS_LIB_SOURCE_DIR}/graphics_lib.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/projection.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/vector2.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/vector3.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/matrix_stack.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/matrix.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/vector3h.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/color.cpp
   )

set(TEST_SOURCES
    test_main.cpp
    test_src/vector2_test.cpp
    test_src/vector3_test.cpp
    test_src/matrix_test.cpp
    test_src/matrix_stack_test.cpp
    test_src/graphics_lib_test.cpp
    test_src/color_test.cpp
   )

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${TEST_SOURCES} ${SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
