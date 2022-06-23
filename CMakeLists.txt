cmake_minimum_required(VERSION 3.21)
project(Airport)

set(CMAKE_CXX_STANDARD 14)

add_executable(Airport main.cpp zeit.cpp zeit.h plane.cpp plane.h Tower.cpp Tower.h)
