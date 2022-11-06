cmake_minimum_required(VERSION 3.14)
# require C++20
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_NAME runhw02)

set(SOURCES
    run.cpp
)

add_library(hw02 combinatorics.h combinatorics.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_include_directories(hw02 ${CMAKE_SOURCE_DIR})
target_link_libraries(${EXECUTABLE_NAME} hw02)