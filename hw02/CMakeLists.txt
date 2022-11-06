cmake_minimum_required(VERSION 3.14)
# require C++20
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_NAME runhw02)

set(SOURCES
    run.cpp
)
target_include_directories(${CMAKE_SOURCE_DIR})
add_library(hw02 combinatorics.h combinatorics.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} hw02)
target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_20)