#include <unnecessary/graphics/geometry.h>

namespace gl {

    Geometry::Geometry(
            const VertexBuffer &vBuf,
            const IndexBuffer &iBuf,
            const VertexArrayBuffer &vertexArray,
            const Material &material
    )
            : vBuf(vBuf), iBuf(iBuf), vertexArray(vertexArray), material(material),
              program(ShaderProgram(*material.getShader())) {}

    Geometry Geometry::from(
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

    const VertexBuffer &Geometry::getVertexBuffer() const {
        return vBuf;
    }

    const IndexBuffer &Geometry::getIndexBuffer() const {
        return iBuf;
    }

    const VertexArrayBuffer &Geometry::getVertexArray() const {
        return vertexArray;
    }

    const Material &Geometry::getMaterial() const {
        return material;
    }

    const ShaderProgram &Geometry::getProgram() const {
        return program;
    }

    void Geometry::draw() {
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

    void Geometry::bind() const {
        vertexArray.bind();
        vBuf.bind();
        iBuf.bind();
    }
}