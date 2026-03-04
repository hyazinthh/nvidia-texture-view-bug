cmake_minimum_required(VERSION 3.10)
project(nvidia-texture-view-bug)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
include_directories(glad/include)

add_executable(nvidia-texture-view-bug
    src/main.h
    src/main.cpp
    glad/src/gl.c
)

find_package(OpenGL REQUIRED)
target_link_libraries(nvidia-texture-view-bug glfw OpenGL::GL ${CMAKE_DL_LIBS})
target_compile_features(nvidia-texture-view-bug PRIVATE cxx_std_17)