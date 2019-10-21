
unnecessary_module(
        base
        SOURCES
        include/unnecessary/application.h
        src/unnecessary/application.cpp
)
unnecessary_module_dependencies(base
        LIBS
        glew_s;glfw;glm_static;entityx
        )