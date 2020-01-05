set(
        OPENGL_BUFFERS
        include/unnecessary/graphics/buffers/index_buffer.h
        include/unnecessary/graphics/buffers/vertex_array_buffer.h
        include/unnecessary/graphics/buffers/vertex_buffer.h
        include/unnecessary/graphics/buffers/uniform_buffer.h
        src/unnecessary/graphics/buffers/index_buffer.cpp
        src/unnecessary/graphics/buffers/vertex_array_buffer.cpp
        src/unnecessary/graphics/buffers/vertex_buffer.cpp
        #        src/unnecessary/graphics/buffers/uniform_buffer.cpp
)
set(
        OPENGL_RENDERING
        include/unnecessary/graphics/ecs/drawing.h
        src/unnecessary/graphics/ecs/drawing.cpp
        include/unnecessary/graphics/ecs/lighting.h
        include/unnecessary/graphics/ecs/gl.h
        src/unnecessary/graphics/ecs/gl.cpp
)
set(
        OPENGL_MISC
        include/unnecessary/graphics/binding.h
        include/unnecessary/graphics/geometry.h
        include/unnecessary/graphics/graphics.h
        include/unnecessary/graphics/material.h
        include/unnecessary/graphics/texture.h

        include/unnecessary/graphics/utility/debugging.h
        include/unnecessary/graphics/utility/layout.h
        src/unnecessary/graphics/utility/debugging.cpp
        src/unnecessary/graphics/utility/layout.cpp

        src/unnecessary/graphics/material.cpp
        src/unnecessary/graphics/geometry.cpp
        src/unnecessary/graphics/binding.cpp
)
set(
        OPENGL_SHADERS
        include/unnecessary/graphics/shaders/program.h
        include/unnecessary/graphics/shaders/shader.h
        src/unnecessary/graphics/shaders/program.cpp
        src/unnecessary/graphics/shaders/shader.cpp
)
set(
        OPENGL_ALL
        ${OPENGL_BUFFERS}
        ${OPENGL_MISC}
        ${OPENGL_SHADERS}
        ${OPENGL_RENDERING}
)
unnecessary_module(
        opengl_rendering
        SOURCES ${OPENGL_ALL}
)
unnecessary_module_dependencies(
        opengl_rendering
        MODULES base common_ecs
        LIBS glew_s glfw glm_static entityx
)
unnecessary_resources(
        opengl_rendering
        RESOURCES
        shaders/std.frag
        shaders/std.vert
        shaders/std.geom
        assets/teapot.obj
        assets/bunny.obj
)