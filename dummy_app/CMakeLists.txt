add_executable(dummy_app main.cpp)

unnecessary_app(
        dummy_app
        MODULES
        base
        common_ecs
        opengl_rendering
)