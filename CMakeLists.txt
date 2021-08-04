cmake_minimum_required(VERSION 3.12)
project(test)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/Users/bytedance/Documents/boost/include)

add_executable(main RGB565.cpp)
target_link_libraries(main ${OpenCV_LIBS})
