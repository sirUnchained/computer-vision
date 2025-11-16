cmake_minimum_required(VERSION 4.0)
project(07_Gamma_correction)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(07_Gamma_correction main.cpp)

target_link_libraries(07_Gamma_correction ${OpenCV_LIBS})
