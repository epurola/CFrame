cmake_minimum_required(VERSION 3.14)
project(CFrame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect source files
file(GLOB_RECURSE CFRAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/CFrame/*.cpp)
file(GLOB_RECURSE CFRAME_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/CFrame/*.h)

# Add static library
add_library(CFrame STATIC ${CFRAME_SOURCES} ${CFRAME_HEADERS}  )

# Include paths
target_include_directories(CFrame PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CFrame
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3/SDL/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/freetype/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/freetype/include/freetype
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb
)

# SDL build options
set(SDL_SHARED ON)
set(SDL_STATIC ON)
set(SDL_BUILD_EXAMPLES OFF)

# Add subdirectories (ensure these folders contain CMakeLists.txt)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/Glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3/SDL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/freetype)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)

# Link dependencies
target_link_libraries(CFrame
    Glad
    SDL3-shared
    freetype
    Shcore
)

# Platform define
add_definitions(-DCF_PLATFORM_WINDOWS)
