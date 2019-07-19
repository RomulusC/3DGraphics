if(CMAKE_COMPILER_IS_GNUCC)
#GCC SPACIFIC SETTING, SPDLOG WONT CORRECTLY COMPILE AS A SHARED LIBRARY 
add_definitions(-fPIC)
endif (CMAKE_COMPILER_IS_GNUCC) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

set(CURRENT_LIBRARY "Engine")

file(GLOB ENGINE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp, ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB ENGINE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE ENGINE_VENDOR_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.h,${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.hpp, 
                                        ${CMAKE_CURRENT_SOURCE_DIR}/src/vendors/*.cpp)

#Configure for Shared Library (DLL or .o)
add_library(${CURRENT_LIBRARY} SHARED ${ENGINE_HEADERS} ${ENGINE_SOURCES} ${ENGINE_VENDOR_SOURCES})
set_property(TARGET ${CURRENT_LIBRARY} PROPERTY CXX_STANDARD 17)

# spdlog
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendors/spdlog EXCLUDE_FROM_ALL)
target_link_libraries(${CURRENT_LIBRARY} PRIVATE spdlog)

# Global Include Directories
target_include_directories(${CURRENT_LIBRARY} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${CURRENT_LIBRARY} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendors/spdlog/include")


if (WIN32)
    # Preprocessor Definitions
    add_compile_definitions(EG_PLATFORM_WINDOWS)
    add_compile_definitions(EG_BUILD_DLL)

    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY CMAKE_BINARY_DIR)
    if (MSVC)
        Set(ENGINE_DLL_DIR "${CMAKE_BINARY_DIR}/${CURRENT_LIBRARY}/$<CONFIG>/" PARENT_SCOPE)  
    else (MSVC)
        Set(ENGINE_DLL_DIR "${CMAKE_BINARY_DIR}/${CURRENT_LIBRARY}/" PARENT_SCOPE)  
    endif (MSVC)
   
endif (WIN32)
