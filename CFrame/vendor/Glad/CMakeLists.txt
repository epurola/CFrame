cmake_minimum_required(VERSION 3.10)

project(Glad)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_ARCH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_ARCH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_ARCH}")

# Create a static library target
add_library(Glad STATIC
    src/glad.c
)

# Include directories for Glad
target_include_directories(Glad PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# Set properties for Windows-specific configurations
if(WIN32)
    set_target_properties(Glad PROPERTIES
        STATIC_LIBRARY_FLAGS "/MT" # Enable static runtime on Windows
    )
endif()

# Optional: Set the output directory for intermediate object files
set_target_properties(Glad PROPERTIES
    OBJECT_OUTPUTS "${CMAKE_BINARY_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_ARCH}/Glad"
)

# Ensure that the `Glad` library gets built for the correct system version
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()
