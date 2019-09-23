#ifndef OPENGL_VERTEX_BUFFER_H
#define OPENGL_VERTEX_BUFFER_H

#include <cstdint>
#include <utility>
#include <vector>
#include <ostream>
#include <GL/glew.h>
#include <unnecessary/graphics/binding.h>
#include <unnecessary/utility/layout.h>
#include <sstream>

namespace gl {


    class VertexElement : public LayoutElement {
    private:
        GLenum type;
        bool normalized;
    public:
        VertexElement(uint8_t elementLength, uint8_t elementCount, GLenum type, bool normalized);

        GLenum getType() const;

        bool isNormalized() const;
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
        );
    };



}
#endif
