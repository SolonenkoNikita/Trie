cmake_minimum_required(VERSION 3.16)
project(Compare)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
    abseil
    GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
    GIT_TAG        20230125.1 
)

FetchContent_MakeAvailable(abseil)

add_executable(Compare source/main.cpp)

target_link_libraries(Compare Trie Random absl::btree)
