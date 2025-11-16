cmake_minimum_required(VERSION 4.0)
project(05_Arithmetic_Operations)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(05_Arithmetic_Operations main.cpp)

target_link_libraries(05_Arithmetic_Operations ${OpenCV_LIBS})
