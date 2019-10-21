
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
)
    cmake_parse_arguments(PARSE_ARGV 0 unnecessary_module "" "" "SOURCES")

    create_unnecessary_module(${NAME}_s STATIC "${unnecessary_module_SOURCES}")
    create_unnecessary_module(${NAME}_d SHARED "${unnecessary_module_SOURCES}")
    create_unnecessary_module(${NAME}_m MODULE "${unnecessary_module_SOURCES}")
endfunction()


function(unnecessary_module_dependencies NAME)
    cmake_parse_arguments(PARSE_ARGV 0 unnecessary_module_dependencies "" "" "MODULES;LIBS")
    foreach (dep ${unnecessary_module_dependencies_MODULES})
        message(STATUS "Uses module '${dep}'")
        target_link_libraries(
                unnecessary_${NAME}_s
                unnecessary_${dep}_s
        )
        target_link_libraries(
                unnecessary_${NAME}_d
                unnecessary_${dep}_d
        )

    endforeach ()
    foreach (lib ${unnecessary_module_dependencies_LIBS})
        message(STATUS "Uses library '${lib}'")
    endforeach ()

    target_link_libraries(
            unnecessary_${NAME}_s
            ${unnecessary_module_dependencies_LIBS}
    )
    target_link_libraries(
            unnecessary_${NAME}_d
            ${unnecessary_module_dependencies_LIBS}
    )
    target_link_libraries(
            unnecessary_${NAME}_m
            ${unnecessary_module_dependencies_LIBS}
    )
endfunction()