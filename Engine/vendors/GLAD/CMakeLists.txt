cmake_minimum_required (VERSION 3.1)
project (GLAD VERSION 1.0.0)

file(GLOB_RECURSE PROJECT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)

add_library(GLAD STATIC ${PROJECT_HEADERS} ${PROJECT_SOURCES})
set_property(TARGET GLAD PROPERTY CXX_STANDARD 17)

target_include_directories(GLAD PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")