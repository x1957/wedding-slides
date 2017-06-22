cmake_minimum_required(VERSION 2.6)
project(Wedding)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_definitions(-std=c++1z)

include_directories($ENV{HOME}/local/opencv/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories($ENV{HOME}/local/opencv/lib)

add_executable(resize-image src/resize-image.cpp)
target_link_libraries(resize-image opencv_imgproc)
target_link_libraries(resize-image opencv_core)
target_link_libraries(resize-image opencv_highgui)
target_link_libraries(resize-image opencv_imgcodecs)
target_link_libraries(resize-image opencv_imgproc)
