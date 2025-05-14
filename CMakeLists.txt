# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/CFrame")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}/CFrame")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/CFrame")

add_subdirectory(CFrame) 

if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DCF_DEBUG)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  /Zi /Od")
        
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_definitions(-DCF_RELEASE)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Zi /Od")

        
    elseif (CMAKE_BUILD_TYPE STREQUAL "Dist")
        add_definitions(-DCF_DIST)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
    endif()
endif()


# Set the source directory
set(SOURCE_DIR "C:/dev/CFrame/SandBox/src")

# Use file(GLOB ...) to include all .cpp and .h files from the directory
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.h")

# Create the executable with the found files
add_executable(SandBox ${SOURCES} )

# Include directories for SandBox
target_include_directories(SandBox PRIVATE
    ${CMAKE_SOURCE_DIR}/CFrame/src
    ${CMAKE_SOURCE_DIR}/CFrame/vendor
)

# Link the SandBox project with the CFrame static library
target_link_libraries(SandBox CFrame)

# Add platform-specific flags for Windows
if(WIN32)
    set(CMAKE_SYSTEM_VERSION "latest")
    add_definitions(-DCF_PLATFORM_WINDOWS)
endif()

