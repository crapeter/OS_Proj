cmake_minimum_required(VERSION 3.11)

# Project name and C++ version
project(OS_Proj)
set(CMAKE_CXX_STANDARD 20)

# Add FetchContent module
include(FetchContent)

# Fetch Scheduling library
FetchContent_Declare(
  scheduling
  GIT_REPOSITORY https://github.com/dpuyda/scheduling
  GIT_TAG main
  GIT_SHALLOW TRUE
)

# Make the scheduling library available
FetchContent_MakeAvailable(scheduling)

# Add your source files
add_executable(OS_Proj main.cpp)

# Include the scheduling headers directory
target_include_directories(OS_Proj PRIVATE ${scheduling_SOURCE_DIR}/include)

# Link the scheduling library
target_link_libraries(OS_Proj PRIVATE scheduling)

# Optional: Add additional compile flags if needed
# target_compile_options(MyProject PRIVATE -Wall -Wextra)
