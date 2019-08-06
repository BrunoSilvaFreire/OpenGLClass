#ifndef OPENGL_VERTEX_ARRAY_BUFFER_H
#define OPENGL_VERTEX_ARRAY_BUFFER_H

#include "graphics/binding.h"

namespace gl {
    class VertexArrayBuffer {
    private:
        uint32_t id;
    public:
        explicit VertexArrayBuffer(uint32_t id) : id(id) {

        }

        void bind() {
            glBindVertexArray(id);
        }

        static VertexArrayBuffer createAndBind(const VertexLayout &layout) {
            uint32_t id;
            glCreateVertexArrays(1, &id);
            VertexArrayBuffer buffer(id);
            buffer.bind();
            const auto &elements = layout.getElements();
            uint32_t offset;
            uint8_t stride = layout.getStride();
            for (size_t i = 0; i < elements.size(); ++i) {
                auto &e = elements[i];
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(
                        i, e.getElementCount(), e.getType(), false, stride, nullptr
                );
            }
            return buffer;
        }
    };
}
#endif
