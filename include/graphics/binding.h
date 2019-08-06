//
// Created by bruno on 06/08/2019.
//

#ifndef OPENGL_BINDING_H
#define OPENGL_BINDING_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>

namespace gl {

    template<GLenum TARGET>
    struct BindableMixin {
    private:
        uint32_t id;
    public:
        explicit BindableMixin(uint32_t id) : id(id) {}


        void bind() {
            glBindBuffer(
                    TARGET,
                    id
            );
        }

        void dispose() {
            glDeleteBuffers(1, &id);
        }
    };
}
#endif //OPENGL_BINDING_H
