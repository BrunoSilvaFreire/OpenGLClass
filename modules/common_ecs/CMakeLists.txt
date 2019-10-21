set(
        COMMON_ECS_SOURCES
        include/unnecessary/ecs/common.h
        src/unnecessary/ecs/common.cpp
)
unnecessary_module(
        common_ecs
        SOURCES ${COMMON_ECS_SOURCES}
)
unnecessary_module_dependencies(
        common_ecs
        MODULES base
)