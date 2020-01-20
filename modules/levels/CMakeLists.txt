unnecessary_module(
        worlds
        SOURCES include/unnecessary/worlds/world.h
)
unnecessary_module_dependencies(
        worlds
        MODULES base common_ecs serialization
)