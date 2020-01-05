#ifndef OPENGL_INDEX_BUFFER_H
#define OPENGL_INDEX_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <GL/glew.h>
#include <unnecessary/graphics/binding.h>

namespace un {


    class IndexBuffer : public BindableMixin<GL_ELEMENT_ARRAY_BUFFER> {
    public:
        static IndexBuffer createAndPush(
                uint32_t *data, size_t length
        );

        explicit IndexBuffer(uint32_t id);

    };
}
#endif
