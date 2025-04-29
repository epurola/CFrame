# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define the workspace "CFrame"
project(CFrame)

# Set the architecture and configuration variables
set(CMAKE_SYSTEM_PROCESSOR x64)
set(CMAKE_CXX_STANDARD 17)

# Define the output directories
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/CFrame")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}/CFrame")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/CFrame")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/CFrame/vendor/stb
    ${CMAKE_SOURCE_DIR}/CFrame/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/CFrame/vendor/glm/glm
    ${CMAKE_SOURCE_DIR}/CFrame/vendor/Glad/include
    ${CMAKE_SOURCE_DIR}/CFrame/vendor/SDL3/SDL/include
    ${CMAKE_SOURCE_DIR}/CFrame/vendor/freetype/include
    ${CMAKE_SOURCE_DIR}/CFrame/vendor/freetype/include/freetype
)

add_subdirectory(CFrame/vendor/Glad)
add_subdirectory(CFrame/vendor/SDL3/SDL)


# Define the source files
file(GLOB_RECURSE CFRAME_SRC "${CMAKE_SOURCE_DIR}/CFrame/src/*.cpp" "${CMAKE_SOURCE_DIR}/CFrame/src/*.h")

# Define the CFrame Staticlib target
add_library(CFrame STATIC ${CFRAME_SRC} "CFrame/src/CFrame/Renderer/FrameBuffer.h")

# Link libraries
target_link_libraries(CFrame
    Glad
    SDL3
    freetype
)

# Link directories for external dependencies
link_directories(
    ${CMAKE_SOURCE_DIR}/CFrame/vendor/freetype/lib
)
link_directories(
    ${CMAKE_SOURCE_DIR}/x64/Debug  # The path to where SDL3.lib is located
)

# Add the preprocessor definitions
add_definitions(-DCF_PLATFORM_WINDOWS)

# Handle configuration-specific settings
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCF_DEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DCF_RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif(CMAKE_BUILD_TYPE STREQUAL "Dist")
    add_definitions(-DCF_DIST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()



# Create SandBox executable

# Set the source directory
set(SOURCE_DIR "C:/dev/CFrame/SandBox/src")

# Use file(GLOB ...) to include all .cpp and .h files from the directory
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.h")

# Create the executable with the found files
add_executable(SandBox ${SOURCES} "CFrame/src/CFrame/Renderer/FrameBuffer.h")

#add_executable(SandBox
#    "C:/dev/CFrame/SandBox/src/App.cpp"
#    "C:/dev/CFrame/SandBox/src/ServerInfoBox.cpp"
#    "C:/dev/CFrame/SandBox/src/ServerInfoBox.h"
#)

# Include directories for SandBox
target_include_directories(SandBox PRIVATE
    ${CMAKE_SOURCE_DIR}/CFrame/src
)

# Link the SandBox project with the CFrame static library
target_link_libraries(SandBox CFrame)

# Add platform-specific flags for Windows
if(WIN32)
    set(CMAKE_SYSTEM_VERSION "latest")
    add_definitions(-DCF_PLATFORM_WINDOWS)
endif()

