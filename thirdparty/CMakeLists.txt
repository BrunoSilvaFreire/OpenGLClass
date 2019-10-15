set(OpenGL_GL_PREFERENCE GLVND)
add_subdirectory(glew/build/cmake)
add_subdirectory(glfw)

set(GLM_TEST_ENABLE OFF GLOBAL CACHED)

add_subdirectory(glm)
target_compile_definitions(glm INTERFACE GLM_CONFIG_XYZW_ONLY)
add_subdirectory(entityx)
set(ENTITYX_BUILD_TESTING false GOBAL CACHED)
target_include_directories(
        glm_static
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glm>
)
target_include_directories(
        glew_s
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glew/include>
)

add_library(
        lodepng
        lodepng/lodepng.h
        lodepng/lodepng.cpp
)
target_include_directories(
        lodepng
        PUBLIC
        lodepng
)