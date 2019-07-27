file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Sandbox.cpp)

add_executable(Sandbox ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(Sandbox PRIVATE Engine)

# Additional Settings
target_compile_options(Sandbox PRIVATE -Wall)
set_property(TARGET Sandbox PROPERTY CXX_STANDARD 17)



if (WIN32)
# Preprocessor Definitions
    add_compile_definitions(EG_PLATFORM_WINDOWS)
endif (WIN32)

