cmake_minimum_required(VERSION 3.16)

project(chess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Add include directories
include_directories(/opt/homebrew/include)

# Add library directories
link_directories(/opt/homebrew/lib)

# Find all source files in src directory and subdirectories
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

# Create executable
add_executable(chess ${SOURCES})

# Link SDL3 library
target_link_libraries(chess SDL3)

# Set rpath for macOS to find libraries at runtime
if(APPLE)
    set_target_properties(chess PROPERTIES
        INSTALL_RPATH "/opt/homebrew/lib"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()
