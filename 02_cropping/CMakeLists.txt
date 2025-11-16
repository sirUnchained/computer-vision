cmake_minimum_required(VERSION 4.0)
project(02_cropping)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(02_cropping main.cpp)

target_link_libraries(02_cropping ${OpenCV_LIBS})
