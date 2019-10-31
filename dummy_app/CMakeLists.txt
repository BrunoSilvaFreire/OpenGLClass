add_executable(dummy_app main.cpp)

unnecessary_app(
        dummy_app
        MODULES
        base
        common_ecs
        opengl_rendering
)
target_link_libraries(
        dummy_app
        tinyobjloader
)