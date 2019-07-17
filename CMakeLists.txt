# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (Graphics_Dev VERSION 1.0.0)

set(MASTERDIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

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
add_subdirectory(Sandbox)



if (WIN32)

  # Additional Settings 
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

endif (WIN32)
