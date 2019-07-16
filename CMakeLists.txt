# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (Sandbox VERSION 1.0.0)
set(Application "Application")


file(GLOB PROJECT_HEADERS src/*.hpp, src/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE VENDORS_SOURCES src/vendors/*.h, src/vendors/*.cpp)

# The main executable
add_executable(Application ${PROJECT_SOURCES} ${PROJECT_HEADERS}                               
                               ${VENDORS_SOURCES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Application)

set_property(TARGET Application PROPERTY CXX_STANDARD 17)
target_compile_options(Application PRIVATE -Wall)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(Application PRIVATE glfw)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(Application PRIVATE libglew_static)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(Application PRIVATE glm)