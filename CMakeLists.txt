cmake_minimum_required(VERSION 3.12)
project(test)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(Boost 1.76.0) 
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
include_directories(include)
add_executable(main RGB565.cpp)
target_link_libraries(main ${OpenCV_LIBS})
