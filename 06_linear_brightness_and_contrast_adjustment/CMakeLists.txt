cmake_minimum_required(VERSION 4.0)
project(06_linear_brightness_and_contrast_adjustment)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(06_linear_brightness_and_contrast_adjustment main.cpp)

target_link_libraries(06_linear_brightness_and_contrast_adjustment ${OpenCV_LIBS})
