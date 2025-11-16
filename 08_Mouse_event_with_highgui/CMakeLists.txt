cmake_minimum_required(VERSION 4.0)
project(08_Mouse_event_with_highgui)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(08_Mouse_event_with_highgui main.cpp)

target_link_libraries(08_Mouse_event_with_highgui ${OpenCV_LIBS})