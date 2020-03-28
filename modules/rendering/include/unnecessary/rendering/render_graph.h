#ifndef UNNECESSARYENGINE_RENDER_GRAPH_H
#define UNNECESSARYENGINE_RENDER_GRAPH_H

#include <unnecessary/graphs/graph.h>

namespace un {
    struct RenderingVertex {
        uint64_t cmdBuffer;
        uint32_t priority;
    };
    struct RenderingEdge {

    };

    typedef MatrixGraph<RenderingVertex, RenderingEdge> RenderGraph;
}
#endif
