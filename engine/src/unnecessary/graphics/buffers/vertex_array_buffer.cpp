#include <unnecessary/graphics/buffers/vertex_array_buffer.h>

namespace gl {

    VertexArrayBuffer::VertexArrayBuffer(uint32_t id) : id(id) {

    }

    VertexArrayBuffer
    VertexArrayBuffer::createFor(const VertexLayout &layout, const IndexBuffer &ibo, const VertexBuffer &vbo) {
        uint32_t id;
        glCall(glCreateVertexArrays(1, &id));
        VertexArrayBuffer buffer(id);
        buffer.bind();
        ibo.bind();
        vbo.bind();
        const auto &elements = layout.getElements();
        uint32_t offset = 0;
        uint8_t stride = layout.getStride();
        for (size_t i = 0; i < elements.size(); ++i) {
            auto &e = elements[i];
            glCall(glEnableVertexAttribArray(i));
            glCall(
                    glVertexAttribPointer(
                            i,
                            e.getCount(),
                            e.getType(),
                            e.isNormalized(),
                            stride,
                            reinterpret_cast<const void *>(offset)
                    )
            );
            offset += e.getSize();
        }
        return buffer;
    }

    void VertexArrayBuffer::unbind() {
        glBindVertexArray(0);
    }

    void VertexArrayBuffer::bind() const {
        glBindVertexArray(id);
    }
}