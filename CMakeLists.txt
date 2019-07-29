# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (Graphics_Dev VERSION 1.0.0)

add_compile_definitions(EG_DEBUG)   
add_compile_definitions(USING_GLFW)   


# Engine
add_subdirectory(Engine)

# Application 
add_subdirectory(Sandbox)

if (WIN32)
  if (MSVC)
    # Additional Settings 
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
  endif (MSVC)

endif (WIN32)
