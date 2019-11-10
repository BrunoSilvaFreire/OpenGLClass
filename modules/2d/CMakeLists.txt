
set(
        2D_ALL
        include/unnecessary/2d/common.h
        src/unnecessary/2d/common.cpp
)

unnecessary_module(
        2d
        SOURCES ${2D_ALL}
)
unnecessary_module_dependencies(
        2d
        MODULES common_ecs
)