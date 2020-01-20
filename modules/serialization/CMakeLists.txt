set(
        SERIALIZATION_ALL
        include/unnecessary/serialization/json_backend.h
        include/unnecessary/serialization/serialization.h
        include/unnecessary/serialization/serialization_backend.h
)
unnecessary_module(
        serialization
        SOURCES ${SERIALIZATION_ALL}
)