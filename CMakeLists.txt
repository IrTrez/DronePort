cmake_minimum_required(VERSION 3.22)
project(DronePort)

set(CMAKE_CXX_STANDARD 14)

include_directories(DronePort)

add_executable(DronePort
        DronePort/components.cpp
        DronePort/components.h
        DronePort/main.cpp)
