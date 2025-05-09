cmake_minimum_required(VERSION 3.10)
project(bean)

# Find SDL3
find_package(SDL3 REQUIRED)

# Add executable
add_executable(app src/main.c)

# Link SDL3
target_link_libraries(app PRIVATE SDL3::SDL3)
