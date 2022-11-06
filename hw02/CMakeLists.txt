cmake_minimum_required(VERSION 3.14)
# require C++20
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_NAME runhw02)
# so language servers like clangd know what the buildsystem does
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# windows needs "exported" symbols for linking
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors -link hw02.lib)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W3 /WX)

    # so the dll files are alongside the executables
    # and the windows loader is happy (no more error 0xc0000135)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

set(HEADERS 
    hw02.h
)

set(SOURCES
    run.cpp
)
add_library(hw02 combinatorics.h combinatorics.cpp)
add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCES})