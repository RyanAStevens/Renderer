cmake_minimum_required(VERSION 2.6)
project(pixeltoaster)

include_directories(include)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(SRC_DIR "src")
set(INCL_DIR "inlcude")

set(SOURCES
   SRC_DIR/PixelToaster.cpp  
  # SRC_DIR/Profile.cpp  
  # SRC_DIR/Test.cpp
   )

add_executable(runTests ${SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
