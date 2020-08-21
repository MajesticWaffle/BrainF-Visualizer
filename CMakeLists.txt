cmake_minimum_required(VERSION 3.16)
project(ZPlusPlus)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(bfv main.cpp output.cpp output.h)