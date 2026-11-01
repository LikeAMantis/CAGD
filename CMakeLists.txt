cmake_minimum_required (VERSION 3.10)
project ("CAGD")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd

# GLFW Pfade
include_directories("C:/externals/glfw-3.3.8/include")
link_directories("C:/externals/glfw-3.3.8/lib-vc2022")

# Include sub-projects.
add_subdirectory ("Exercise_1")
