
#ifndef UNNECESSARYENGINE_UNIFORM_BUFFER_H
#define UNNECESSARYENGINE_UNIFORM_BUFFER_H

#include <unnecessary/graphics/binding.h>

namespace un {
    class UniformBuffer : public Identified {
    public:
        static UniformBuffer create() {
            uint32_t id;
            glCreateBuffers(1, &id);
            return UniformBuffer(id);
        }

        static UniformBuffer createWithData(
                void *data,
                size_t length
        ) {
            auto buf = create();
            buf.update(data, length);
            return buf;
        }

        explicit UniformBuffer(uint32_t id) : Identified(id) {}

        void update(void *data, size_t size) {
            glCall(
                    glNamedBufferData(
                            getId(),
                            size, data, GL_STATIC_DRAW
                    )
            );
        }
    };
}
#endif