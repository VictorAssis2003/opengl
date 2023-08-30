cmake_minimum_required(VERSION 3.27.2)
project(glfw_project VERSION 0.1.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(glfw_project 
src/main.cpp src/glad.c src/glad.h)

target_link_libraries(glfw_project glfw)
