cmake_minimum_required(VERSION 3.28)
project(file_extension_reading CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
add_executable(main src/main.cpp src/file.cpp)
