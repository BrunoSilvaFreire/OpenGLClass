#ifndef OPENGL_VERTEX_ARRAY_BUFFER_H
#define OPENGL_VERTEX_ARRAY_BUFFER_H

#include <unnecessary/utility/debugging.h>
#include <unnecessary/graphics/binding.h>
#include <unnecessary/graphics/buffers/vertex_buffer.h>
#include <unnecessary/graphics/buffers/index_buffer.h>


namespace gl {
    class VertexArrayBuffer {
    private:
        uint32_t id;
    public:
        explicit VertexArrayBuffer(uint32_t id);

        void bind() const;

        static VertexArrayBuffer createFor(
                const VertexLayout &layout,
                const IndexBuffer &ibo,
                const VertexBuffer &vbo
        );

        static void unbind();
    };
}
#endif
