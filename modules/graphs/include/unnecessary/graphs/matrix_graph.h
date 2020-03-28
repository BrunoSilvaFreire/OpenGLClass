#ifndef UNNECESSARYENGINE_MATRIX_GRAPH_H
#define UNNECESSARYENGINE_MATRIX_GRAPH_H

#include <unnecessary/graphs/graph.h>

namespace un {
    template<typename V, typename E>
    class MatrixGraph : Graph<V, E> {
    private:
        std::vector<V> vertices;
        std::vector<E> edges;

        void resizeEdgesToFit() {
            auto totalVertices = vertices.size();
            auto desiredEdges = totalVertices * totalVertices;
            edges.resize(desiredEdges);
        }

    public:
        const std::vector<V> &getVertices() const {
            return vertices;
        }

        const std::vector<E> &getEdges() const {
            return edges;
        }

        uint64_t indexOfEdge(uint32_t from, uint32_t to) {
            auto size = vertices.size();
            return from * size + to;
        }

        bool isOutOfBounds(uint16_t vertexIndex) override {
            return vertexIndex >= vertices.size();
        }

        template<typename ...T>
        uint16_t emplaceVertex(T... args) {
            vertices.emplace_back(std::forward<T...>(args...));
            resizeEdgesToFit();
            return vertices.size() - 1;
        }

        uint16_t addVertex(const V &vertex) override {
            vertices.push_back(vertex);
            resizeEdgesToFit();
            return vertices.size() - 1;
        }


        uint32_t connect(uint16_t from, uint16_t to, const E &edge) override {
            if (isOutOfBounds(from) || isOutOfBounds(to)) {
                throw std::runtime_error("Parameters are out of bounds");
            }
            auto edgeIndex = indexOfEdge(from, to);
            edges[edgeIndex] = edge;
            return edgeIndex;
        }

        template<typename ...T>
        uint32_t connect(uint16_t from, uint16_t to, T... args) {
            if (isOutOfBounds(from) || isOutOfBounds(to)) {
                throw std::runtime_error("Parameters are out of bounds");
            }
            auto edgeIndex = indexOfEdge(from, to);
            edges[edgeIndex] = E(std::forward<T...>(args...));
            return edgeIndex;
        }
    };
}
#endif