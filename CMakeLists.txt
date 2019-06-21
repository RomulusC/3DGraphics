# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (Sandbox VERSION 1.0.0)

file(GLOB PROJECT_HEADERS src/*.hpp, src/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB VENDORS_SOURCES src/vendors/stb_image/*.h, src/vendors/stb_image/*.cpp)

# The main executable
add_executable(main ${PROJECT_SOURCES} ${PROJECT_HEADERS}                               
                               ${VENDORS_SOURCES})

set_property(TARGET main PROPERTY CXX_STANDARD 17)
target_compile_options(main PRIVATE -Wall)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE libglew_static)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)