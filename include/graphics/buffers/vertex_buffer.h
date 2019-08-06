#ifndef OPENGL_VERTEX_BUFFER_H
#define OPENGL_VERTEX_BUFFER_H

#include <cstdint>
#include <utility>
#include <vector>
#include <ostream>
#include <GL/glew.h>
#include <graphics/binding.h>
#include <utility/layout.h>

namespace gl {


    class VertexElement : public LayoutElement {
    private:
        GLenum type;
    public:
        VertexElement(uint8_t elementLength, uint8_t elementCount, GLenum type) : LayoutElement(
                elementLength,
                elementCount
        ), type(type) {}

        GLenum getType() const {
            return type;
        }
    };

    typedef Layout<VertexElement> VertexLayout;

    class VertexBuffer : public BindableMixin<GL_ARRAY_BUFFER> {
    private:
        VertexLayout layout;
        void *data;
        size_t length;
    public:


        VertexBuffer(
                uint32_t id, VertexLayout layout, void *data, size_t length
        ) : BindableMixin(id),
            layout(std::move(layout)),
            data(data),
            length(length) {}

        static VertexBuffer createAndPush(
                const VertexLayout &layout,
                void *data,
                size_t length
        ) {
            uint32_t id;
            glCreateBuffers(1, &id);
            VertexBuffer buf(id, layout, data, length * layout.getStride());
            glBufferData(
                    GL_ARRAY_BUFFER,
                    length, data,
                    GL_TRIANGLES
            );
            return buf;
        }
    };

}
#endif
