cmake_minimum_required(VERSION 4.0)
project(01_start_opencv_gray_scaling)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(01_start_opencv_gray_scaling main.cpp)

target_link_libraries(01_start_opencv_gray_scaling ${OpenCV_LIBS})
