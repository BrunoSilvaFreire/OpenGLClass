
function(create_unnecessary_module NAME TYPE SOURCES)
    list(LENGTH "${SOURCES}" TOTAL_FILES)

    message(STATUS "Creating unnecessary module '${NAME}' (${TYPE})")
    add_library(
            unnecessary_${NAME}
            ${TYPE}
            "${SOURCES}"
    )
    set_target_properties(
            unnecessary_${NAME}
            PROPERTIES
            LINKER_LANGUAGE CXX
    )
    target_include_directories(
            unnecessary_${NAME}
            PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endfunction()

function(
        unnecessary_module
        NAME
        SOURCES
)
    create_unnecessary_module(${NAME}_s STATIC "${SOURCES}")
    create_unnecessary_module(${NAME}_d SHARED "${SOURCES}")
    create_unnecessary_module(${NAME}_m MODULE "${SOURCES}")
endfunction()

function(unnecessary_module_libraries NAME LIBS)
    message("Module ${NAME} uses libraries ${LIBS}")

    target_link_libraries(
            unnecessary_${NAME}_s
            ${LIBS}
    )
    target_link_libraries(
            unnecessary_${NAME}_d
            ${LIBS}
    )
    target_link_libraries(
            unnecessary_${NAME}_m
            ${LIBS}
    )
endfunction()

function(unnecessary_module_dependency NAME DEPENDENCIES)
    foreach (dep ${DEPENDENCIES})
        message("Including ${dep}")
        target_link_libraries(
                unnecessary_${NAME}_s
                unnecessary_${dep}_s
        )
        target_link_libraries(
                unnecessary_${NAME}_d
                unnecessary_${dep}_d
        )

    endforeach ()
endfunction()