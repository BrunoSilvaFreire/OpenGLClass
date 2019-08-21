#ifndef OPENGL_INDEX_BUFFER_H
#define OPENGL_INDEX_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <GL/glew.h>
#include <graphics/binding.h>

namespace gl {


    class IndexBuffer : public BindableMixin<GL_ELEMENT_ARRAY_BUFFER> {
    private:
        uint32_t *data;
        size_t length;
    public:
        static IndexBuffer createAndPush(
                uint32_t *data, size_t length
        ) {
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

        IndexBuffer(uint32_t id, uint32_t *data, size_t length) : BindableMixin(id), data(data), length(length) {}

        uint32_t *getData() const {
            return data;
        }

        size_t getLength() const {
            return length;
        }
    };
}
#endif
