#include <unnecessary/graphics/buffers/index_buffer.h>

namespace un {

    IndexBuffer IndexBuffer::createAndPush(uint32_t *data, size_t length) {
        uint32_t id;
        glCreateBuffers(1, &id);
        IndexBuffer buf(id);
        buf.bind();
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                length * sizeof(uint32_t),
                data,
                GL_STATIC_DRAW
        );
        return buf;
    }

    IndexBuffer::IndexBuffer(uint32_t id) : BindableMixin(id) {}


}