cmake_minimum_required (VERSION 3.8)

project(Vulkan_Demos)

# set language std
set(CMAKE_CXX_STANDARD 20)

# Disable fallback to a previous version
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable CXX Syntax EXTENSIONS
set(CMAKE_CXX_EXTENSIONS OFF)

# Add sub directories
add_subdirectory(demos)



