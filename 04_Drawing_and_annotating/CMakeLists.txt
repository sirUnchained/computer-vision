cmake_minimum_required(VERSION 4.0)
project(04_Drawing_and_annotating)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(04_Drawing_and_annotating main.cpp)

target_link_libraries(04_Drawing_and_annotating ${OpenCV_LIBS})
