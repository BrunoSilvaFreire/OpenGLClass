
#ifndef UNNECESSARYENGINE_RENDERING_BACKEND_H
#define UNNECESSARYENGINE_RENDERING_BACKEND_H

#include <unnecessary/rendering/render_graph.h>

namespace un {
    class RenderingBackend {
        virtual void render(const RenderGraph &graph) = 0;
    };
}
#endif
