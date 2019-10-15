set(
        UNNECESSARY_BASE_SOURCES
        include/unnecessary/application.h;
        src/unnecessary/application.cpp
)
unnecessary_module(
        base
        "${UNNECESSARY_BASE_SOURCES}"
)
unnecessary_module_libraries(base "glew_s;glfw;glm_static;entityx")