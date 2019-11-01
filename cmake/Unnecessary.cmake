
set(
        UNNECESSARY_MODULE_TYPES
        STATIC;SHARED
)
macro(line_break)
    message("")
endmacro()
function(
        unnecessary_module
        NAME
)
    cmake_parse_arguments(PARSE_ARGV 0 unnecessary_module "" "" "SOURCES")
    list(LENGTH unnecessary_module_SOURCES TOTAL_FILES)
    message("Creating module ${NAME} (${TOTAL_FILES} files)")
    foreach (type ${UNNECESSARY_MODULE_TYPES})
        string(TOLOWER ${type} lower)
        set(subname unnecessary_${NAME}_${lower})
        message(STATUS "Creating submodule '${subname}'")
        add_library(
                ${subname}
                ${type}
                ${unnecessary_module_SOURCES}
        )
        set_target_properties(
                ${subname}
                PROPERTIES
                LINKER_LANGUAGE CXX
        )
        target_include_directories(
                ${subname}
                PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
    endforeach ()
    line_break()
endfunction()


function(unnecessary_app NAME DEPENDENCY_TYPE)
    _unnecessary_collect_artifacts(unnecessary_app)
    message("Creating application ${NAME}")

    foreach (dep ${unnecessary_app_MODULES})
        message(STATUS "+ Module '${dep}'")
        set(subdep unnecessary_${dep}_static)
        target_link_libraries(
                ${NAME}
                ${subdep}
        )

        _unnecessary_collect_resources(${NAME} ${dep} temp_res)
        message("${temp_res}")
        if (NOT "${temp_res}" STREQUAL "")
            message(STATUS "+ Resources of '${dep}'")
            get_target_property(FOO_SOURCE_DIR ${subdep} SOURCE_DIR)
            foreach (res ${temp_res})
                message("${FOO_SOURCE_DIR}/${res} to ${CMAKE_CURRENT_BINARY_DIR}/${res}")
                add_custom_command(
                        TARGET ${NAME}
                        COMMAND ${CMAKE_COMMAND} -E copy "${FOO_SOURCE_DIR}/${res}" "${CMAKE_CURRENT_BINARY_DIR}/${res}"
                        POST_BUILD
                )
            endforeach ()
        endif ()


    endforeach ()

endfunction()
#
# Collects libraries as modules specified as parameters.
#
# Doesn't collect resources
#
macro(_unnecessary_collect_artifacts PREFIX)
    cmake_parse_arguments(PARSE_ARGV 0 ${PREFIX} "" "" "MODULES;LIBS")
    list(LENGTH ${PREFIX}_MODULES MOD_COUNT)
    list(LENGTH ${PREFIX}_LIBS LIB_COUNT)
    set(HAS_MODS (${MOD_COUNT} GREATER 0))
    set(HAS_LIBS (${LIB_COUNT} GREATER 0))
    if (NOT ${HAS_MODS} AND NOT ${HAS_LIBS})
        message(AUTHOR_WARNING "No modules or libraries listed as dependencies!")
        return()
    endif ()
    set(DEP_MSG "Adding ")
    if (${HAS_MODS})
        string(APPEND DEP_MSG "${MOD_COUNT} modules")
        if (${HAS_LIBS})
            string(APPEND DEP_MSG " and ")
        endif ()
    endif ()
    if (${HAS_LIBS})
        string(APPEND DEP_MSG "${MOD_COUNT} libraries")
    endif ()
    string(APPEND DEP_MSG " as dependencies of ${NAME}")
endmacro()
macro(_unnecessary_collect_resources NAME DEP OUT)
    foreach (type ${UNNECESSARY_MODULE_TYPES})
        string(TOLOWER ${type} lower)
        set(mod unnecessary_${NAME}_${lower})
        set(subdep unnecessary_${DEP}_${lower})
        get_target_property(mod_res ${subdep} UNNECESSARY_RESOURCES)
        if (NOT "${mod_res}" STREQUAL "mod_res-NOTFOUND")
            foreach (res ${mod_res})
                if (NOT ${res} IN_LIST "${OUT}")
                    list(APPEND ${OUT} ${res})

                endif ()
            endforeach ()
        endif ()

    endforeach ()
endmacro()
function(unnecessary_module_dependencies NAME)
    _unnecessary_collect_artifacts(unnecessary_module_dependencies)
    foreach (dep ${unnecessary_module_dependencies_MODULES})
        message(STATUS "+ Module '${dep}'")
        foreach (type ${UNNECESSARY_MODULE_TYPES})
            string(TOLOWER ${type} lower)
            set(mod unnecessary_${NAME}_${lower})
            set(subdep unnecessary_${dep}_${lower})
            target_link_libraries(
                    ${mod}
                    ${subdep}
            )

        endforeach ()
        _unnecessary_collect_resources(${NAME} ${dep} dep_res)
        if (NOT ${dep_res} STREQUAL "")
            message("+ Resources of ${dep}")
            unnecessary_resources(
                    ${NAME}
                    RESOURCES ${dep_res}
            )
        endif ()

    endforeach ()
    foreach (lib ${unnecessary_module_dependencies_LIBS})
        message(STATUS "+ Library '${lib}'")
    endforeach ()
    foreach (type ${UNNECESSARY_MODULE_TYPES})
        string(TOLOWER ${type} lower)
        target_link_libraries(
                unnecessary_${NAME}_${lower}
                ${unnecessary_module_dependencies_LIBS}
        )
    endforeach ()
    line_break()

endfunction()
function(_add_unnecessary_resources NAME RESOURCES)
    foreach (file ${RESOURCES})
        set(out ${CMAKE_CURRENT_BINARY_DIR}/resources/${file})
        set(in ${CMAKE_CURRENT_SOURCE_DIR}/${file})

        get_filename_component(parent ${out} DIRECTORY)
        #[[add_custom_command(
                TARGET ${NAME}
                POST_BUILD
                COMMAND mkdir -p ${parent} && cp ${in} ${out}
        )]]
    endforeach ()
    get_target_property(
            existing_resources
            ${NAME}
            UNNECESSARY_RESOURCES
    )
    if (NOT "${existing_resources}" STREQUAL "existing_resources-NOTFOUND")
        list(APPEND RESOURCES ${existing_resources})
    endif ()
    set_target_properties(
            ${NAME}
            PROPERTIES
            UNNECESSARY_RESOURCES "${RESOURCES}"
    )


endfunction()
function(unnecessary_resources NAME)
    cmake_parse_arguments(PARSE_ARGV 0 unnecessary_resources "" "" "RESOURCES")
    foreach (type ${UNNECESSARY_MODULE_TYPES})
        string(TOLOWER ${type} lower)
        set(subname unnecessary_${NAME}_${lower})
        _add_unnecessary_resources(${subname} "${unnecessary_resources_RESOURCES}")
    endforeach ()

endfunction()
