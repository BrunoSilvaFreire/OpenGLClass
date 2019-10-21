//
// Created by bruno on 06/08/2019.
//

#ifndef OPENGL_BINDING_H
#define OPENGL_BINDING_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <unnecessary/graphics/utility/debugging.h>

#define bind_scope(obj) obj.bind();\

namespace gl {

    template<GLenum TARGET>
    struct BindableMixin {
    private:
        uint32_t id;
    public:
        explicit BindableMixin(uint32_t id) : id(id) {}

        static void unbind() {
            glCall(
                    glBindBuffer(
                            TARGET,
                            0
                    )
            );
        }

        void bind() const {
            glCall(
                    glBindBuffer(
                            TARGET,
                            id
                    )
            );
        }

        void dispose() {
            glDeleteBuffers(1, &id);
        }
    };
}
#endif //OPENGL_BINDING_H
