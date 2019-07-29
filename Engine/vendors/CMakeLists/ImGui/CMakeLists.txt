cmake_minimum_required (VERSION 3.1)
project (imgui VERSION 1.0.0)

file(GLOB_RECURSE PROJECT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(imgui STATIC ${PROJECT_HEADERS} ${PROJECT_SOURCES})
set_property(TARGET imgui PROPERTY CXX_STANDARD 17)

target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")