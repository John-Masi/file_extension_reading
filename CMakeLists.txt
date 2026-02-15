cmake_minimum_required(VERSION 3.28)
project(file_extension_reading CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(file_extension_reading src/main.cpp src/file.cpp)

#target_include_directories(file_extension_reading PRIVATE ${CMAKE_SOURCE_DIR}/include)
