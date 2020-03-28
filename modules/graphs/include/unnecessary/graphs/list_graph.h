#ifndef UNNECESSARYENGINE_LIST_GRAPH_H
#define UNNECESSARYENGINE_LIST_GRAPH_H

#include <unnecessary/graphs/graph.h>

namespace un {
    template<typename V, typename E>
    class ListGraph : Graph<V, E> {
    public:
        struct ListVertex {
        private:
            V data;
            std::vector<std::tuple<uint16_t, E>> edges;
        public:
            ListVertex(V data) : data(data), edges() {}

            void connect(uint16_t to, E edge) {
                edges.emplace_back({to, edge});
            }
        };

    private:
        std::vector<ListVertex> vertices;
    public:
        bool isOutOfBounds(uint16_t vertexIndex) override {
            return vertexIndex >= vertices.size();
        }

        uint16_t addVertex(const V &vertex) override {
            vertices.emplace_back(vertex);
            return vertices.size() - 1;
        }

        uint32_t connect(uint16_t from, uint16_t to, const E &edge) override {
            ListVertex &vert = vertices[from];
            vert.connect(to, edge);
            return from;
        }
    };
}
#endif