cmake_minimum_required(VERSION 3.6)
project(VanEmdeBoasTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14")

set(SOURCE_FILES main.cpp veb.cpp veb.h veb.cpp my_math.h)
add_executable(VanEmdeBoasTree ${SOURCE_FILES})