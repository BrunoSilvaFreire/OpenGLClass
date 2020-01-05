#include <unnecessary/graphics/geometry.h>

#include <utility>

namespace un {

    Geometry::Geometry(
            VertexBuffer vBuf,
            IndexBuffer iBuf,
            VertexArrayBuffer vertexArray,
            Material material,
            size_t indicesCount
    ) : vBuf(std::move(vBuf)), iBuf(std::move(iBuf)),
        vertexArray(std::move(vertexArray)), material(std::move(material)),
        indicesCount(indicesCount) {

    }

    Geometry Geometry::from(
            const VertexLayout &layout,
            void *vData,
            size_t vCount,
            uint32_t *iData,
            size_t iCount,
            Material material
    ) {
        VertexBuffer vBuf = VertexBuffer::createAndPush(layout, vData, vCount);
        IndexBuffer iBuf = IndexBuffer::createAndPush(iData, iCount);
        VertexArrayBuffer vao = VertexArrayBuffer::createFor(layout, iBuf, vBuf);
        VertexArrayBuffer::unbind();
        VertexBuffer::unbind();
        IndexBuffer::unbind();
        return Geometry(vBuf, iBuf, vao, material, iCount);
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

    size_t Geometry::getIndicesCount() const {
        return indicesCount;
    }

    void Geometry::bind() const {
        vertexArray.bind();
    }
}