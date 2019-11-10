#ifndef OPENGL_GEOMETRY_H
#define OPENGL_GEOMETRY_H

#include <unnecessary/graphics/material.h>
#include <unnecessary/graphics/buffers/index_buffer.h>
#include <unnecessary/graphics/buffers/vertex_buffer.h>
#include <unnecessary/graphics/buffers/vertex_array_buffer.h>

#include <utility>
#include <unnecessary/graphics/shaders/program.h>
#include <unnecessary/graphics/utility/debugging.h>

namespace un {

    class Geometry {
    private:
        VertexBuffer vBuf;
        IndexBuffer iBuf;
        VertexArrayBuffer vertexArray;
        Material material;
    public:
        Geometry(
                VertexBuffer vBuf,
                IndexBuffer iBuf,
                VertexArrayBuffer vertexArray,
                Material material
        );

        static Geometry from(
                const VertexLayout &layout,
                void *vData,
                size_t vCount,
                uint32_t *iData,
                size_t iCount,
                Material material
        );

        const VertexBuffer &getVertexBuffer() const;

        const IndexBuffer &getIndexBuffer() const;

        const VertexArrayBuffer &getVertexArray() const;

        const Material &getMaterial() const;

        void bind() const;
    };
}

#endif
