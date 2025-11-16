cmake_minimum_required(VERSION 4.0)
project(03_bitwise_operations_and_masking)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(03_bitwise_operations_and_masking main.cpp)

target_link_libraries(03_bitwise_operations_and_masking ${OpenCV_LIBS})
