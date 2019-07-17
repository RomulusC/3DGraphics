#GCC SPACIFIC SETTING, SPDLOG WONT CORRECTLY COMPILE AS A SHARED LIBRARY 
if(CMAKE_COMPILER_IS_GNUCC)
add_definitions(-fPIC)
endif (CMAKE_COMPILER_IS_GNUCC) 

set(CURRENT_LIBRARY "Engine")
file(GLOB ENGINE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp, ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB ENGINE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE ENGINE_VENDOR_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.h,${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.hpp, 
                                        ${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.cpp)

add_library(${CURRENT_LIBRARY} SHARED ${ENGINE_HEADERS} ${ENGINE_SOURCES} ${ENGINE_VENDOR_SOURCES})

# spdlog
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendors/spdlog
 EXCLUDE_FROM_ALL)
target_link_libraries(${CURRENT_LIBRARY} PRIVATE spdlog)

target_include_directories(${CURRENT_LIBRARY} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${CURRENT_LIBRARY} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendors/spdlog/include")


if (WIN32)
    # Preprocessor Definitions
    add_compile_definitions(EG_PLATFORM_WINDOWS)
    add_compile_definitions(EG_BUILD_DLL)


    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ENGINE_OUTPUT_DIRECTORY})
endif (WIN32)
