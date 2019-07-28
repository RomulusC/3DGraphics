if(CMAKE_COMPILER_IS_GNUCC)
#GCC SPACIFIC SETTING, SPDLOG WONT CORRECTLY COMPILE TO A SHARED LIBRARY 
add_definitions(-fPIC)
endif (CMAKE_COMPILER_IS_GNUCC) 

file(GLOB_RECURSE ENGINE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp, ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE ENGINE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(Engine STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES} )
set_property(TARGET Engine PROPERTY CXX_STANDARD 17)

# spdlog
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendors/spdlog EXCLUDE_FROM_ALL)
target_link_libraries(Engine PUBLIC spdlog)

# glfw
add_subdirectory(vendors/glfw EXCLUDE_FROM_ALL)
target_link_libraries(Engine PUBLIC glfw)

# GLAD
add_subdirectory(vendors/GLAD EXCLUDE_FROM_ALL)
target_link_libraries(Engine PUBLIC GLAD)

# imgui
add_subdirectory(vendors/imgui EXCLUDE_FROM_ALL)
target_link_libraries(Engine PUBLIC imgui)

# glm
add_subdirectory(vendors/glm EXCLUDE_FROM_ALL)
target_link_libraries(Engine PRIVATE glm)

# Global Include Directories
target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_compile_definitions(GLFW_INCLUDE_NONE)   

if (WIN32)
    # Preprocessor Definitions
    add_compile_definitions(EG_PLATFORM_WINDOWS)     


endif (WIN32)
