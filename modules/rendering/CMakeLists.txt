set(
        RENDER_GRAPH include/unnecessary/rendering/render_graph.h
)
set(
        RENDERING_MISC
        include/unnecessary/rendering/rendering_backend.h
        include/unnecessary/rendering/ecs/components.h
)
set(
        RENDERING_LIGHTING
        include/unnecessary/rendering/lighting/lights.h
)
set(
        RENDERING_ALL
        ${RENDER_GRAPH}
        ${RENDERING_MISC}
        ${RENDERING_LIGHTING}
)
unnecessary_module(
        rendering
        SOURCES ${RENDERING_ALL}
)
unnecessary_module_dependencies(
        rendering
        MODULES graphs
        LIBS glm_static
)