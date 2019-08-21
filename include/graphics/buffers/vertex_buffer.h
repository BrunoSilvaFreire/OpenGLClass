#ifndef OPENGL_VERTEX_BUFFER_H
#define OPENGL_VERTEX_BUFFER_H

#include <cstdint>
#include <utility>
#include <vector>
#include <ostream>
#include <GL/glew.h>
#include <graphics/binding.h>
#include <utility/layout.h>
#include <sstream>

namespace gl {


    class VertexElement : public LayoutElement {
    private:
        GLenum type;
        bool normalized;
    public:
        VertexElement(uint8_t elementLength, uint8_t elementCount, GLenum type, bool normalized) : LayoutElement(
                elementLength,
                elementCount
        ), type(type), normalized(normalized) {}

        GLenum getType() const {
            return type;
        }

        bool isNormalized() const {
            return normalized;
        }
    };

    typedef Layout<VertexElement> VertexLayout;


    std::string element_to_string(uint8_t *start, VertexElement &element);

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
                size_t count
        ) {
            uint32_t id;
            glCreateBuffers(1, &id);
            VertexBuffer buf(id, layout, data, count * layout.getStride());
            buf.bind();
            glBufferData(
                    GL_ARRAY_BUFFER,
                    count * layout.getStride(), data,
                    GL_STATIC_DRAW
            );
            return buf;
        }
    };

    std::string element_to_string(uint8_t *ptr, VertexElement &element) {
        std::stringstream stream;


        auto count = element.getCount();
        auto type = element.getType();
        stream << (int) count << "x " << type << " (";
        auto tSize = element.getSize();
        for (int i = 0; i < count; ++i) {
            auto pos = ptr + i * tSize;

            switch (type) {
                case GL_FLOAT:
                    stream << *((float *) pos);
                default:
                    break;
            }
            if (i != count - 1) {
                stream << ", ";
            }
        }

        stream << ") [";
        /*for (int j = 0; j < count; ++j) {
            stream << shiroi::string_utility::hex(ptr + j * tSize, ptr + (j + 1) * tSize);
            if (j != count - 1) {
                stream << ' ';
            }
        }*/
        stream << " @ " << reinterpret_cast<void *>(ptr) << "]";
        return stream.str();
    }

}
#endif
