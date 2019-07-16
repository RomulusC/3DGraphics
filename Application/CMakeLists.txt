# Projects Settings

file(GLOB PROJECT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp, ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE VENDORS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.h, ${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.cpp)

# The main executable
add_executable(Application ${PROJECT_SOURCES} ${PROJECT_HEADERS}                               
                               ${VENDORS_SOURCES})

target_link_libraries(Application PRIVATE Engine)
target_link_libraries(Application PRIVATE glfw)
target_link_libraries(Application PRIVATE libglew_static)
target_link_libraries(Application PRIVATE glm)

#Additional Settings
target_compile_options(Application PRIVATE -Wall)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Application)

set_property(TARGET Application PROPERTY CXX_STANDARD 17)

target_include_directories(Application PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")