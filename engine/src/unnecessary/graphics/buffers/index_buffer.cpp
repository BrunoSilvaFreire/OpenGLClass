#include <unnecessary/graphics/buffers/index_buffer.h>

namespace gl {

    IndexBuffer IndexBuffer::createAndPush(uint32_t *data, size_t length) {
        uint32_t id;
        glCreateBuffers(1, &id);
        IndexBuffer buf(id, data, length);
        buf.bind();
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                length * sizeof(uint32_t),
                data,
                GL_STATIC_DRAW
        );
        return buf;
    }

    IndexBuffer::IndexBuffer(uint32_t id, uint32_t *data, size_t length)
            : BindableMixin(id), data(data), length(length) {}

    uint32_t *IndexBuffer::getData() const {
        return data;
    }

    size_t IndexBuffer::getLength() const {
        return length;
    }
}