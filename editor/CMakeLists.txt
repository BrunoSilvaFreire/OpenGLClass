add_executable(
        unnecessary_editor main.cpp
)
target_link_libraries(unnecessary_editor glfw)
set(
        FLUTTER_HOME
        /opt/flutter/bin/cache/artifacts/engine/linux-x64/
)
target_include_directories(
        unnecessary_editor
        PUBLIC
        ${FLUTTER_HOME}
        ${FLUTTER_HOME}/cpp_client_wrapper_glfw/include/
)