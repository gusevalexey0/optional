cmake_minimum_required(VERSION 3.12)
project(optional)

set(CMAKE_CXX_STANDARD 14)

add_library(counted testing.cpp)

add_executable(main main.cpp)
add_executable(testing testing.cpp)
target_link_libraries(testing -lgtest)