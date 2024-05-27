# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(PBapp VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_subdirectory(app)

# Add the executable
# add_executable(PBapp main.cpp src/*.cpp)

# Include directories for header files (if any)
# target_include_directories(PBapp PUBLIC "${PROJECT_SOURCE_DIR}/app/include")

# If there are any libraries, link them here (none in this simple example)
# target_link_libraries(MyProject PRIVATE some_library)

# Optionally, add custom configurations (e.g., compile options, definitions, etc.)
# target_compile_options(MyProject PRIVATE -Wall -Wextra -pedantic)