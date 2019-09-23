
add_library(
        unnecessary
        include/unnecessary/application.h
        include/unnecessary/graphics/buffers/vertex_buffer.h
        include/unnecessary/graphics/buffers/index_buffer.h
        include/unnecessary/graphics/binding.h
        include/unnecessary/graphics/graphics.h include/unnecessary/graphics/geometry.h include/unnecessary/graphics/buffers/vertex_array_buffer.h include/unnecessary/ecs/common.h include/unnecessary/graphics/shaders/shader.h include/unnecessary/utility/layout.h include/unnecessary/graphics/material.h include/unnecessary/graphics/shaders/program.h include/unnecessary/utility/debugging.h ../dummy_app/main.cpp src/unnecessary/application.cpp src/unnecessary/utility/layout.cpp src/unnecessary/graphics/material.cpp src/unnecessary/graphics/geometry.cpp src/unnecessary/graphics/shaders/program.cpp src/unnecessary/graphics/shaders/shader.cpp src/unnecessary/graphics/buffers/index_buffer.cpp src/unnecessary/graphics/buffers/vertex_array_buffer.cpp src/unnecessary/graphics/buffers/vertex_buffer.cpp src/unnecessary/utility/debugging.cpp src/unnecessary/ecs/common.cpp)
target_include_directories(unnecessary PUBLIC include)
target_link_libraries(unnecessary glew_s glfw glm_static entityx)
if (UNIX)
    target_link_libraries(unnecessary stdc++fs)
endif ()