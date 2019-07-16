# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (Sandbox VERSION 1.0.0)

# Engine
add_subdirectory(Engine)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

# Application 
add_subdirectory(Application)