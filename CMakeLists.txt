cmake_minimum_required(VERSION 3.14)
project(software_renderer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  libsdl 
  URL https://github.com/libsdl-org/SDL/releases/download/release-2.30.3/SDL2-2.30.3.zip
)

FetchContent_MakeAvailable(googletest libsdl)

include_directories(${GTEST_INCLUDE_DIRS} include test/test_include)

set(GRAPHICS_LIB_SOURCE_DIR "src/")

set(SOURCES
    ${GRAPHICS_LIB_SOURCE_DIR}/graphics_lib.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/projection.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/vector2.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/vector3.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/matrix_stack.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/transform_matrix.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/vector3h.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/color.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/vertex.cpp
    ${GRAPHICS_LIB_SOURCE_DIR}/draw_routines.cpp
   )

set(GRAPHICS_LIB_TEST_SOURCE_DIR "test/test_src/")

set(TEST_SOURCES
    ${GRAPHICS_LIB_TEST_SOURCE_DIR}/vector2_test.cpp
#    ${GRAPHICS_LIB_TEST_SOURCE_DIR}/vector3_test.cpp
    ${GRAPHICS_LIB_TEST_SOURCE_DIR}/matrix_stack_test.cpp
    ${GRAPHICS_LIB_TEST_SOURCE_DIR}/graphics_lib_test.cpp
    ${GRAPHICS_LIB_TEST_SOURCE_DIR}/color_test.cpp
    ${GRAPHICS_LIB_TEST_SOURCE_DIR}/draw_routines_test.cpp
   )

enable_testing()

add_executable(
  software_renderer_test 
  test/test_main.cpp
  ${TEST_SOURCES} ${SOURCES}
)

target_link_libraries(
  software_renderer_test
  GTest::gtest_main
)

add_executable(
  software_renderer
  src/main.cpp
  ${SOURCES}
)
target_link_libraries(software_renderer PRIVATE SDL2::SDL2)

include(GoogleTest)
gtest_discover_tests(software_renderer_test)
