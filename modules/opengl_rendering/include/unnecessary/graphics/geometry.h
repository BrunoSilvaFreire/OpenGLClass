#ifndef OPENGL_GEOMETRY_H
#define OPENGL_GEOMETRY_H

#include <unnecessary/graphics/material.h>
#include <unnecessary/graphics/buffers/index_buffer.h>
#include <unnecessary/graphics/buffers/vertex_buffer.h>
#include <unnecessary/graphics/buffers/vertex_array_buffer.h>

#include <utility>
#include <unnecessary/graphics/shaders/program.h>
#include <unnecessary/graphics/utility/debugging.h>

namespace gl {
    class Geometry {
    private:
        VertexBuffer vBuf;
        IndexBuffer iBuf;
        VertexArrayBuffer vertexArray;
        Material material;
        ShaderProgram program;
    public:
        Geometry(
                const VertexBuffer &vBuf,
                const IndexBuffer &iBuf,
                const VertexArrayBuffer &vertexArray,
                const Material &material
        );

        static Geometry from(
                const VertexLayout &layout,
                void *vData,
                size_t vCount,
                uint32_t *iData,
                size_t iCount,
                const Material &material
        );

        const VertexBuffer &getVertexBuffer() const;

        const IndexBuffer &getIndexBuffer() const;

        const VertexArrayBuffer &getVertexArray() const;

        const Material &getMaterial() const;

        const ShaderProgram &getProgram() const;

        void bind() const;
    };
}

#endif
