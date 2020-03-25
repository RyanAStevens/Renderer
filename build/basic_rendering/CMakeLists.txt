cmake_minimum_required(VERSION 2.6)
project(basic_rendering)

find_package(X11 REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(BASIC_REND_SRC_BASE_DIR "../../src/basic_rendering")
set(RUNTIME_OUTPUT_DIRECTORY ".")

include_directories("../../third_party/pixeltoaster/include")

add_executable(draw_line ${BASIC_REND_SRC_BASE_DIR}/draw_line.cpp ../../third_party/pixeltoaster/src/PixelToaster.cpp)
target_link_libraries(draw_line ${X11_LIBRARIES})
