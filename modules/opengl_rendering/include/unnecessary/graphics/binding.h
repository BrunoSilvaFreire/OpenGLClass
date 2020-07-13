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

namespace un {
    struct Identified {
    protected:
        uint32_t id;
    public:
        explicit Identified(uint32_t id = -1);

        uint32_t getId() const;
    };

    template<GLenum TARGET>
    struct BindableMixin : Identified {
    private:
    public:
        explicit BindableMixin(uint32_t id) : Identified(id) {}

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

        uint32_t getId() const {
            return id;
        }
    };
}
#endif //OPENGL_BINDING_H
