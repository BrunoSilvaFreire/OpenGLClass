
#ifndef UNNECESSARYENGINE_GRAPH_H
#define UNNECESSARYENGINE_GRAPH_H

#include <cstdint>
#include <vector>
#include <stdexcept>

namespace un {
    template<typename V, typename E>
    class Graph {
    public:
        virtual bool isOutOfBounds(uint16_t vertexIndex) = 0;

        virtual uint16_t addVertex(const V &vertex) = 0;

        virtual uint32_t connect(uint16_t from, uint16_t to, const E &edge) = 0;

        void connectBilateral(uint16_t a, uint16_t b, const E &edge) {
            connect(a, b, edge);
            connect(b, a, edge);
        }
    };



}
#endif
