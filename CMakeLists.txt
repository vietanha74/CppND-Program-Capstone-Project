cmake_minimum_required(VERSION 3.15)
project(MandelbrotSet)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

find_package(OpenCV REQUIRED)

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCE "src/*.cpp")

add_compile_options(-std=c++11)
add_executable(MandelbrotSet ${SOURCE})

target_link_libraries(MandelbrotSet ${OpenCV_LIBS} )