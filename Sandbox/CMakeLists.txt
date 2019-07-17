# Projects Settings
set(CURRENT_LIBRARY "Sandbox")

file(GLOB PROJECT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp, ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE VENDORS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.h, ${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.cpp)

# The main executable
add_executable(${CURRENT_LIBRARY} ${PROJECT_SOURCES} ${PROJECT_HEADERS}                               
                               ${VENDORS_SOURCES})

target_link_libraries(${CURRENT_LIBRARY} PRIVATE Engine)
target_link_libraries(${CURRENT_LIBRARY} PRIVATE glfw)
target_link_libraries(${CURRENT_LIBRARY} PRIVATE libglew_static)
target_link_libraries(${CURRENT_LIBRARY} PRIVATE glm)

# Additional Settings
target_compile_options(${CURRENT_LIBRARY} PRIVATE -Wall)

set_property(TARGET ${CURRENT_LIBRARY} PROPERTY CXX_STANDARD 17)

target_include_directories(${CURRENT_LIBRARY} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (WIN32)
# Preprocessor Definitions
    add_compile_definitions(EG_PLATFORM_WINDOWS)

    if (MSVC)

    #ENGINE.DLL POST_BUILD COPY: [Engine/Debug/Engine.dll] to [Sandbox/Debug/]   
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY CMAKE_BINARY_DIR)
    Set(SANDBOX_EXE_LOC "${CMAKE_BINARY_DIR}/${CURRENT_LIBRARY}/$<CONFIG>/") 

    add_custom_command(TARGET  ${CURRENT_LIBRARY} POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  
    "${ENGINE_DLL_DIR}/Engine.dll"     
    ${SANDBOX_EXE_LOC})                 
    #END ENGINE.DLL POST_BUILD COPY

   endif(MSVC)

endif (WIN32)

