cmake_minimum_required(VERSION 3.8)
project(Akinator)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp TreeLib.cpp TreeLib.h AkinatorLib.cpp AkinatorLib.h)
add_executable(Akinator ${SOURCE_FILES})