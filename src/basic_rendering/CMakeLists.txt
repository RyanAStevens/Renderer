cmake_minimum_required(VERSION 2.6)
project(basic_rendering)

find_package(X11 REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(BASIC_REND_SRC_BASE_DIR "../../src/basic_rendering")
set(GRAPHICS_LIB_SRC_DIR "../../src/graphics_lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASIC_REND_SRC_BASE_DIR}/build")

include_directories("../../third_party/pixeltoaster/include" "../../include/graphics_lib")

add_executable(draw_triangle ${BASIC_REND_SRC_BASE_DIR}/draw_triangle.cpp ../../third_party/pixeltoaster/src/PixelToaster.cpp ${GRAPHICS_LIB_SRC_DIR}/graphics_lib.cpp ${GRAPHICS_LIB_SRC_DIR}/image.cpp ${GRAPHICS_LIB_SRC_DIR}/window.cpp ${GRAPHICS_LIB_SRC_DIR}/vector2.cpp ${GRAPHICS_LIB_SRC_DIR}/color.cpp)
target_link_libraries(draw_triangle ${X11_LIBRARIES})
