#ifndef OPENGL_GEOMETRY_H
#define OPENGL_GEOMETRY_H

#include <graphics/material.h>
#include <graphics/buffers/index_buffer.h>
#include <graphics/buffers/vertex_buffer.h>
#include <graphics/buffers/vertex_array_buffer.h>

#include <utility>
#include <graphics/shaders/program.h>
#include <utility/debugging.h>

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
        )
                : vBuf(vBuf), iBuf(iBuf), vertexArray(vertexArray), material(material),
                  program(ShaderProgram(*material.getShader())) {}

        static Geometry from(
                const VertexLayout &layout,
                void *vData,
                size_t vCount,
                uint32_t *iData,
                size_t iCount,
                const Material &material
        ) {
            VertexBuffer vBuf = VertexBuffer::createAndPush(layout, vData, vCount);
            IndexBuffer iBuf = IndexBuffer::createAndPush(iData, iCount);
            VertexArrayBuffer vao = VertexArrayBuffer::createFor(layout, iBuf, vBuf);
            VertexArrayBuffer::unbind();
            VertexBuffer::unbind();
            IndexBuffer::unbind();
            return Geometry(vBuf, iBuf, vao, material);
        }

        const VertexBuffer &getVertexBuffer() const {
            return vBuf;
        }

        const IndexBuffer &getIndexBuffer() const {
            return iBuf;
        }

        const VertexArrayBuffer &getVertexArray() const {
            return vertexArray;
        }

        const Material &getMaterial() const {
            return material;
        }

        const ShaderProgram &getProgram() const {
            return program;
        }

        void draw() {
            vertexArray.bind();
            glCall(glUseProgram(program.getId()));
            glCall(
                    glDrawElements(
                            GL_TRIANGLES,
                            iBuf.getLength(),
                            GL_UNSIGNED_INT, nullptr
                    )
            );
        }

        void bind() const {
            vertexArray.bind();
            vBuf.bind();
            iBuf.bind();
        }
    };
}

#endif
