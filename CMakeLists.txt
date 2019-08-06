cmake_minimum_required(VERSION 3.14)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(thirdparty)
add_executable(
        OpenGL
        src/dummy.cpp
        include/application.h
        include/graphics/buffers/vertex_buffer.h
        include/graphics/buffers/index_buffer.h include/graphics/binding.h include/graphics/graphics.h include/graphics/geometry.h include/graphics/buffers/vertex_array_buffer.h include/ecs/common.h include/graphics/shaders/shader.h include/utility/layout.h include/graphics/material.h include/graphics/shaders/program.h include/utility/debugging.h)
target_include_directories(OpenGL PUBLIC include)
target_link_libraries(OpenGL glew_s glfw glm_static entityx)
if (UNIX)
    target_link_libraries(OpenGL stdc++fs)
endif ()