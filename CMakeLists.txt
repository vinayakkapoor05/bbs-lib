cmake_minimum_required(VERSION 3.10)
project(bbs_lib CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(bbs_toy STATIC
    src/bbs_toy.cpp
)

target_include_directories(bbs_toy
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(toy_demo examples/toy_demo.cpp)
target_link_libraries(toy_demo PRIVATE bbs_toy)