cmake_minimum_required(VERSION 3.16)
project(Random)

set(CMAKE_CXX_STANDARD 20)

add_library (Random STATIC source/Random.cpp)

target_include_directories(Random PUBLIC include)