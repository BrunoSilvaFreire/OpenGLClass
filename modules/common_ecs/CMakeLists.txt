set(
        COMMON_ECS_SOURCES
        include/unnecessary/ecs/common.h
        src/unnecessary/ecs/common.cpp
)
unnecessary_module(common_ecs "${COMMON_ECS_SOURCES}")
unnecessary_module_dependency(common_ecs base)