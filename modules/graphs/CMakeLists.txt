set(
        GRAPHS_BASE
        include/unnecessary/graphs/graph.h
        include/unnecessary/graphs/matrix_graph.h
        include/unnecessary/graphs/list_graph.h
)
set(
        GRAPHS_ALL
        ${GRAPHS_BASE}
)
unnecessary_module(
        graphs
        SOURCES ${GRAPHS_ALL}
)
add_executable(graphs_dummy_app dummy/dummy.cpp)
target_link_libraries(graphs_dummy_app unnecessary_graphs_static)