add_subdirectory(glew/build/cmake)
message("${OPENGL_LIBRARIES}")
add_subdirectory(glfw)

set(GLM_TEST_ENABLE OFF CACHE BOOL "Disable GLM tests")

add_subdirectory(glm)
target_compile_definitions(glm_static INTERFACE GLM_FORCE_XYZW_ONLY)
add_subdirectory(entityx)
set(ENTITYX_BUILD_TESTING OFF CACHE BOOL "Disabl entityx tests")
set(
        BUILD_STATIC_LIBS ON CACHE BOOL "Enable GLM static lib"
)
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

target_compile_definitions(
        glew_s
        PUBLIC
        GLEW_NO_GLU
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
add_subdirectory(
        tinyobjloader
)