cmake_minimum_required(VERSION 4.0)
project(09_thresholding_image)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(09_thresholding_image main.cpp)

target_link_libraries(09_thresholding_image ${OpenCV_LIBS})